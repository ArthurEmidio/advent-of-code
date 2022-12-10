#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

map<char, int> scoreOnPlay = {{'A', 1}, {'B', 2}, {'C', 3}};
map<char, char> wins = {{'A', 'C'}, {'B', 'A'}, {'C', 'B'}};

int main() {
	string line;

	int ans = 0;
	while (getline(cin, line)) {
		char opponent = line[0];
		char should = (line[2] - 'X') + 'A';
		
		if (wins[should] == opponent) {
			ans += 6 + scoreOnPlay[should];
		} else if (should == opponent) {
			ans += 3 + scoreOnPlay[should];
		} else {
			ans += scoreOnPlay[should];
		}
	}

	cout << ans << endl;

	return 0;
}