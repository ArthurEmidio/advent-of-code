#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int n;
    vector<int> v;
    while (scanf("%d", &n) != EOF) {
        v.push_back(n);
    }

    int curr = v[0] + v[1] + v[2];
    int ans = 0;
    for (int i = 3; i < v.size(); i++) {
        int newCurr = curr - v[i - 3] + v[i];
        if (newCurr > curr) ans++;
        curr = newCurr;
    }

    printf("%d\n", ans);

    return 0;
}