#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <unordered_map>

using namespace std;

const static vector<int> hallwayValidDests = {0, 1, 3, 5, 7, 9, 10};
const static int roomPos[4] = {2, 4, 6, 8};
const static int cost[4] = {1, 10, 100, 1000};

vector<char> parseRow(const string &s) {
    vector<char> res;
    for (int i = 3; i <= 9; i += 2) res.push_back(s[i]);
    return res;
}

bool isHallwayPathClear(int start, int end, const string &hallway) {
    if (start > end) swap(start, end);
    for (int i = start; i <= end; i++) {
        if (hallway[i] != '.') return false;
    }
    return true;
}

bool isPathToRoomClear(int hallwayPos, const string &hallway, const pair<char, char> rooms[]) {
    char c = hallway[hallwayPos];
    const pair<char, char> &room = rooms[c - 'A'];
    if ((room.first != c && room.first != '.') || (room.second != c && room.second != '.')) return false;
    return isHallwayPathClear(hallwayPos < roomPos[c - 'A'] ? hallwayPos+1 : hallwayPos - 1, roomPos[c - 'A'], hallway);
}

int distToHallway(int roomIndex, int hallwayPos, const string &hallway, const pair<char, char> rooms[], bool &movingFront) {
    const pair<char, char> &room = rooms[roomIndex];
    int dist = room.first == '.' ? 2 : 1;
    char c = room.first == '.' ? room.second : room.first;
    movingFront = (dist == 1);
    return (abs(roomPos[roomIndex] - hallwayPos) + dist) * cost[c - 'A'];
}

int distToRoom(int hallwayPos, const string &hallway, const pair<char, char> rooms[]) {
    char c = hallway[hallwayPos];
    int roomIndex = c - 'A';
    int dist = rooms[roomIndex].second == '.' ? 2 : 1;
    return (abs(roomPos[roomIndex] - hallwayPos) + dist) * cost[roomIndex];
}

struct Move {
    int totCost;
    string hallway;
    pair<char, char> rooms[4];

    Move(int totCost, const string &hallway, const pair<char, char> _rooms[]) : totCost(totCost), hallway(hallway) {
        for (int i = 0; i < 4; i++) rooms[i] = _rooms[i];
    }

    string encode() {
        string res = hallway;
        for (int i = 0; i < 4; i++) {
            res += rooms[i].first;
            res += rooms[i].second;
        }
        return res;
    }
};

Move moveToRoom(int hallwayPos, const string &hallway, const pair<char, char> rooms[]) {
    char c = hallway[hallwayPos];
    int roomIndex = c - 'A';

    int dist = distToRoom(hallwayPos, hallway, rooms);
    
    string hallwayCopy = hallway;
    hallwayCopy[hallwayPos] = '.';
    
    pair<char, char> roomsCopy[4];
    for (int i = 0; i < 4; i++) roomsCopy[i] = rooms[i];
    if (roomsCopy[roomIndex].second == '.') roomsCopy[roomIndex].second = c;
    else roomsCopy[roomIndex].first = c;

    return Move(dist, hallwayCopy, roomsCopy);
}

Move moveToHallway(int roomIndex, int hallwayPos, const string &hallway, const pair<char, char> rooms[]) {
    bool movingFront;
    int dist = distToHallway(roomIndex, hallwayPos, hallway, rooms, movingFront);

    string hallwayCopy = hallway;
    pair<char, char> roomsCopy[4];
    for (int i = 0; i < 4; i++) roomsCopy[i] = rooms[i];

    if (movingFront) {
        hallwayCopy[hallwayPos] = roomsCopy[roomIndex].first;
        roomsCopy[roomIndex].first = '.';
    } else {
        hallwayCopy[hallwayPos] = roomsCopy[roomIndex].second;
        roomsCopy[roomIndex].second = '.';
    }
    
    return Move(dist, hallwayCopy, roomsCopy);
}

bool shouldMoveFromRoom(int roomIndex, const pair<char, char> rooms[]) {
    const pair<char, char> &room = rooms[roomIndex];
    if (room.second != '.' && (room.second - 'A') != roomIndex) return true;
    if (room.first != '.' && (room.first - 'A') != roomIndex) return true;
    return false; 
}

bool won(const string &hallway, const pair<char, char> rooms[]) {
    for (char c : hallway) if (c != '.') return false;
    for (int i = 0; i < 4; i++) {
        if (rooms[i].first == '.' || (rooms[i].first - 'A') != i) return false;
        if (rooms[i].second == '.' || (rooms[i].second - 'A') != i) return false;
    }
    return true;
}

long long solve(const string &curr, map<string, long long> &dp) {
    if (dp.count(curr)) return dp[curr];

    string hallway = curr.substr(0, 11);
    pair<char, char> rooms[4];
    for (int i = 11, j = 0; i < curr.size(); i += 2, j++) rooms[j] = {curr[i], curr[i + 1]};

    if (won(hallway, rooms)) return 0;

    long long ans = INT_MAX;
    for (int i = 0; i < hallway.size(); i++) {
        if (hallway[i] == '.') continue;
        if (!isPathToRoomClear(i, hallway, rooms)) continue;
        Move mv = moveToRoom(i, hallway, rooms);
        ans = min(ans, mv.totCost + solve(mv.encode(), dp));
    }

    for (int i = 0; i < 4; i++) {
        if (!shouldMoveFromRoom(i, rooms)) continue;
        for (int j : hallwayValidDests) {
            if (!isHallwayPathClear(roomPos[i] < j ? roomPos[i]+1 : roomPos[i]-1, j, hallway)) continue;
            Move mv = moveToHallway(i, j, hallway, rooms);
            ans = min(ans, mv.totCost + solve(mv.encode(), dp));
        }
    }

    return dp[curr] = ans;
}

int main() {
    string s;
    getline(cin, s);
    getline(cin, s);

    getline(cin, s);
    vector<char> row1 = parseRow(s);
    getline(cin, s);
    vector<char> row2 = parseRow(s);

    string input = string(11, '.');
    for (int i = 0; i < 4; i++) input += row1[i], input += row2[i];

    map<string, long long> dp;
    cout << solve(input, dp) << endl;

    return 0;
}