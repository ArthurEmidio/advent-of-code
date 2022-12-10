#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <utility>

using namespace std;

int main() {
    map<string, pair<int, int>> dirs = {{"forward", {1, 0}}, {"down", {0, 1}}, {"up", {0, -1}}};

    char in[100];
    int n;

    int x = 0, y = 0;
    while (scanf("%s %d", in, &n) != EOF) {
        string dir(in);

        pair<int, int> delta = dirs[dir];
        x += delta.first * n;
        y += delta.second * n;
    }
    
    cout << x*y << endl;

    return 0;
}