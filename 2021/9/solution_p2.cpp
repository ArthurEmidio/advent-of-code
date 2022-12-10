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

int getBasinSize(int i, int j, vector<vector<bool>> &vis, const Matrix &m) {
    if (i < 0 || j < 0 || i >= m.size() || j >= m.back().size() || vis[i][j]) return 0;

    vis[i][j] = true;
    if (m[i][j] == 9) return 0;

    int ans = 1;
    for (const pair<int, int> &d : deltas) ans += getBasinSize(i + d.first, j + d.second, vis, m);
    return ans;
}

int solve(const Matrix &m) {
    vector<pair<int, int>> lowerPoints;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.back().size(); j++) {
            int val = m[i][j];
            bool isLowerPoint = true;
            for (const pair<int, int> &d : deltas) {
                isLowerPoint = isLowerPoint && isValueLowerThan(val, i + d.first, j + d.second, m);
            }
            if (isLowerPoint) lowerPoints.push_back({i, j});
        }
    }

    vector<int> basinSizes;
    vector<vector<bool>> vis(m.size(), vector<bool>(m.back().size()));
    for (const pair<int, int> &p : lowerPoints) {
        if (!vis[p.first][p.second]) basinSizes.push_back(getBasinSize(p.first, p.second, vis, m));
    }

    sort(basinSizes.rbegin(), basinSizes.rend());

    return basinSizes[0] * basinSizes[1] * basinSizes[2];
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