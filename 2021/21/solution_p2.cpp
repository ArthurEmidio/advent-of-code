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

long long dp[3][11][30][11][30][3];

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

long long solve(int turn, int p1, int p1s, int p2, int p2s, int target) {
    if (p1s >= 21) return target == 1 ? 1L : 0L;
    if (p2s >= 21) return target == 1 ? 0L : 1L;

    long long &ans = dp[turn][p1][p1s][p2][p2s][target];
    if (ans != -1) return ans;

    ans = 0;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                int sum = i + j + k;
                int p1c = p1, p1sc = p1s;
                int p2c = p2, p2sc = p2s;

                if (turn == 1) move(p1c, p1sc, sum);
                else move(p2c, p2sc, sum);
                ans += solve(!turn, p1c, p1sc, p2c, p2sc, target);
            }
        }
    }

    return ans;
}

int main() {
    memset(dp, -1, sizeof dp);

    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    int playerOneStart = parseStartPosition(line1);
    int playerTwoStart = parseStartPosition(line2);
    
    long long universesPlayerOneWins = solve(1, playerOneStart, 0, playerTwoStart, 0, 1);
    long long universesPlayerTwoWins = solve(1, playerOneStart, 0, playerTwoStart, 0, 2);

    cout << max(universesPlayerOneWins, universesPlayerTwoWins) << endl;

    return 0;
}