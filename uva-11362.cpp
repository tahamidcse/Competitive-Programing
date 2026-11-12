#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_NODES = 100005; // 10,000 strings * 10 digits max
int trie[MAX_NODES][10];
bool isEnd[MAX_NODES];
int nodeCount;

void initTrie() {
    nodeCount = 1;
    memset(trie[0], -1, sizeof(trie[0]));
    isEnd[0] = false;
}

// Inserts a string and returns false if a prefix conflict is found
bool insertAndCheck(const string& s) {
    int curr = 0;
    bool createdNewNode = false;

    for (char c : s) {
        int digit = c - '0';
        if (trie[curr][digit] == -1) {
            trie[curr][digit] = nodeCount;
            memset(trie[nodeCount], -1, sizeof(trie[nodeCount]));
            isEnd[nodeCount] = false;
            nodeCount++;
            createdNewNode = true;
        }
        curr = trie[curr][digit];

        // Case 1: An existing shorter number is a prefix of the current number
        if (isEnd[curr]) {
            return false;
        }
    }

    // Case 2: The current number is a prefix of an already inserted longer number
    if (!createdNewNode) {
        return false;
    }

    isEnd[curr] = true;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n;
        cin >> n;
        initTrie();

        bool consistent = true;
        for (int i = 0; i < n; i++) {
            string phone;
            cin >> phone;
            if (consistent) {
                if (!insertAndCheck(phone)) {
                    consistent = false;
                }
            }
        }

        cout << (consistent ? "YES" : "NO") << "\n";
    }

    return 0;
}
