#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;
    int n = s.length();

    // 1. Precompute Double Rolling Hashes
    const ll P1 = 31, M1 = 1e9 + 7;
    const ll P2 = 37, M2 = 1e9 + 9;
    vector<ll> pow1(n + 1, 1), pow2(n + 1, 1);
    vector<ll> h1(n + 1, 0), h2(n + 1, 0);

    for (int i = 0; i < n; i++) {
        pow1[i + 1] = (pow1[i] * P1) % M1;
        pow2[i + 1] = (pow2[i] * P2) % M2;
        h1[i + 1] = (h1[i] * P1 + (s[i] - 'a' + 1)) % M1;
        h2[i + 1] = (h2[i] * P2 + (s[i] - 'a' + 1)) % M2;
    }

    // Pack two 32-bit hashes into a single 64-bit integer to save memory
    auto get_hash = [&](int l, int r) -> ull {
        ull res1 = (h1[r + 1] - (h1[l] * pow1[r - l + 1]) % M1 + M1) % M1;
        ull res2 = (h2[r + 1] - (h2[l] * pow2[r - l + 1]) % M2 + M2) % M2;
        return (res1 << 32) | res2;
    };

    // 2. Run Standard Manacher's Algorithm
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    int m = t.length();
    vector<int> p(m, 0);
    int c = 0, r = 0;
    for (int i = 0; i < m; i++) {
        int mirror = 2 * c - i;
        if (i < r) p[i] = min(r - i, p[mirror]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m && t[i - p[i] - 1] == t[i + p[i] + 1]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }

    // 3. Extract sub-palindromes from each center, stopping when seen
    // Map stores: hash -> earliest ending index in original string
    unordered_map<ull, int> first_end;
    first_end.reserve(n);

    for (int i = 1; i < m - 1; i++) {
        int rad = p[i];
        while (rad >= 1) {
            // Convert transformed center i and radius rad to original [l, r]
            int l = (i - rad) / 2;
            int end_idx = (i + rad - 2) / 2;

            ull h = get_hash(l, end_idx);
            auto it = first_end.find(h);

            if (it == first_end.end()) {
                // Brand new palindrome: insert and continue shrinking
                first_end[h] = end_idx;
                rad -= 2;
            } else {
                // Already seen! Update earliest ending position if needed, then STOP
                if (end_idx < it->second) {
                    it->second = end_idx;
                }
                break;
            }
        }
    }

    // 4. Count how many distinct palindromes first appear at each prefix
    vector<int> added_at(n, 0);
    for (const auto& entry : first_end) {
        added_at[entry.second]++;
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        total += added_at[i];
        cout << total << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
