#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

string step(const string &s, const map<string, char> &rules) {
    string ans;

    for (int i = 0; i < s.size(); i++) {
        ans += s[i];
        if (i + 1 < s.size()) {
            string currPair = s.substr(i, 2);
            if (rules.count(currPair)) ans += rules.at(currPair);
        }
    }

    return ans;
}

int mostFrequent(const string &s) {
    map<char, int> hist;
    for (char c : s) hist[c]++;
    int ans = 0;
    for (const pair<char, int> &h : hist) ans = max(ans, h.second);
    return ans;
}

int leastFrequent(const string &s) {
    map<char, int> hist;
    for (char c : s) hist[c]++;
    int ans = INT_MAX;
    for (const pair<char, int> &h : hist) ans = min(ans, h.second);
    return ans;
}

int main() {
    string pattern;
    getline(cin, pattern);

    string currLine;
    map<string, char> rules;
    while (getline(cin, currLine)) {
        if (currLine.empty()) continue;

        string delimiter = " -> ";
        string lhs = currLine.substr(0, currLine.find(delimiter));
        string rhs = currLine.substr(lhs.size() + delimiter.size());
        rules[lhs] = rhs[0];
    }

    string curr = pattern;
    for (int i = 0; i < 10; i++) curr = step(curr, rules);
    int ans = mostFrequent(curr) - leastFrequent(curr);
    cout << ans << endl;
    
    return 0;
}