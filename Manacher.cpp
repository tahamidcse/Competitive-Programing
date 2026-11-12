
#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd_trivial(string s) {
    int n = s.size();

    s = "$" + s + "^";

    vector<int> p(n + 2);

    for (int i = 1; i <= n; i++) {
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
    }

    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;

    for (auto c : s) {
        t += string("#") + c;
    }

    auto res = manacher_odd_trivial(t + "#");

    return vector<int>(begin(res) + 1, end(res) - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        string s;
        cin >> s;

        int n = s.size();

        string rev = s;
        reverse(rev.begin(), rev.end());

        string t = s + rev;

        vector<int> p = manacher(t);

        int longest = 0;

        // Boundary between original and reversed string
        int boundary = 2 * n;

        for (int c = 0; c < (int)p.size(); c++) {

            // Palindrome must end at the boundary
            if (c + p[c] - 1 == boundary) {
                longest = max(longest, p[c] - 1);
            }
        }

        int ans = n - longest;

        cout << "Case " << tc << ": " << ans << '\n';
    }

    return 0;
}
