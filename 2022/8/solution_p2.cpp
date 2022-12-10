#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

int solve(const vector<string> &rows) {
	int rowCount = rows.size();
	int colCount = rows.front().size();
	vector<vector<vector<int>>> factors(rowCount, vector<vector<int>>(colCount));

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			int k = j - 1;
			while (k >= 0 && rows[i][j] > rows[i][k]) k--;
			factors[i][j].push_back(k == -1 ? j : j - k);

			k = j + 1;
			while (k < colCount && rows[i][j] > rows[i][k]) k++;
			factors[i][j].push_back(k == colCount ? colCount - j - 1 : k - j);
		}
	}

	for (int j = 0; j < colCount; j++) {
		for (int i = 0; i < rowCount; i++) {
			int k = i - 1;
			while (k >= 0 && rows[i][j] > rows[k][j]) k--;
			factors[i][j].push_back(k == -1 ? i : i - k);

			k = i + 1;
			while (k < rowCount && rows[i][j] > rows[k][j]) k++;
			factors[i][j].push_back(k == rowCount ? rowCount - i - 1 : k - i);
		}
	}

	int ans = 0;
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			int prod = 1;
			for (int x : factors[i][j]) prod *= x;
			ans = max(ans, prod);
		}
	}
	return ans;
}

int main() {
	string line;

	vector<string> rows;
	while (getline(cin, line)) rows.push_back(line);
	
	cout << solve(rows) << endl;

	return 0;
}