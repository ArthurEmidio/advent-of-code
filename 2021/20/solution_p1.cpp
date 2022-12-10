#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <unordered_map>

using namespace std;

using Image = vector<vector<bool>>;

bool getValue(int i, int j, const Image &img, bool defaultColor) {
    if (i < 0 || j < 0 || i >= img.size() || j >= img.front().size()) return defaultColor;
    return img[i][j];
}

int getWindowValue(int i, int j, const Image &img, bool defaultColor) {
    vector<bool> bits;
    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            bits.push_back(getValue(k, l, img, defaultColor));
        }
    }

    int ans = 0;
    for (bool b : bits) ans = ans*2 + (b ? 1 : 0);
    return ans;
}

Image addPadding(const Image &img, bool defaultColor) {
    Image res(img.size() + 6, vector<bool>(img.front().size() + 6, defaultColor));
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img.front().size(); j++) {
            res[i + 3][j + 3] = img[i][j];
        }
    }
    return res;
}

Image enhance(const vector<bool> &algo, const Image &img, bool defaultColor) {
    Image padded = addPadding(img, defaultColor);

    Image result(padded.size(), vector<bool>(padded.front().size()));
    for (int i = 0; i < padded.size(); i++) {
        for (int j = 0; j < padded.front().size(); j++) {
            int val = getWindowValue(i, j, padded, defaultColor);
            result[i][j] = algo[val];
        }
    }

    return result;
}

int solve(const vector<bool> &algo, const Image &img) {
    Image enhanced = img;
    bool defaultColor = false;
    for (int i = 0; i < 2; i++) {
        enhanced = enhance(algo, enhanced, defaultColor);

        for (int i = 0; i < enhanced.size(); i++) {
            for (int j = 0; j < enhanced.front().size(); j++) {
                cout << enhanced[i][j];
            }
            cout << endl;
        }

        cout << endl;
        cout << endl;

        defaultColor = enhanced[0][0];
    }

    int ans = 0;
    for (int i = 0; i < enhanced.size(); i++) {
        for (int j = 0; j < enhanced.front().size(); j++) {
            if (enhanced[i][j]) ans++;
        }
    }

    return ans;
}

int main() {
    string algoStr;
    cin >> algoStr;
    vector<bool> algo;
    for (char c : algoStr) algo.push_back(c == '#');

    string s;
    Image img;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        vector<bool> row;
        for (char c : s) row.push_back(c == '#');
        img.push_back(row);
    }

    cout << solve(algo, img) << endl;

    return 0;
}