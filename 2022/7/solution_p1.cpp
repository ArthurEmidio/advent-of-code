#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>

using namespace std;

#define N 100000

struct Directory {
	string name;
	Directory *parentDirectory;
	map<string, Directory*> subDirectories;
	int accumulatedFileSize;

	Directory(string name, Directory *parentDirectory, map<string, Directory*> subDirectories, int accumulatedFileSize) :
		name(name), parentDirectory(parentDirectory), subDirectories(subDirectories), accumulatedFileSize(accumulatedFileSize) {}

	Directory(string name, Directory *parentDirectory) : name(name), parentDirectory(parentDirectory) {}
};

enum CommandType { CD, LS };

struct Command {
	CommandType type;
	string arg;

	Command(const CommandType &type, const string &arg) : type(type), arg(arg) {}
	Command(const CommandType &type) : type(type) {}

	static Command ls() {
		return Command(CommandType::LS);
	}

	static Command cd(const string &arg) {
		return Command(CommandType::CD, arg);
	}
};

struct File {
	string name;
	int size;

	File(const string &name, int size) : name(name), size(size) {}
};

string getToken(int start, const string &s) {
	string ans;
	for (int i = start; i < s.size() && !isblank(s[i]); i++) ans += s[i];
	return ans;
}

Command parseCommand(const string &line) {
	string commandType = getToken(2, line);

	if (commandType == "cd") return Command::cd(getToken(3 + commandType.size(), line));
	else if (commandType == "ls") return Command::ls();

	throw runtime_error("invalid command: " + commandType);
}

Directory* cd(const string &path, Directory *curr, Directory *root) {
	if (path == "..") return curr->parentDirectory;
	if (path == "/") return root;
	
	if (!curr->subDirectories.count(path)) throw runtime_error("invalid path to cd: " + path);
	return curr->subDirectories[path];
}

void processSubdirectory(Directory *curr, const string &subDirectoryName) {
	curr->subDirectories[subDirectoryName] = new Directory(subDirectoryName, curr);
}

void processFile(Directory *curr, const File &file) {
	curr->accumulatedFileSize += file.size;
}

File parseFile(const string &line) {
	string fileSize = getToken(0, line);
	string fileName = getToken(fileSize.size() + 1, line);
	return File(fileName, stoi(fileSize)); 
}

long long solve(Directory *curr, long long &accumulatedSize) {
	if (curr == nullptr) return 0L;
	long long totalSize = curr->accumulatedFileSize;

	for (const pair<string, Directory*> &subDir : curr->subDirectories) {
		totalSize += solve(subDir.second, accumulatedSize);
	}

	if (totalSize <= N) {
		accumulatedSize += totalSize;
	}

	return totalSize;
}

void print(Directory *curr, int indent) {
	if (curr == nullptr) return;

	for (int i = 0; i < indent; i++) cout << " ";
	cout << curr->name << " (" << curr->accumulatedFileSize << ")" << endl;
	for (const pair<string, Directory*> &subDir : curr->subDirectories) {
		print(subDir.second, indent + 2);
	}
}

int main() {
	string line;

	Directory *root = new Directory("/", nullptr);
	Directory *curr = nullptr;

	while (getline(cin, line)) {
		if (line.front() == '$') {
			Command command = parseCommand(line);
			if (command.type == CommandType::CD) {
				curr = cd(command.arg, curr, root);
			} else {
				assert(curr->accumulatedFileSize == 0);
				assert(curr->subDirectories.empty());
			}
		} else if (isdigit(line.front())) {
			processFile(curr, parseFile(line));
		} else if (getToken(0, line) == "dir") {
			processSubdirectory(curr, getToken(4, line));
		}
	}

	long long result = 0;
	solve(root, result);
	cout << result << endl;

	return 0;
}