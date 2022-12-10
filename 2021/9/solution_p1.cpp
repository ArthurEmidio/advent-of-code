#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

using Matrix = vector<vector<int>>;

static const vector<pair<int, int>> deltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool isValueLowerThan(int val, int i, int j, const Matrix &m) {
    if (i < 0 || j < 0 || i >= m.size() || j >= m.back().size()) return true;
    return val < m[i][j];
}

int solve(const Matrix &m) {
    int ans = 0;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.back().size(); j++) {
            int val = m[i][j];
            bool isLowerPoint = true;
            for (const pair<int, int> &d : deltas) {
                isLowerPoint = isLowerPoint && isValueLowerThan(val, i + d.first, j + d.second, m);
            }
            if (isLowerPoint) ans += 1 + m[i][j];
        }
    }

    return ans;
}

int main() {
    string s;
    Matrix m;
    while (getline(cin, s)) {
        m.push_back(vector<int>());
        for (char c : s) {
            if (isnumber(c)) m.back().push_back(c - '0');
        }
    }

    cout << solve(m) << endl;
    
    return 0;
}