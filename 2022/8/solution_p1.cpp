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
	vector<vector<bool>> isVisible(rows.size(), vector<bool>(colCount, false));

	for (int i = 0; i < rowCount; i++) {
		char maxSoFar;

		isVisible[i][0] = true;
		int j = 1;
		maxSoFar = rows[i][0];
		while (j < colCount) {
			if (rows[i][j] > maxSoFar) {
				isVisible[i][j] = true;
				maxSoFar = rows[i][j];
			}
			j++;
		}

		isVisible[i][colCount - 1] = true;
		j = colCount - 2;
		maxSoFar = rows[i][colCount - 1];
		while (j >= 0) {
			if (rows[i][j] > maxSoFar) {
				isVisible[i][j] = true;
				maxSoFar = rows[i][j];
			}
			j--;
		}
	}

	for (int j = 0; j < colCount; j++) {
		char maxSoFar;

		isVisible[0][j] = true;
		int i = 1;
		maxSoFar = rows[0][j];
		while (i < rowCount) {
			if (rows[i][j] > maxSoFar) {
				isVisible[i][j] = true;
				maxSoFar = rows[i][j];
			}
			i++;
		}

		isVisible[rowCount - 1][j] = true;
		i = rowCount - 2;
		maxSoFar = rows[rowCount - 1][j];
		while (i >= 0) {
			if (rows[i][j] > maxSoFar) {
				isVisible[i][j] = true;
				maxSoFar = rows[i][j];
			}
			i--;
		}
	}

	int ans = 0;
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			cout << isVisible[i][j];
			if (isVisible[i][j]) ans++;
		}
		cout << endl;
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