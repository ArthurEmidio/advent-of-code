#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
    string s;
    vector<int> v;
    while (getline(cin, s, ',')) {
        v.push_back(stoi(s));
    }

    sort(v.begin(), v.end());

    int ans = INT_MAX;
    for (int i = v.front(); i <= v.back(); i++) {
        int curr = 0;
        for (int p : v) curr += abs(p - i);
        ans = min(ans, curr);
    }

    cout << ans << endl;
    
    return 0;
}