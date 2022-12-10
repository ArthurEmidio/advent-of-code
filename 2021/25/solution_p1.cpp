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

vector<string> iterate(const vector<string> &grid, bool &moved) {
    int rows = grid.size();
    int cols = grid.front().size();

    vector<string> newGrid = grid;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != '>') continue;
            int nextCol = j + 1 == cols ? 0 : j + 1;
            if (grid[i][nextCol] == '.') {
                swap(newGrid[i][nextCol], newGrid[i][j]);
                moved = true;
            }
        }
    }

    vector<string> intermediate = newGrid;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (grid[i][j] != 'v') continue;
            int nextRow = i + 1 == rows ? 0 : i + 1;
            if (intermediate[nextRow][j] == '.') {
                swap(newGrid[nextRow][j], newGrid[i][j]);
                moved = true;
            }
        }
    }

    return newGrid;
}

int solve(const vector<string> &grid) {
    bool moved = true;
    vector<string> curr = grid;
    int ans = 0;
    
    while (moved) {
        moved = false;
        curr = iterate(curr, moved);
        ans++;
    }

    return ans;
}

int main() {
    string s;
    vector<string> grid;
    while (getline(cin, s)) grid.push_back(s);

    cout << solve(grid) << endl;

    return 0;
}