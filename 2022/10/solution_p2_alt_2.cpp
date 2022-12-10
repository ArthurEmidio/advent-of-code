#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>
#include <chrono>
#include <thread>

using namespace std;

#define W 40
#define H 6

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

void render(const vector<vector<char>> &crt) {
	for (int i = 0; i < crt.size(); i++) {
		for (int j = 0; j < crt.front().size(); j++) {
			cout << crt[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void draw(vector<vector<char>> &crt, int currCycle, int registerValue) {
	int row = (currCycle - 1) / W;
	int col = (currCycle - 1) % W;
	crt[row][col] = abs(registerValue - col) <= 1 ? '#' : '.';

	render(crt);
	this_thread::sleep_for(std::chrono::milliseconds(20));
}

vector<vector<char>> solve(const vector<Command> &commands) {
	vector<vector<char>> crt(H, vector<char>(W, '.'));
	int currCycle = 1;
	int registerValue = 1;

	for (const Command &command : commands) {
		draw(crt, currCycle, registerValue);
		if (command.type == CommandType::ADDX) registerValue += command.aux;
		currCycle++;
	}

	return crt;
}

int main() {
	string line;

	vector<Command> commands;
	while (getline(cin, line)) {
		string cmd = line.substr(0, 4);
		if (cmd == "addx") {
			int x = stoi(line.substr(5));
			commands.push_back(Command::noop());
			commands.push_back(Command::addx(x));
		} else if (cmd == "noop") {
			commands.push_back(Command::noop());
		} else {
			assert(false);
		}
	}

	solve(commands);
	
	return 0;
}