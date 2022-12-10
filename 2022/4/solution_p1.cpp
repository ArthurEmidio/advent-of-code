#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

struct Interval {
	int start;
	int end;

	Interval(int s, int e) : start(s), end(e) {}
};

Interval parseInterval(const string &s) {
	string b = s.substr(0, s.find('-'));
	string e = s.substr(b.size() + 1);
	return Interval(stoi(b), stoi(e));
}

pair<Interval, Interval> parse(const string &s) {
	string i1 = s.substr(0, s.find(','));
	string i2 = s.substr(i1.size() + 1);

	return {parseInterval(i1), parseInterval(i2)};
}

bool fullyContains(const Interval &i1, const Interval &i2) {
	return (i2.start >= i1.start && i2.end <= i1.end) || (i1.start >= i2.start && i1.end <= i2.end);
}

int main() {
	string line;
	int ans = 0;

	while (getline(cin, line)) {
		pair<Interval, Interval> intervals = parse(line);
		if (fullyContains(intervals.first, intervals.second)) ans++;
	}

	cout << ans << endl;

	return 0;
}