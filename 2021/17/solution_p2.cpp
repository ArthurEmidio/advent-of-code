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

using Area = pair<pair<int, int>, pair<int, int>>;

pair<int, int> parseArea(const string &s) {
    string p0 = s.substr(2, s.find("..") - 2);
    string p1 = s.substr(p0.size() + 4);
    return {stoi(p0), stoi(p1)};;
}

Area parse(const string &s) {
    string util = s.substr(string("target area: ").size());
    string xAreaStr = util.substr(0, util.find(", "));
    string yAreaStr = util.substr(xAreaStr.size() + 2);
    
    pair<int, int> xArea = parseArea(xAreaStr);
    pair<int, int> yArea = parseArea(yAreaStr);

    return {xArea, yArea};
}

void simulate(const Area &area, int xVel, int yVel, bool &reachesArea) {
    int x = 0, y = 0;
    while (y > area.second.first || yVel >= 0) {
        x += xVel;
        y += yVel;

        if (x >= area.first.first && x <= area.first.second && y >= area.second.first && y <= area.second.second) reachesArea = true;

        xVel = max(0, --xVel);
        yVel--;
    }
}

int main() {
    string s;
    getline(cin, s);
    Area area = parse(s);

    int ans = 0;
    for (int x = 0; x <= 300; x++) {
        for (int y = -500; y <= 500; y++) {
            bool reachesArea = false;
            int maxHeight;
            simulate(area, x, y, reachesArea);
            if (reachesArea) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}