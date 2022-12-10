// 0 -> 6
// 1 -> 2 !
// 2 -> 5
// 3 -> 6
// 4 -> 4 !
// 5 -> 5 -> the string with 5 characters 
// 6 -> 6
// 7 -> 3 ! -> allows me to determine the line at the top
// 8 -> 7 ! -> not useful
// 9 -> 6

/*
    top-left: character showing up 6 times.
    bottom-left: character showing up 4 times.
    bottom-right: character showing up 9 times.

    top-right: get characters from string with 2 chars. Character representing top-right is the one without a representative.
    top: get characters from string with 3 chars. Character representing top is the one without a representative.
    middle: get characters from string with 4 chars. Character representing middle is the one without a representative.
    bottom: get characters from string with 7 chars. Character representing bottom is the one without a representative.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

enum Line {
    TOP, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, TOP_LEFT, MIDDLE
};

static const map<set<Line>, int> SEGMENT_MAP = {
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::BOTTOM_LEFT, Line::TOP_LEFT}, 0},
    {{Line::TOP_RIGHT, Line::BOTTOM_RIGHT}, 1},
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM, Line::BOTTOM_LEFT, Line::MIDDLE}, 2},
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::MIDDLE}, 3},
    {{Line::TOP_RIGHT, Line::BOTTOM_RIGHT, Line::TOP_LEFT, Line::MIDDLE}, 4},
    {{Line::TOP, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::TOP_LEFT, Line::MIDDLE}, 5},
    {{Line::TOP, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::BOTTOM_LEFT, Line::TOP_LEFT, Line::MIDDLE}, 6},
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM_RIGHT}, 7},
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::BOTTOM_LEFT, Line::TOP_LEFT, Line::MIDDLE}, 8},
    {{Line::TOP, Line::TOP_RIGHT, Line::BOTTOM_RIGHT, Line::BOTTOM, Line::TOP_LEFT, Line::MIDDLE}, 9}
};

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

int decode(const map<char, Line> &charToLine, const vector<string> &msg) {
    int ans = 0;
    for (const string &s : msg) {
        set<Line> lineSet;
        for (char c : s) lineSet.insert(charToLine.at(c));
        ans = ans*10 + SEGMENT_MAP.at(lineSet);
    }
    return ans;
}

char showingUp(int n, const vector<string> &signals) {
    map<char, int> hist;
    for (const string &signal : signals) {
        for (char c : signal) hist[c]++;
    }

    for (const pair<char, int> &p : hist) {
        if (p.second == n) return p.first;
    }
    exit(EXIT_FAILURE);
    return -1;
}

string filter(int length, const vector<string> &words) {
    for (const string &w : words) {
        if (w.size() == length) return w;
    }
    exit(EXIT_FAILURE);
    return "";
}

char withoutRep(const string &signal, const map<char, Line> &charToLine) {
    for (char c : signal) {
        if (!charToLine.count(c)) return c;
    }
    exit(EXIT_FAILURE);
    return ' ';
}

int solve(const vector<string> &signals, const vector<string> &msg) {
    map<char, Line> charToLine;

    charToLine[showingUp(4, signals)] = Line::BOTTOM_LEFT;
    charToLine[showingUp(6, signals)] = Line::TOP_LEFT;
    charToLine[showingUp(9, signals)] = Line::BOTTOM_RIGHT;

    charToLine[withoutRep(filter(2, signals), charToLine)] = Line::TOP_RIGHT;
    charToLine[withoutRep(filter(3, signals), charToLine)] = Line::TOP;
    charToLine[withoutRep(filter(4, signals), charToLine)] = Line::MIDDLE;
    charToLine[withoutRep(filter(7, signals), charToLine)] = Line::BOTTOM;

    return decode(charToLine, msg);
}

int main() {
    string s;
    vector<int> v;
    int ans = 0;
    while (getline(cin, s)) {
        string s1 = s.substr(0, s.find(" | "));
        string s2 = s.substr(s1.size() + 3);
        vector<string> lhs = getWords(s1);
        vector<string> rhs = getWords(s2);
        ans += solve(lhs, rhs);
    }

    cout << ans << endl;
    
    return 0;
}