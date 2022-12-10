#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
	string line;

	long long ans = 0;
	while (getline(cin, line)) {
		long long curr = stoi(line);
		while (getline(cin, line)) {
			if (line.empty()) break;
			curr += stoi(line);
		}
		ans = max(ans, curr);
	}

	cout << ans << endl;


	return 0;
}