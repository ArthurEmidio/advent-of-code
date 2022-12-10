#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

map<string, long long> step(const map<string, long long> &pairsHistogram, const map<string, char> &rules) {
    map<string, long long> ans;

    for (const pair<string, long long> &p : pairsHistogram) {
        if (rules.count(p.first)) {
            char c = rules.at(p.first);
            string newPairOne = string(1, p.first[0]) + string(1, c);
            string newPairTwo = string(1, c) + string(1, p.first[1]);
            ans[newPairOne] += p.second;
            ans[newPairTwo] += p.second;
        } else {
            ans[p.first] += p.second;
        }
    }

    return ans;
}

long long frequency(const map<string, long long> &pairsHistogram, const string &originalPattern, function<bool(long long, long long)> func) {
    map<char, long long> hist;
    for (const pair<string, long long> &p : pairsHistogram) {
        hist[p.first[0]] += p.second;
        hist[p.first[1]] += p.second;
    }

    long long ans = hist.begin()->second;
    for (const pair<char, long long> &h : hist) {
        long long cnt = h.second;
        if (h.first == originalPattern.front()) cnt++;
        if (h.first == originalPattern.back()) cnt++;
        ans = func(ans, cnt / 2) ? ans : cnt / 2;
    }
    return ans;
}

long long mostFrequent(const map<string, long long> &pairsHistogram, const string &originalPattern) {
    return frequency(pairsHistogram, originalPattern, [=](long long a, long long b) {
        return a > b;
    });
}

long long leastFrequent(const map<string, long long> &pairsHistogram, const string &originalPattern) {
    return frequency(pairsHistogram, originalPattern, [=](long long a, long long b) {
        return a < b;
    });
}

/*
    NN: 1
    NC: 1
    CB: 1

    NN: 1
    CN: 1
    NC: 2
    CB: 1
    CH: 1
    HB: 1
*/

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

    map<string, long long> pairsHistogram;
    for (int i = 0; i + 1 < pattern.size(); i++) pairsHistogram[pattern.substr(i, 2)]++;
    for (int i = 0; i < 40; i++) pairsHistogram = step(pairsHistogram, rules);

    long long mostFrequentCount = mostFrequent(pairsHistogram, pattern);
    long long leastFrequentCount = leastFrequent(pairsHistogram, pattern);
    cout << mostFrequentCount << " " << leastFrequentCount << endl;
    cout << mostFrequentCount - leastFrequentCount << endl;
    
    return 0;
}