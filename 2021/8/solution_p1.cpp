// 0 -> 6
// 1 -> 2 !
// 2 -> 5
// 3 -> 6
// 4 -> 4 !
// 5 -> 5
// 6 -> 6
// 7 -> 3 !
// 8 -> 7 !
// 9 -> 6

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

vector<string> getWords(const string &s) {
    vector<string> words;

    size_t offset = 0;
    while (true) {
        size_t pos = s.find(" ", offset);
        string word = s.substr(offset, pos - offset);
        words.push_back(word);

        if (pos == string::npos) break;
        offset = pos + 1;
    }

    return words;
}

int main() {
    set<int> easyLengths = {2, 3, 4, 7};

    string s;
    vector<int> v;
    int ans = 0;
    while (getline(cin, s)) {
        string s1 = s.substr(0, s.find(" | "));
        string s2 = s.substr(s1.size() + 3);
        vector<string> words = getWords(s2);
        for (const string &w : words) if (easyLengths.count(w.size())) ans++;
    }

    cout << ans << endl;
    
    return 0;
}