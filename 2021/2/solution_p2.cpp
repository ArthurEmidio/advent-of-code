#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    char in[100];
    int n;

    int x = 0, y = 0, aim = 0;
    while (scanf("%s %d", in, &n) != EOF) {
        string dir(in);

        if (dir == "down") aim += n;
        else if (dir == "up") aim -= n;
        else x += n, y += aim * n;
    }
    
    cout << x*y << endl;

    return 0;
}