#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

int getPriority(char c) {
	return islower(c) ? (c - 'a') + 1 : (c - 'A') + 27;
}

int solve(const string &s) {
	int n = s.size();
	string p1 = s.substr(0, n / 2);
	string p2 = s.substr(p1.size(), n / 2);

	set<char> seenInFirst;
	for (char c : p1) seenInFirst.insert(c);
	
	char common;
	for (char c : p2) {
		if (seenInFirst.count(c)) {
			common = c;
			break;
		}
	}

	assert(common != 0);

	return getPriority(common);
}

int main() {
	string line;
	int ans = 0;

	while (getline(cin, line)) {
		ans += solve(line);
	}

	cout << ans << endl;

	return 0;
}