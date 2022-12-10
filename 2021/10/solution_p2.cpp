#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>

using namespace std;

static const set<char> open = {'(', '[', '{', '<'};
static const map<char, char> matches = {{')', '('}, {']', '['}, {'}', '{'}, {'>', '<'}};
static const map<char, int> scores = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

long long calcScore(const string &s) {
    stack<char> st;
    for (char c : s) {
        if (open.count(c)) st.push(c);
        else {
            if (st.empty() || matches.at(c) != st.top()) return -1;
            st.pop();
        }
    }

    long long ans = 0;
    while (!st.empty()) {
        ans = ans*5 + scores.at(st.top());
        st.pop();
    }

    return ans;
}

int main() {
    string s;
    vector<long long> scores;
    while (getline(cin, s)) {
        long long score = calcScore(s);
        if (score >= 0) scores.push_back(score);
    }

    sort(scores.begin(), scores.end());
    cout << scores[scores.size() / 2] << endl;
    
    return 0;
}