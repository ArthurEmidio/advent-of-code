#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

enum CommandType {
	ADDX, NOOP
};

struct Command {
	CommandType type;
	int aux;

	Command(CommandType type) : type(type), aux(0) {}
	Command(CommandType type, int aux) : type(type), aux(aux) {}

	static Command addx(int aux) {
		return Command(CommandType::ADDX, aux);
	}

	static Command noop() {
		return Command(CommandType::NOOP);
	}
};

int computeStrengthForKeyCycles(const set<int> &keyCycles, int currCycle, int registerValue) {
	return keyCycles.count(currCycle) ? currCycle * registerValue : 0;
}

int solve(const vector<Command> &commands, const set<int> &keyCycles) {
	int currCycle = 1;
	int registerValue = 1;
	int ans = 0;

	for (const Command &command : commands) {
		currCycle++;
		ans += computeStrengthForKeyCycles(keyCycles, currCycle, registerValue);

		if (command.type == CommandType::ADDX) {
			currCycle++;
			registerValue += command.aux;
			ans += computeStrengthForKeyCycles(keyCycles, currCycle, registerValue);
		}
	}

	return ans;
}

int main() {
	string line;

	vector<Command> commands;
	while (getline(cin, line)) {
		string cmd = line.substr(0, 4);
		if (cmd == "addx") {
			int x = stoi(line.substr(5));
			commands.push_back(Command::addx(x));
		} else if (cmd == "noop") {
			commands.push_back(Command::noop());
		} else {
			assert(false);
		}
	}

	cout << solve(commands, {20, 60, 100, 140, 180, 220}) << endl;
	
	return 0;
}