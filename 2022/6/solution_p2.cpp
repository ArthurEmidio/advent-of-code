#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

#define N 14

int main() {
	string line;
	getline(cin, line);

	map<char, int> seen;
	int i;
	for (i = 0; i < line.size() && seen.size() < N; i++) {
		seen[line[i]]++;
		if (i >= N) {
			int cnt = --seen[line[i - N]];
			if (!cnt) seen.erase(line[i - N]);
		}
	}

	cout << i << endl;

	return 0;
}