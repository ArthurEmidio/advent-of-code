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

struct Item {
    bool isLiteral;
    int value;
    vector<Item> items;

    Item(int value) : isLiteral(true), value(value) {}
    Item(const vector<Item> items) : isLiteral(false), items(items) {}

    bool isLiteralPair() const {
        return !isLiteral && items.size() == 2 && items[0].isLiteral && items[1].isLiteral;
    }
};

void print(const Item &item) {
    if (item.isLiteral) {
        cout << item.value;
    } else {
        cout << "[";
        for (int i = 0; i + 1 < item.items.size(); i++) {
            print(item.items[i]);
            cout << ",";
        }
        print(item.items.back());
        cout << "]";
    }
}

Item add(const Item &i1, const Item &i2) {
    return Item({i1, i2});
}

pair<Item, int> parse(int i, const string &s) {
    if (isdigit(s[i])) {
        int j = i;
        while (j < s.size() && isdigit(s[j])) j++;
        int n = stoi(s.substr(i, j - i));
        return {Item(n), j};
    }

    if (s[i] != '[') exit(1);

    int j = i + 1;
    vector<Item> items;
    while (j < s.size() && s[j] != ']') {
        pair<Item, int> p = parse(j, s);
        items.push_back(p.first);
        j = p.second;
        if (j < s.size() && s[j] == ',') j++;
    }
    return {Item(items), j + 1};
}

struct ExplosionLocation {
    int previousIndex;
    int previousAdd;
    int nextIndex;
    int nextAdd;
    Item* literalPairItem;

    ExplosionLocation(int pidx, int nidx, Item* literalPairItem) :
        previousIndex(pidx), previousAdd(literalPairItem->items[0].value), nextIndex(nidx), nextAdd(literalPairItem->items[1].value), literalPairItem(literalPairItem) {}
};

ExplosionLocation* findExplosion(Item &item, int &n, int level) {
    if (item.isLiteral) {
        n++;
        return nullptr;
    }

    if (item.isLiteralPair() && level >= 4) {
        return new ExplosionLocation(n - 1, n + 2, &item);
    }

    for (Item &i : item.items) {
        ExplosionLocation* loc = findExplosion(i, n, level + 1);
        if (loc) return loc;
    }

    return nullptr;
}

Item explode(Item &item, int &n, ExplosionLocation *explosionLocation) {
    if (item.isLiteral) {
        if (n == explosionLocation->previousIndex) item.value += explosionLocation->previousAdd;
        else if (n == explosionLocation->nextIndex) item.value += explosionLocation->nextAdd;
        n++;
        return item;
    }

    if (&item == explosionLocation->literalPairItem) {
        n += 2;
        return Item(0);
    }
    
    for (Item &i : item.items) i = explode(i, n, explosionLocation);

    return item;
}

Item split(Item &item, bool &splitted) {
    if (splitted) return item;

    if (item.isLiteral) {
        if (item.value >= 10) {
            splitted = true;
            return Item({item.value/2, (item.value+1)/2});
        }
        return item;
    }

    for (Item &i : item.items) i = split(i, splitted);

    return item;
}

void stabilize(Item &root) {
    bool changed = true;
    while (changed) {
        changed = false;
        int n = 0;
        ExplosionLocation *loc = findExplosion(root, n, 0);
        if (loc) {
            n = 0;
            root = explode(root, n, loc);
            changed = true;

            print(root);
            cout << endl;
        }

        if (!changed) {
            bool splitted = false;
            root = split(root, splitted);
            changed = splitted;

            print(root);
            cout << endl;
        }
    }
}

long long magnitude(const Item &item) {
    if (item.isLiteral) return item.value;
    return 3*magnitude(item.items[0]) + 2*magnitude(item.items[1]);
}

int main() {
    string s;
    getline(cin, s);
    Item root = parse(0, s).first;

    while (getline(cin, s)) {
        print(root);
        cout << endl;

        Item item = parse(0, s).first;
        root = add(root, item);
        stabilize(root);

        print(root);
        cout << endl;
    }

    cout << magnitude(root) << endl;

    return 0;
}