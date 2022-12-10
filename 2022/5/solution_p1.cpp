#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

struct Movement {
	int quantity;
	int from;
	int to;

	Movement(int q, int f, int t) : quantity(q), from(f), to(t) {}
};

string parseStackLevel(const string &s) {
	string ans;
	for (int i = 1; i < s.size(); i += 4) ans.push_back(s[i]);
	return ans;
}

pair<int, int> parseIntegerFromIndex(int i, const string &s) {
	int ans = 0;
	while (i < s.size() && isnumber(s[i])) {
		ans = ans*10 + (s[i] - '0');
		i++;
	}
	return {ans, i};
}

Movement parseMovement(const string &s) {
	pair<int, int> quant = parseIntegerFromIndex(5, s);
	pair<int, int> from = parseIntegerFromIndex(quant.second + 6, s);
	pair<int, int> to = parseIntegerFromIndex(from.second + 4, s);
	return Movement(quant.first, from.first, to.first);
}

string solve(vector<stack<char>> stacks, const vector<Movement> &movements) {
	for (const Movement &movement : movements) {
		int fromIndex = movement.from - 1;
		int toIndex = movement.to - 1;

		for (int i = 0; i < movement.quantity; i++) {
			stacks[toIndex].push(stacks[fromIndex].top());
			stacks[fromIndex].pop();
		}
	}

	string ans;
	for (const stack<char> &stack : stacks) ans += stack.top();
	return ans;
}

int main() {
	string line;

	vector<string> levels;
	while (getline(cin, line) && line.find('[') != string::npos) {
		levels.push_back(parseStackLevel(line));
	}
	reverse(levels.begin(), levels.end());

	vector<stack<char>> stacks(levels.front().size());
	for (const string &level : levels) {
		for (int i = 0; i < level.size(); i++) {
			if (!isblank(level[i])) stacks[i].push(level[i]);
		}
	}

	getline(cin, line);

	vector<Movement> movements;
	while (getline(cin, line)) {
		movements.push_back(parseMovement(line));
	}

	cout << solve(stacks, movements) << endl;

	return 0;
}