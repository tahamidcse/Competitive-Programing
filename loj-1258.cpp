
#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(string &s) {
    int n = s.size();

    vector<int> d1(n);

    int l = 0, r = -1;

    for (int i = 0; i < n; i++) {

        int k = (i > r) ? 1 :
            min(d1[l + r - i], r - i + 1);

        while (i - k >= 0 && i + k < n &&
               s[i - k] == s[i + k]) {
            k++;
        }

        d1[i] = k;

        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }

    return d1;
}

vector<int> manacher_even(string &s) {
    int n = s.size();

    vector<int> d2(n);

    int l = 0, r = -1;

    for (int i = 0; i < n; i++) {

        int k = (i > r) ? 0 :
            min(d2[l + r - i + 1], r - i + 1);

        while (i - k - 1 >= 0 && i + k < n &&
               s[i - k - 1] == s[i + k]) {
            k++;
        }

        d2[i] = k;

        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    return d2;
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

        vector<int> odd = manacher_odd(s);
        vector<int> even = manacher_even(s);

        int longest = 0;

        // Odd length palindromic suffix
        for (int i = 0; i < n; i++) {

            int right = i + odd[i] - 1;

            if (right == n - 1) {
                longest = max(longest,
                              2 * odd[i] - 1);
            }
        }

        // Even length palindromic suffix
        for (int i = 0; i < n; i++) {

            int right = i + even[i] - 1;

            if (even[i] > 0 && right == n - 1) {
                longest = max(longest,
                              2 * even[i]);
            }
        }

        int ans = n - longest;

        cout << "Case " << tc << ": " << n + ans << '\n';
    }

    return 0;
}
