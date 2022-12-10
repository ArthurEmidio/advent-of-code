#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int getDecimal(const string &binary) {
    int ans = 0;
    for (int i = binary.size() - 1, currPower = 1; i >= 0; i--, currPower *= 2) {
        if (binary[i] == '1') ans += currPower;
    }
    return ans;
}

int getMajority(const vector<string> &v, int i) {
    int zeroCount = 0, oneCount = 0;
    for (int j = 0; j < v.size(); j++) {
        if (v[j][i] == '0') zeroCount++;
        else oneCount++;
    }
    return oneCount > zeroCount ? 1 : (oneCount == zeroCount) ? 0 : -1;
}

vector<string> filter(const vector<string> &v, int i, bool keepOne) {
    vector<string> ans;
    for (const string &s : v) {
        if ((keepOne && s[i] == '1') || (!keepOne && s[i] == '0')) ans.push_back(s);
    }
    return ans;
}

int main() {
    char in[50];
    vector<string> v;
    while (scanf("%s", in) != EOF) {
        string s(in);
        v.push_back(s);
    }

    int bit_count = v.front().size();
    vector<string> oxygenFilter = v, co2Filter = v;
    for (int i = 0; i < bit_count; i++) {
        if (oxygenFilter.size() > 1) {
            int g = getMajority(oxygenFilter, i);
            oxygenFilter = filter(oxygenFilter, i, g == 1 || g == 0);
        }
        if (co2Filter.size() > 1) {
            int e = getMajority(co2Filter, i);
            co2Filter = filter(co2Filter, i, e == -1);
        }
    }

    string oxygen = oxygenFilter.front();
    string co2 = co2Filter.front();

    cout << getDecimal(oxygen) << " " << getDecimal(co2) << " " << getDecimal(oxygen) * getDecimal(co2) << endl;

    return 0;
}