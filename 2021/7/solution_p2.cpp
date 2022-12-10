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
        int curr = 0; // 1 + 2 + 3 + 4 -> n(n+1)/2
        for (int p : v) {
            int delta = abs(p - i);
            curr += (delta * (delta+1))/2;
        }
        ans = min(ans, curr);
    }

    cout << ans << endl;
    
    return 0;
}