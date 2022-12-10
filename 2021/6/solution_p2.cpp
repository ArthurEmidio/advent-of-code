#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

long long dp[300][300];

long long solve(int timer, int daysLeft) {
    if (!daysLeft) return 0;

    long long &ans = dp[timer][daysLeft];
    if (ans != -1) return ans;

    if (!timer) return ans = 1 + solve(6, daysLeft - 1) + solve(8, daysLeft - 1);
    return ans = solve(timer - 1, daysLeft - 1);
}

int main() {
    memset(dp, -1, sizeof(dp));

    string s;
    vector<int> v;
    while (getline(cin, s, ',')) {
        v.push_back(stoi(s));
    }

    long long ans = 0;
    for (int n : v) ans += 1 + solve(n, 256);
    cout << ans << endl;

    return 0;
}