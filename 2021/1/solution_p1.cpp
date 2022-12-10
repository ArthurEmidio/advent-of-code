#include <cstdio>

int main() {
    int n;
    int ans = 0;
    int prev = -1;
    while (scanf("%d", &n) != EOF) {
        if (prev > -1 && n > prev) ans++;
        prev = n;
    }

    printf("%d\n", ans);

    return 0;
}