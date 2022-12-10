#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

#define N 4

bool onlyUnique(const map<char, int> &in) {
	return in.size() == N;
}

int main() {
	string line;
	getline(cin, line);

	map<char, int> seen;
	for (int i = 0; i < N; i++) seen[line[i]]++;

	int ans;
	for (int i = N; i < line.size(); i++) {
		if (onlyUnique(seen)) {
			ans = i;
			break;
		}
		seen[line[i - N]]--;
		if (!seen[line[i - N]]) seen.erase(line[i - N]);
		seen[line[i]]++;
	}

	cout << ans << endl;

	return 0;
}