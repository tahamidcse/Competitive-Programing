#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum elements n <= 2*10^5, max bits = 30 (since x_i <= 10^9 < 2^30)
const int MAX_NODES = 200005 * 31;
int trie[MAX_NODES][2];
int nodes_count = 1;

void insert(int num) {
    int curr = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!trie[curr][bit]) {
            trie[curr][bit] = nodes_count++;
        }
        curr = trie[curr][bit];
    }
}

int query_max_xor(int num) {
    int curr = 0;
    int max_xor = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int opposite_bit = 1 - bit;
        if (trie[curr][opposite_bit]) {
            max_xor |= (1 << i);
            curr = trie[curr][opposite_bit];
        } else {
            curr = trie[curr][bit];
        }
    }
    return max_xor;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Insert 0 initially to account for subarrays starting at index 0
    insert(0);

    int prefix_xor = 0;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        prefix_xor ^= x;
        ans = max(ans, query_max_xor(prefix_xor));
        insert(prefix_xor);
    }

    cout << ans << "\n";
    return 0;
}
