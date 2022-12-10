#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

string getValidCharacters() {
	string s;
	for (char c = 'a'; c <= 'z'; c++) s.push_back(c);
	for (char c = 'A'; c <= 'Z'; c++) s.push_back(c);
	return s;
}

int getPriority(char c) {
	return islower(c) ? (c - 'a') + 1 : (c - 'A') + 27;
}

bool isInAll(char c, const vector<set<char>> &sacks) {
	for (const set<char> &sack : sacks) {
		if (!sack.count(c)) return false;
	}
	return true;
}

int solve(const vector<string> &sacks, const string &validCharacters) {
	vector<set<char>> sacksSets;
	for (const string &s : sacks) {
		set<char> sackSet;
		for (char c : s) sackSet.insert(c);
		sacksSets.push_back(sackSet);
	}

	char common;
	for (char c : validCharacters) {
		if (isInAll(c, sacksSets)) {
			common = c;
			break;
		}
	}

	assert(common != 0);

	return getPriority(common);
}

int main() {
	string validCharacters = getValidCharacters();
	string line;
	int ans = 0;

	while (getline(cin, line)) {
		string sack2, sack3;
		getline(cin, sack2);
		getline(cin, sack3);
		ans += solve({line, sack2, sack3}, validCharacters);
	}

	cout << ans << endl;

	return 0;
}