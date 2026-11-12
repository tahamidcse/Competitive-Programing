
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll BASE = 3;

vector<ll> power3;

ll getHash(const string &s) {
    ll hashValue = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        hashValue += (s[i] - 'a' + 1) * power3[i];
    }

    return hashValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> initial(n);
    vector<ll> hashes;

    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        cin >> initial[i];
        maxLen = max(maxLen, (int)initial[i].size());
    }

    power3.resize(maxLen + 1);

    power3[0] = 1;

    for (int i = 1; i <= maxLen; i++) {
        power3[i] = power3[i - 1] * BASE;
    }

    for (const string &s : initial) {
        hashes.push_back(getHash(s));
    }

    sort(hashes.begin(), hashes.end());

    while (m--) {
        string s;
        cin >> s;

        bool found = false;

        for (int i = 0; i < (int)s.size(); i++) {

            char original = s[i];

            for (char c = 'a'; c <= 'c'; c++) {

                if (c == original)
                    continue;

                s[i] = c;

                ll h = getHash(s);

                if (binary_search(
                    hashes.begin(),
                    hashes.end(),
                    h
                )) {
                    found = true;
                    break;
                }
            }

            s[i] = original;

            if (found)
                break;
        }

        cout << (found ? "YES" : "NO") << '\n';
    }

    return 0;
}
