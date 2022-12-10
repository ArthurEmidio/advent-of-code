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

#define ROOM_SIZE 4

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

bool isPathToRoomClear(int hallwayPos, const string &hallway, const vector<char> rooms[]) {
    char c = hallway[hallwayPos];
    const vector<char> &room = rooms[c - 'A'];
    
    for (char slot : room) {
        if (slot != c && slot != '.') return false;
    }
    
    return isHallwayPathClear(hallwayPos < roomPos[c - 'A'] ? hallwayPos+1 : hallwayPos-1, roomPos[c - 'A'], hallway);
}

int distToHallway(int roomIndex, int hallwayPos, const string &hallway, const vector<char> rooms[], int &movingIndex) {
    const vector<char> &room = rooms[roomIndex];
    
    int dist = 0;
    char c;
    for (int i = 0; i < room.size(); i++) {
        if (room[i] != '.') {
            dist = i + 1, c = room[i];
            break;
        }
    }

    movingIndex = dist - 1;
    return (abs(roomPos[roomIndex] - hallwayPos) + dist) * cost[c - 'A'];
}

int getRoomSlotIndexForInsertion(const vector<char> &room) {
    int roomSlotIndex = -1;
    for (int i = room.size() - 1; i >= 0; i--) {
        if (room[i] == '.') {
            roomSlotIndex = i;
            break;
        }
    }
    return roomSlotIndex;
}

int distToRoom(int hallwayPos, const string &hallway, const vector<char> rooms[]) {
    char c = hallway[hallwayPos];
    int roomIndex = c - 'A';
    int dist = getRoomSlotIndexForInsertion(rooms[roomIndex]) + 1;
    return (abs(roomPos[roomIndex] - hallwayPos) + dist) * cost[roomIndex];
}

struct Move {
    int totCost;
    string hallway;
    vector<char> rooms[4];

    Move(int totCost, const string &hallway, const vector<char> _rooms[]) : totCost(totCost), hallway(hallway) {
        for (int i = 0; i < 4; i++) rooms[i] = _rooms[i];
    }

    string encode() {
        string res = hallway;
        for (int i = 0; i < 4; i++) {
            for (char c : rooms[i]) res += c;
        }
        return res;
    }
};

Move moveToRoom(int hallwayPos, const string &hallway, const vector<char> rooms[]) {
    char c = hallway[hallwayPos];
    int roomIndex = c - 'A';

    int dist = distToRoom(hallwayPos, hallway, rooms);
    
    string hallwayCopy = hallway;
    hallwayCopy[hallwayPos] = '.';
    
    vector<char> roomsCopy[4];
    for (int i = 0; i < 4; i++) roomsCopy[i] = rooms[i];

    vector<char> &room = roomsCopy[roomIndex];
    room[getRoomSlotIndexForInsertion(room)] = c;

    return Move(dist, hallwayCopy, roomsCopy);
}

Move moveToHallway(int roomIndex, int hallwayPos, const string &hallway, const vector<char> rooms[]) {
    int movingIndex;
    int dist = distToHallway(roomIndex, hallwayPos, hallway, rooms, movingIndex);

    string hallwayCopy = hallway;
    vector<char> roomsCopy[4];
    for (int i = 0; i < 4; i++) roomsCopy[i] = rooms[i];

    hallwayCopy[hallwayPos] = roomsCopy[roomIndex][movingIndex];
    roomsCopy[roomIndex][movingIndex] = '.';
    
    return Move(dist, hallwayCopy, roomsCopy);
}

bool shouldMoveFromRoom(int roomIndex, const vector<char> rooms[]) {
    const vector<char> &room = rooms[roomIndex];
    for (char c : room) {
        if (c != '.' && (c - 'A') != roomIndex) return true;
    }
    return false; 
}

bool won(const string &hallway, const vector<char> rooms[]) {
    for (char c : hallway) if (c != '.') return false;
    for (int i = 0; i < 4; i++) {
        for (char c : rooms[i]) {
            if (c == '.' || (c - 'A') != i) return false;
        }
    }
    return true;
}

long long solve(const string &curr, map<string, long long> &dp) {
    if (dp.count(curr)) return dp[curr];

    string hallway = curr.substr(0, 11);
    vector<char> rooms[4];
    for (int i = 11, j = 0; i < curr.size(); i += ROOM_SIZE, j++) {
        for (int k = 0; k < ROOM_SIZE; k++) {
            rooms[j].push_back(curr[i + k]);
        }
    }

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

    vector<vector<char>> rows;

    getline(cin, s);
    rows.push_back(parseRow(s));

    rows.push_back({'D', 'C', 'B', 'A'});
    rows.push_back({'D', 'B', 'A', 'C'});

    getline(cin, s);
    rows.push_back(parseRow(s));

    string input = string(11, '.');
    for (int i = 0; i < 4; i++) {
        for (const vector<char> &row : rows) {
            input += row[i];
        }
    }

    map<string, long long> dp;
    cout << solve(input, dp) << endl;

    return 0;
}