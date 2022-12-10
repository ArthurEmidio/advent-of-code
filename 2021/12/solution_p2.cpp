#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

using Graph = map<string, set<string>>;

bool isSmallCave(const string &s) {
    for (char c : s) {
        if (tolower(c) != c) return false;
    }
    return true;
}

int solve(const string &curr, set<string> &visited, bool usedAllowance, const Graph &graph) {
    if (curr == "start") return 1;
    if (visited.count(curr) && isSmallCave(curr)) {
        if (usedAllowance || curr == "end") return 0;
        usedAllowance = true;
    }

    bool added = false;
    if (!visited.count(curr)) visited.insert(curr), added = true;

    int ans = 0;
    for (const string &adj : graph.at(curr)) ans += solve(adj, visited, usedAllowance, graph);

    if (added) visited.erase(curr);

    return ans;
}

int solve(const Graph &graph) {
    set<string> visited;
    return solve("end", visited, false, graph);
}

int main() {
    string s;
    Graph graph;
    while (getline(cin, s)) {
        string src = s.substr(0, s.find("-"));
        string dst = s.substr(src.size() + 1);
        graph[src].insert(dst);
        graph[dst].insert(src);
    }

    cout << solve(graph) << endl;
    
    return 0;
}