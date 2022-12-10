#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

using Point = pair<int, int>;
using Matrix = vector<vector<char>>;

struct FoldInstruction {
    FoldInstruction(bool horizontal, int axisCoordinate) : horizontal(horizontal), axisCoordinate(axisCoordinate) {}

    bool horizontal;
    int axisCoordinate;
};

Matrix fold(const Matrix &m, const FoldInstruction &inst) {
    int rowMax, colMax;
    if (inst.horizontal) rowMax = inst.axisCoordinate, colMax = m.front().size();
    else rowMax = m.size(), colMax = inst.axisCoordinate;

    Matrix result(rowMax, vector<char>(colMax));
    for (int i = 0; i < rowMax; i++) {
        for (int j = 0; j < colMax; j++) {
            result[i][j] = m[i][j];
        }
    }

    if (inst.horizontal) {
        int currRow = inst.axisCoordinate - 1, copyRow = inst.axisCoordinate + 1;
        while (currRow >= 0 && copyRow < m.size()) {
            for (int i = 0; i < m.front().size(); i++) result[currRow][i] = m[currRow][i] == m[copyRow][i] ? m[currRow][i] : '#';
            currRow--, copyRow++;
        }
    } else {
        int currCol = inst.axisCoordinate - 1, copyCol = inst.axisCoordinate + 1;
        while (currCol >= 0 && copyCol < m.front().size()) {
            for (int i = 0; i < m.size(); i++) result[i][currCol] = m[i][currCol] == m[i][copyCol] ? m[i][currCol] : '#';
            currCol--, copyCol++;
        }
    }

    return result;
}

int main() {
    string s;
    vector<Point> points;
    while (getline(cin, s)) {
        if (s.empty()) break;

        string x = s.substr(0, s.find(","));
        string y = s.substr(x.size() + 1);
        points.push_back(Point(stoi(x), stoi(y)));
    }

    vector<FoldInstruction> foldInstructions;
    while (getline(cin, s)) {
        string coords = s.substr(string("fold along ").size());
        string axis = coords.substr(0, coords.find("="));
        string axisCoordinate = coords.substr(axis.size() + 1);
        foldInstructions.push_back(FoldInstruction(axis == "y", stoi(axisCoordinate)));
    }

    int maxX = 0, maxY = 0;
    for (Point p : points) maxX = max(maxX, p.first), maxY = max(maxY, p.second);

    Matrix curr = Matrix(maxY + 1, vector<char>(maxX + 1, '.'));
    for (Point p : points) curr[p.second][p.first] = '#';
    
    Matrix result = fold(curr, foldInstructions.front());

    int ans = 0;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.front().size(); j++) {
            ans += result[i][j] == '#';
        }
    }

    cout << ans << endl;
    
    return 0;
}