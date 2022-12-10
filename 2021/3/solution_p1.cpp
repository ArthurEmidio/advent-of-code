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

int main() {
    char in[50];
    vector<string> v;
    while (scanf("%s", in) != EOF) {
        string s(in);
        v.push_back(s);
    }

    int bit_count = v.front().size();
    string gamma, epsilon;
    for (int i = 0; i < bit_count; i++) {
        int zero_count = 0, one_count = 0;
        for (int j = 0; j < v.size(); j++) {
            if (v[j][i] == '0') zero_count++;
            else one_count++;
        }

        if (zero_count > one_count) gamma += '0', epsilon += '1';
        else gamma += '1', epsilon += '0';
    }

    cout << getDecimal(gamma) << " " << getDecimal(epsilon) << " " << getDecimal(gamma) * getDecimal(epsilon) << endl;

    return 0;
}