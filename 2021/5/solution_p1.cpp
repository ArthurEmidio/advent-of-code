#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

using Matrix = vector<vector<int>>;
using Point = pair<int, int>;

struct Line {
    Point p1;
    Point p2;
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}
};

Point parsePoint(const string &s) {
    string delimiter = ",";
    string x = s.substr(0, s.find(delimiter));
    string y = s.substr(x.size() + delimiter.size());
    return Point(stoi(x), stoi(y));
}

Line parseLine(const string &s) {
    string delimiter = " -> ";
    string p1_str = s.substr(0, s.find(delimiter));
    string p2_str = s.substr(p1_str.size() + delimiter.size());
    return Line(parsePoint(p1_str), parsePoint(p2_str));
}

int main() {
    string line_str;
    vector<Line> lines;
    while (getline(cin, line_str)) lines.push_back(parseLine(line_str));

    Matrix matrix(1000, vector<int>(1000));
    for (const Line &line : lines) {
        if (line.p1.first != line.p2.first && line.p1.second != line.p2.second) continue;
        // cout << line.p1.first << " " << line.p1.second << ") (" << line.p2.first << " " << line.p2.second << endl;

        Point p1, p2;
        if (line.p1.first > line.p2.first || line.p1.second > line.p2.second) p1 = line.p2, p2 = line.p1;
        else p1 = line.p1, p2 = line.p2;

        // cout << p1.first << " " << p1.second << ") (" << p2.first << " " << p2.second << endl;

        for (int i = p1.first; i <= p2.first; i++) {
            for (int j = p1.second; j <= p2.second; j++) {
                // cout << i << " " << j << endl;
                matrix[i][j]++;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.front().size(); j++) {
            // cout << matrix[i][j] << " ";
            if (matrix[i][j] >= 2) ans++;
        }
        // cout << endl;
    }

    cout << ans << endl;

    return 0;
}