#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

using Matrix = vector<vector<int>>;

vector<vector<bool>> getTicked(const Matrix &board, const set<int> &seen) {
    vector<vector<bool>> ticked(board.size(), vector<bool>(board.size()));

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            ticked[i][j] = seen.count(board[i][j]);
        }
    }

    return ticked;
}

bool wins(const Matrix &board, const set<int> &seen) {
    vector<vector<bool>> ticked = getTicked(board, seen);

    for (int i = 0; i < board.size(); i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < board.size(); j++) {
            if (!ticked[i][j]) rowWin = false;
            if (!ticked[j][i]) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    return false;
}

int getAnswer(const Matrix &board, const set<int> &seen, int lastDraw) {
    vector<vector<bool>> ticked = getTicked(board, seen);

    int sumUnticked = 0;
    for (int i = 0; i < board.size(); i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < board.size(); j++) {  
            if (!ticked[i][j]) sumUnticked += board[i][j];
        }
    }  

    return sumUnticked * lastDraw;
}

int main() {
    string draws_str;
    getline(cin, draws_str);
    vector<int> draws;
    string n;
    stringstream ss(draws_str);
    while (getline(ss, n, ',')) draws.push_back(stoi(n));

    string tmp;
    vector<Matrix> boards;
    while (getline(cin, tmp)) {
        Matrix matrix(5, vector<int>(5));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int num;
                cin >> num;
                matrix[i][j] = num;
            }
        }
        boards.push_back(matrix);
    }

    set<int> memo;
    for (int d : draws) {
        memo.insert(d);

        bool found = false;
        for (int i = 0; i < boards.size(); i++) {
            if (wins(boards[i], memo)) {
                cout << getAnswer(boards[i], memo, d) << endl;
                found = true;
                break;
            }
        }

        if (found) break;
    }

    return 0;
}