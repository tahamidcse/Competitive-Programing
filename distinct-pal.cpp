
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Node {
    int next[26];
    int len;
    int link;

    Node() {
        memset(next, 0, sizeof(next));
        len = 0;
        link = 0;
    }
};

Node tree[MAXN];

string s;
int sz, suff;

void init() {
    sz = 2;

    // Root 0: length -1
    tree[0] = Node();
    tree[0].len = -1;
    tree[0].link = 0;

    // Root 1: length 0
    tree[1] = Node();
    tree[1].len = 0;
    tree[1].link = 0;

    suff = 1;
}

int getLink(int v, int pos) {

    while (true) {
        int len = tree[v].len;

        if (pos - 1 - len >= 0 &&
            s[pos - 1 - len] == s[pos]) {
            return v;
        }

        v = tree[v].link;
    }
}

void addChar(int pos) {

    int c = s[pos] - 'a';

    int cur = getLink(suff, pos);

    // Palindrome already exists
    if (tree[cur].next[c]) {
        suff = tree[cur].next[c];
        return;
    }

    // Create a new palindrome
    int nw = sz++;

    tree[nw] = Node();
    tree[nw].len = tree[cur].len + 2;

    tree[cur].next[c] = nw;

    // Length 1 palindrome
    if (tree[nw].len == 1) {
        tree[nw].link = 1;
    }
    else {
        int linkCandidate = getLink(tree[cur].link, pos);

        tree[nw].link =
            tree[linkCandidate].next[c];
    }

    suff = nw;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    init();

    for (int i = 0; i < (int)s.size(); i++) {

        addChar(i);

        cout << sz - 2;

        if (i + 1 < (int)s.size())
            cout << " ";
    }

    cout << '\n';

    return 0;
}
