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

struct Edge {
    pair<int, int> src;
    pair<int, int> dst;
    int weight;

    Edge(const pair<int, int> &src, const pair<int, int> &dst, int weight) : src(src), dst(dst), weight(weight) {}
};

using Matrix = vector<vector<int>>;

static const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool exists(int i, int j, const Matrix &matrix) {
    return i >= 0 && i < matrix.size() && j >= 0 && j < matrix.back().size();
}

vector<Edge> getEdges(int i, int j, const Matrix &matrix) {
    vector<Edge> edges;
    for (const pair<int, int> &d : dirs) {
        int neighborI = i + d.first;
        int neighborJ = j + d.second;
        if (exists(neighborI, neighborJ, matrix)) edges.push_back(Edge({i, j}, {neighborI, neighborJ}, matrix[neighborI][neighborJ]));
    }
    return edges;
}

int shortestPath(const pair<int, int> &src, const pair<int, int> &dst, const Matrix &matrix) {
    Matrix minDists(105, vector<int>(105, INT_MAX));
    minDists[src.first][src.second] = 0;

    auto cmp = [](const pair<int, pair<int, int>> &e1, const pair<int, pair<int, int>> &e2) { return e1.first > e2.first; };
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(cmp)> pq(cmp);
    pq.push({0, src});

    while (!pq.empty()) {
        pair<int, int> from = pq.top().second;
        pq.pop();
        
        for (const Edge &e : getEdges(from.first, from.second, matrix)) {
            int newWeight = minDists[from.first][from.second] + e.weight;
            if (minDists[e.dst.first][e.dst.second] > newWeight) {
                minDists[e.dst.first][e.dst.second] = newWeight;
                pq.push({newWeight, e.dst});
            }
        }
    }

    return minDists[dst.first][dst.second];
}

int main() {
    string s;
    Matrix matrix; 
    while (getline(cin, s)) {
        vector<int> v;
        for (char c : s) v.push_back(c - '0');
        matrix.push_back(v);
    }

    cout << shortestPath({0, 0}, {matrix.size() - 1, matrix.size() - 1}, matrix) << endl;
    
    return 0;
}