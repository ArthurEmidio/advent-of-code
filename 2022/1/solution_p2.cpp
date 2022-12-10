#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
	string line;

	vector<int> calories;
	while (getline(cin, line)) {
		int curr = stoi(line);
		while (getline(cin, line)) {
			if (line.empty()) break;
			curr += stoi(line);
		}
		calories.push_back(curr);
	}

	sort(calories.begin(), calories.end(), greater<>());

	cout << calories[0] + calories[1] + calories[2] << endl;

	return 0;
}