#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int solve(int timer, int daysLeft) {
    if (!daysLeft) return 0;
    if (!timer) return 1 + solve(6, daysLeft - 1) + solve(8, daysLeft - 1);
    return solve(timer - 1, daysLeft - 1);
}

int main() {
    string s;
    vector<int> v;
    while (getline(cin, s, ',')) {
        v.push_back(stoi(s));
    }

    int ans = 0;
    for (int n : v) ans += 1 + solve(n, 80);
    cout << ans << endl;

    return 0;
}