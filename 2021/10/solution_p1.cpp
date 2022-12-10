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
static const map<char, int> scores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

int solve(const string &s) {
    stack<char> st;
    for (char c : s) {
        if (open.count(c)) st.push(c);
        else {
            if (st.empty() || matches.at(c) != st.top()) return scores.at(c);
            st.pop();
        }
    }

    return 0;
}

int main() {
    string s;
    int ans = 0;
    while (getline(cin, s)) ans += solve(s);

    cout << ans << endl;
    
    return 0;
}