/*
for each packet:
    first 3 bits: version
    next 3 bits: type ID

if typeID == 4: literal value
    each group follows, each having 5 bits. the first bit tells whether the group is the last one (0) or not (1)

if typeID != 4: operator packet
    after the packet header (first 6 bits), it contains a bit representing the length type ID
    if lengthTypeId == 0, then next 15 bits represents the total length (in bits) of the subpackets contained in this packet
    if lengthTypeId == 1, then next 11 bits represents the number of sub-packets immediately contained by this packet
*/

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

static const map<char, string> HEX_TO_BINARY = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"}
};

string hexToBinary(const string &hex) {
    string ans;
    for (char c : hex) ans += HEX_TO_BINARY.at(c);
    return ans;
}

int binaryToInteger(const string &binary) {
    int ans = 0;
    for (char b : binary) ans = ans*2 + (b - '0');
    return ans;
}

string extract(int n, int i, const string &s) {
    string ans;
    for (int j = i; j < i + n; j++) ans += s[j];
    return ans;
}

pair<int, int> getVersionSum(int i, const string &s) {
    int version = binaryToInteger(extract(3, i, s));
    int typeId = binaryToInteger(extract(3, i + 3, s));

    if (typeId == 4) {
        int k = i + 6;
        bool literalDone = false;
        while (!literalDone) {
            string literal = extract(4, k + 1, s);

            literalDone = s[k] == '0';
            k += 5;
        }

        return {k, version};
    }

    int versionSum = version;

    int k;
    if (s[i + 6] == '0') {
        int totalLengthBits = binaryToInteger(extract(15, i + 7, s));
        k = i + 22;
        int start = k;

        while (k - start < totalLengthBits) {
            pair<int, int> p = getVersionSum(k, s);
            k = p.first;
            versionSum += p.second;
        }
    } else {
        int subpacketCount = binaryToInteger(extract(11, i + 7, s));
        k = i + 18;

        while (subpacketCount--) {
            pair<int, int> p = getVersionSum(k, s);
            k = p.first;
            versionSum += p.second;
        }
    }

    return {k, versionSum};
}

int main() {
    string s;
    cin >> s;

    string binary = hexToBinary(s);
    cout << getVersionSum(0, binary).second << endl;

    return 0;
}