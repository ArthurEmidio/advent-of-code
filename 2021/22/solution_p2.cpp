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

    long long volume() {
        return (x.second - x.first + 1L) * (y.second - y.first + 1L) * (z.second - z.first + 1L);
    }

    bool isValid() {
        return x.first <= x.second && y.first <= y.second && z.first <= z.second;
    }

    Cuboid intersection(const Cuboid &other) {
        pair<int, int> xrange = {max(this->x.first, other.x.first), min(this->x.second, other.x.second)};
        pair<int, int> yrange = {max(this->y.first, other.y.first), min(this->y.second, other.y.second)};
        pair<int, int> zrange = {max(this->z.first, other.z.first), min(this->z.second, other.z.second)};
        return Cuboid(xrange, yrange, zrange);
    }

    // xii, yii, xif, yif
    // [x1, xii], [xii, xif], [xif, x2]
    // [y1, yii], [yii, yif], [yif, y2]
    // [z1, zii], [zii, zif], [zif, z2]
    vector<Cuboid> split(const Cuboid &other) {
        vector<pair<int, int>> xpos = {{this->x.first, other.x.first - 1}, {other.x.first, other.x.second}, {other.x.second + 1, this->x.second}};
        vector<pair<int, int>> ypos = {{this->y.first, other.y.first - 1}, {other.y.first, other.y.second}, {other.y.second + 1, this->y.second}};
        vector<pair<int, int>> zpos = {{this->z.first, other.z.first - 1}, {other.z.first, other.z.second}, {other.z.second + 1, this->z.second}};

        vector<Cuboid> ans;
        for (int i = 0; i < 3; i++) {
            pair<int, int> xrange = xpos[i];
            if (xrange.first > xrange.second) continue;
            for (int j = 0; j < 3; j++) {
                pair<int, int> yrange = ypos[j];
                if (yrange.first > yrange.second) continue;
                for (int k = 0; k < 3; k++) {
                    if (i == 1 && j == 1 && k == 1) continue;
                    pair<int, int> zrange = zpos[k];
                    if (zrange.first > zrange.second) continue;
                    ans.push_back(Cuboid(xrange, yrange, zrange));
                }
            }
        }

        return ans;
    }

    void print() const {
        cout << toStringPair(x) << "|" << toStringPair(y) << "|" << toStringPair(z) << endl;
    }

    private:
    string toStringPair(const pair<int, int> &p) const {
        return "[" + to_string(p.first) + "," + to_string(p.second) + "]";
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

long long solve(const vector<pair<Command, Cuboid>> &commands) {
    vector<Cuboid> allCuboids;

    long long totalLightedVolume = 0;
    for (int i = commands.size() - 1; i >= 0; i--) {
        Command command = commands[i].first;

        stack<Cuboid> toAnalyse;
        toAnalyse.push(commands[i].second);

        vector<Cuboid> newCuboids;
        long long volume = 0;
        while (!toAnalyse.empty()) {
            Cuboid cuboid = toAnalyse.top();
            toAnalyse.pop();

            bool toDiscard = false;
            for (const Cuboid &other : allCuboids) {
                Cuboid intersection = cuboid.intersection(other);
                if (intersection.isValid()) {
                    vector<Cuboid> splits = cuboid.split(intersection);
                    for (const Cuboid &split : splits) toAnalyse.push(split);
                    toDiscard = true;
                    break;
                }
            }

            if (!toDiscard) {
                volume += cuboid.volume();
                newCuboids.push_back(cuboid);
            }
        }

        allCuboids.insert(allCuboids.end(), newCuboids.begin(), newCuboids.end());
        if (command == Command::ON) totalLightedVolume += volume;
    }

    return totalLightedVolume;
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