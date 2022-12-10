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

int parseStartPosition(const string &s) {
    string p1 = s.substr(0, s.find(':'));
    string p2 = s.substr(p1.size() + 1);
    return stoi(p2.substr(1));
}

void move(int &pos, int &score, int dice) {
    int newPos = (pos + (dice % 10));
    pos = newPos <= 10 ? newPos : ((newPos % 11) + 1);
    score += pos;
}

int solve(int p1, int p2) {
    bool turn = true;
    int cnt = 0;
    int dice = 1;
    int p1s = 0, p2s = 0;
    while (p1s < 1000 && p2s < 1000) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += dice;
            dice = dice == 100 ? 1 : (dice + 1);
            cnt++;
        }

        if (turn) move(p1, p1s, sum);
        else move(p2, p2s, sum);
        turn = !turn;
    }

    return min(p1s, p2s) * cnt;
}

int main() {
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    int playerOneStart = parseStartPosition(line1);
    int playerTwoStart = parseStartPosition(line2);

    cout << solve(playerOneStart, playerTwoStart) << endl;

    return 0;
}