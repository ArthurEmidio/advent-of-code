#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

#define N 10

vector<pair<int, int>> diagDeltas = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
vector<pair<int, int>> linearDeltas = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void draw(vector<pair<int, int>> v) {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			pair<int, int> x = {j - 20, -i + 20};
			bool found = false;
			for (int k = 0; k < v.size(); k++) {
				if (v[k] == x) {
					if (k == 0) cout << 'H';
					else cout << k;
					found = true;
					break;
				}
			}
			if (!found) cout << ".";
		}
		cout << endl;
	}
	cout << endl << endl;
}

bool isOk(const pair<int, int> &head, const pair<int, int> &tail) {
	return abs(head.first - tail.first) <= 1 && abs(head.second - tail.second) <= 1;
}

bool sharesRowOrCol(const pair<int, int> &head, const pair<int, int> &tail) {
	return head.first == tail.first || head.second == tail.second;
}

pair<int, int> moveKnot(const pair<int, int> &fixed, const pair<int, int> &toMove) {
	const vector<pair<int, int>> &deltas = sharesRowOrCol(fixed, toMove) ? linearDeltas : diagDeltas;
	for (const pair<int, int> &delta : deltas) {
		pair<int, int> candidate = {toMove.first + delta.first, toMove.second + delta.second};
		if (isOk(fixed, candidate)) return candidate;
	}
	assert(false);
	return {};
}

void move(char dir, vector<pair<int, int>> &ropes, set<pair<int, int>> &visited) {
	pair<int, int> &head = ropes.front();

	switch (dir) {
		case 'R': head.first++; break;
		case 'L': head.first--; break;
		case 'U': head.second++; break;
		case 'D': head.second--; break;
	}

	for (int i = 1; i < N && !isOk(ropes[i - 1], ropes[i]); i++) {
		ropes[i] = moveKnot(ropes[i - 1], ropes[i]);
	}

	visited.insert(ropes.back());
}

int main() {
	string line;

	vector<pair<int, int>> knots(N);
	set<pair<int, int>> tailVisited;
	while (getline(cin, line)) {
		char dir = line.front();
		int quant = stoi(line.substr(2));
		while (quant--) move(dir, knots, tailVisited);
	}

	cout << tailVisited.size() << endl;

	return 0;
}