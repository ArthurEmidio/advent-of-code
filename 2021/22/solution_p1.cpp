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

struct Cuboid {
    pair<int, int> x;
    pair<int, int> y;
    pair<int, int> z;
    Cuboid(pair<int, int> x, pair<int, int> y, pair<int, int> z) : x(x), y(y), z(z) {}

    void print() {
        cout << toStringPair(x) << "|" << toStringPair(y) << "|" << toStringPair(z) << endl;
    }

    private:
    string toStringPair(const pair<int, int> &p) {
        return "[" + to_string(p.first) + "," + to_string(p.second) + "]";
    }
};

struct Coords {
    int x;
    int y;
    int z;

    Coords(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator<(const Coords &coords) const {
        pair<int, pair<int, int>> p1 = {x, {y, z}};
        pair<int, pair<int, int>> p2 = {coords.x, {coords.y, coords.z}};
        return p1 < p2;
    }
};

enum Command {
    ON, OFF
};

vector<string> split(const string &s, string sep) {
    int start = 0;
    vector<string> res;
    while (start < s.size()) {
        int sepPos = s.find(sep, start);
        if (sepPos == string::npos) sepPos = s.size();
        string token = s.substr(start, sepPos - start);
        res.push_back(token);
        start += token.size() + sep.size();
    }
    return res;
}

Cuboid parseCuboid(const vector<string> &v) {
    vector<pair<int, int>> pairs;
    for (const string &s : v) {
        vector<string> coordPair = split(s.substr(2), "..");
        pairs.push_back({stoi(coordPair[0]), stoi(coordPair[1])});
    }
    return Cuboid(pairs[0], pairs[1], pairs[2]);
}

int solve(const vector<pair<Command, Cuboid>> &commands) {
    set<Coords> coords;

    for (const pair<Command, Cuboid> &cmd : commands) {
        Command command = cmd.first;
        Cuboid cuboid = cmd.second;

        for (int i = max(cuboid.x.first, -50); i <= min(cuboid.x.second, 50); i++) {
            for (int j = max(cuboid.y.first, -50); j <= min(cuboid.y.second, 50); j++) {
                for (int k = max(cuboid.z.first, -50); k <= min(cuboid.z.second, 50); k++) {
                    if (command == Command::ON) coords.insert(Coords(i, j, k));
                    else coords.erase(Coords(i, j, k));
                }
            }
        }
    }

    return coords.size();
}

int main() {
    string s;
    vector<pair<Command, Cuboid>> cmds;
    while (getline(cin, s)) {
        string cmdStr = s.substr(0, s.find(" "));
        Command cmd = cmdStr == "on" ? Command::ON : Command::OFF;
        vector<string> cuboid = split(s.substr(cmdStr.size() + 1), ",");
        cmds.push_back({cmd, parseCuboid(cuboid)});
    }

    cout << solve(cmds) << endl;

    return 0;
}