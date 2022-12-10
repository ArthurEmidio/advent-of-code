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

vector<int> inputIndices;
vector<long long> powers;

void snapshotRegisters(const map<char, long long> &registers) {
    cout << "Registers:" << endl;
    for (const pair<char, long long> &var : registers) {
        cout << var.first << ": " << var.second << endl;
    }
    cout << endl;
}

enum CommandType {
    INP, ADD, MUL, DIV, MOD, EQL
};

class Parameter {
public:
    string value;

    Parameter(const string &value) : value(value) {}
    Parameter() : value("") {}

    long long resolve(long long variables[]) const {
        if (isalpha(value.front())) return variables[value.front()];
        return stoll(value);
    }
};

class CommandTemplate {
    static inline const map<string, CommandType> commandTypeMap = {
        {"inp", CommandType::INP},
        {"add", CommandType::ADD},
        {"mul", CommandType::MUL},
        {"div", CommandType::DIV},
        {"mod", CommandType::MOD},
        {"eql", CommandType::EQL}
    };

public:
    CommandType type;
    char var;
    Parameter param;

    CommandTemplate(const string &cmd, char var) : CommandTemplate(cmd, var, "") {}
    CommandTemplate(const string &cmd, char var, const string &param) : type(commandTypeMap.at(cmd)), var(var), param(Parameter(param)) {}
};

const static map<CommandType, function<void(const CommandTemplate &, long long[])>> funcs = {
    // {CommandType::INP, [](const CommandTemplate &cmd, map<char, long long> &variables) { variables[cmd.var] = streamInputs[streamIndex++]; }},
    {CommandType::ADD, [](const CommandTemplate &cmd, long long variables[]) { variables[cmd.var] += cmd.param.resolve(variables); }},
    {CommandType::MUL, [](const CommandTemplate &cmd, long long variables[]) { variables[cmd.var] *= cmd.param.resolve(variables); }},
    {CommandType::DIV, [](const CommandTemplate &cmd, long long variables[]) { variables[cmd.var] /= cmd.param.resolve(variables); }},
    {CommandType::MOD, [](const CommandTemplate &cmd, long long variables[]) { variables[cmd.var] %= cmd.param.resolve(variables); }},
    {CommandType::EQL, [](const CommandTemplate &cmd, long long variables[]) { variables[cmd.var] = variables[cmd.var] == cmd.param.resolve(variables); }}
};

string readToken(int i, const string &s) {
    string res;
    int k = i;
    while (k < s.size() && s[k] != ' ') k++;
    return s.substr(i, k - i);
}

long long solve(long long z, int pos, map<pair<long long, int>, long long> &dp, const vector<CommandTemplate> &commandTemplates) {
    if (pos == 14) return z == 0 ? 0 : -1;
    
    pair<long long, int> key = {z, pos};
    if (dp.count(key)) return dp[key];

    long long &ans = dp[key];
    ans = -1;
    for (int k = 1; k <= 9; k++) {
        long long variables[255];
        variables['w'] = k;
        variables['x'] = 0;
        variables['y'] = 0;
        variables['z'] = z;

        int commandIndex = inputIndices[pos] + 1;
        while (commandIndex < commandTemplates.size() && commandTemplates[commandIndex].type != CommandType::INP) {
            const CommandTemplate &commandTemplate = commandTemplates[commandIndex];
            funcs.at(commandTemplate.type)(commandTemplate, variables);
            commandIndex++;
        }

        long long nxt = solve(variables['z'], pos + 1, dp, commandTemplates);
        if (nxt >= 0) {
            ans = k*powers[pos] + nxt;
            break;
        }
    }

    return ans;
}

int main() {
    string s;
    vector<CommandTemplate> commandTemplates;
    while (getline(cin, s)) {
        string cmd = s.substr(0, 3);
        char var = s[4];

        if (cmd == "inp") {
            commandTemplates.push_back(CommandTemplate(cmd, var));
        } else {
            string param = readToken(6, s);
            commandTemplates.push_back(CommandTemplate(cmd, var, param));
        }
    }

    for (int i = 0; i < commandTemplates.size(); i++) {
        if (commandTemplates[i].type == CommandType::INP) inputIndices.push_back(i);
    }

    powers = vector<long long>(14);
    for (long long i = 13, power = 1; i >= 0; i--, power *= 10) powers[i] = power;

    map<pair<long long, int>, long long> dp;
    cout << solve(0, 0, dp, commandTemplates) << endl;

    return 0;
}