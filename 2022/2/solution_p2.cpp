#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

map<char, int> scoreOnPlay = {{'A', 1}, {'B', 2}, {'C', 3}};
map<char, char> wins = {{'A', 'C'}, {'B', 'A'}, {'C', 'B'}};
map<char, char> loses = {{'C', 'A'}, {'A', 'B'}, {'B', 'C'}};

enum Result { WIN, LOSE, DRAW };

Result toResult(char c) {
    switch (c) {
        case 'X': return Result::LOSE;
        case 'Y': return Result::DRAW;
        default: return Result::WIN;
    }
}

int main() {
	string line;

	int ans = 0;
	while (getline(cin, line)) {
		char opponent = line[0];
		Result expectedResult = toResult(line[2]);
		
		switch (expectedResult) {
			case Result::WIN:
				ans += 6 + scoreOnPlay[loses[opponent]];
				break;
			case Result::DRAW:
				ans += 3 + scoreOnPlay[opponent];
				break;
			case Result::LOSE:
				ans += scoreOnPlay[wins[opponent]];
				break;
		}
	}

	cout << ans << endl;

	return 0;
}