#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NODES = 3200005; // ~100,000 numbers * 32 bits
int trie[MAX_NODES][2];        // Changed from 10 to 2 (for bits 0 and 1)
int nodeCount;

void initTrie() {
    nodeCount = 1;
    memset(trie[0], -1, sizeof(trie[0]));
}

// Modified: Inserts a 32-bit integer from Most Significant Bit (31) to Least (0)
void insert(int num) {
    int curr = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (trie[curr][bit] == -1) {
            trie[curr][bit] = nodeCount;
            memset(trie[nodeCount], -1, sizeof(trie[nodeCount]));
            nodeCount++;
        }
        curr = trie[curr][bit];
    }
}

// Added: Finds A[i] in the Trie that maximizes (A[i] ^ x)
int queryMaxXor(int x) {
    int curr = 0;
    int bestNum = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (x >> i) & 1;
        int oppositeBit = 1 - bit; // Greedy choice: pick opposite bit for max XOR

        if (trie[curr][oppositeBit] != -1) {
            bestNum |= (oppositeBit << i);
            curr = trie[curr][oppositeBit];
        } else {
            bestNum |= (bit << i);
            curr = trie[curr][bit];
        }
    }
    return bestNum; // Returns A[i]. If you want the max XOR value itself, return (bestNum ^ x)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    initTrie();

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        insert(a);
    }

    while (q--) {
        int x;
        cin >> x;
        int bestA = queryMaxXor(x);
        // Prints A[i] as requested. Change to (bestA ^ x) if the problem asks for the XOR result.
        cout << bestA << "\n"; 
    }

    return 0;
}
