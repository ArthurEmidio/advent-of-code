#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

using Matrix = vector<vector<int>>;

static const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void increment(int i, int j, Matrix &m) {
    if (i < 0 || j < 0 || i >= m.size() || j >= m.back().size()) return;
    m[i][j]++;
}

void flash(int i, int j, Matrix &m) {
    for (const pair<int, int> &d : dirs) increment(i + d.first, j + d.second, m);
}

int step(Matrix &m) {
    vector<vector<bool>> flashed(m.size(), vector<bool>(m.back().size()));

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.back().size(); j++) {
            m[i][j]++;
        }
    }
    
    bool keepChecking = true;
    while (keepChecking) {
        keepChecking = false;
        for (int i = 0; i < m.size(); i++) {
            for (int j = 0; j < m.back().size(); j++) {
                if (m[i][j] > 9 && !flashed[i][j]) {
                    flash(i, j, m);
                    flashed[i][j] = true;
                    keepChecking = true;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.back().size(); j++) {
            if (flashed[i][j]) m[i][j] = 0, ans++;
        }
    }

    return ans;
}

int solve(Matrix &m) {
    int ans = 0;
    for (int i = 0; i < 100; i++) ans += step(m);
    return ans;
}

int main() {
    string s;
    int ans = 0;
    Matrix m;
    while (getline(cin, s)) {
        m.push_back(vector<int>());
        for (char c : s) m.back().push_back(c - '0');
    }

    cout << solve(m) << endl;
    
    return 0;
}