#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

bool isOk(const pair<int, int> &head, const pair<int, int> &tail) {
	return abs(head.first - tail.first) <= 1 && abs(head.second - tail.second) <= 1;
}

void move(char dir, pair<int, int> &head, pair<int, int> &tail, set<pair<int, int>> &visited) {
	pair<int, int> oldHead = head;

	switch (dir) {
		case 'R': head.first++; break;
		case 'L': head.first--; break;
		case 'U': head.second++; break;
		case 'D': head.second--; break;
	}

	if (!isOk(head, tail)) tail = oldHead;
	visited.insert(tail);
}

int main() {
	string line;

	pair<int, int> head, tail;
	set<pair<int, int>> tailVisited;
	while (getline(cin, line)) {
		char dir = line.front();
		int quant = stoi(line.substr(2));
		while (quant--) move(dir, head, tail, tailVisited);
	}
	
	cout << tailVisited.size() << endl;

	return 0;
}