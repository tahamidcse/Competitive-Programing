
#include <bits/stdc++.h>
using namespace std;

/*
    Manacher's Algorithm

    Purpose:
    Find the length of the longest palindromic suffix
    of the given string.

    A palindromic suffix is a palindrome that ends
    at the last character of the original string.

    The result will be used to calculate the minimum
    number of characters required to make the string
    a palindrome by appending characters to the right.
*/

int manacher(string s) {

    /*
        STEP 1: Transform the original string.

        Insert '#' between every character to handle
        both odd-length and even-length palindromes
        uniformly.

        '@' and '$' are boundary sentinels.

        Example:
        Original:   kamal
        Transformed: @#k#a#m#a#l#$
    */

    string t = "@";

    for (char c : s) {
        t += '#';
        t += c;
    }

    t += "#$";

    int n = t.size();

    /*
        p[i] = Radius of the longest palindrome
               centered at position i.

        The radius counts the number of expansions
        around the center in the transformed string.

        Because of the inserted '#', this radius is
        equal to the palindrome length in the original
        string.
    */

    vector<int> p(n, 0);

    /*
        center = Center of the palindrome that currently
                 extends farthest to the right.

        right  = Rightmost boundary of that palindrome.

        Initially, no palindrome has been established.
    */

    int center = 0, right = 0;

    // Stores the longest palindromic suffix length.
    int longest = 0;

    /*
        STEP 2: Process every possible palindrome center.

        We skip the two sentinel characters '@' and '$'
        because they are only used as boundaries.
    */

    for (int i = 1; i < n - 1; i++) {

        /*
            STEP 3: Mirror optimization.

            If the current position i is inside the
            right boundary of the previously discovered
            palindrome, we can use its mirror position.

            mirror = 2 * center - i

            The palindrome radius at the mirror position
            gives us an initial radius at position i.

            We cannot extend beyond the current right
            boundary, so we take the minimum of:

                right - i
                p[mirror]
        */

        int mirror = 2 * center - i;

        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }

        /*
            STEP 4: Expand the palindrome.

            Compare characters on both sides of center i.

            Left  = i - 1 - p[i]
            Right = i + 1 + p[i]

            If they are equal, the palindrome can expand.

            Continue until the characters do not match.
        */

        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }

        /*
            STEP 5: Update the rightmost palindrome.

            If the palindrome centered at i extends
            farther than the previous right boundary,
            update center and right.
        */

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        /*
            STEP 6: Identify the longest palindromic suffix.

            The final character of the transformed string
            (excluding '$') is at index n - 2.

            A palindrome centered at i ends at:

                i + p[i]

            Therefore, if:

                i + p[i] == n - 2

            the palindrome reaches the last character
            of the original string.

            Among all such palindromes, select the
            maximum radius.
        */

        if (i + p[i] == n - 2) {
            longest = max(longest, p[i]);
        }
    }

    // Return the longest palindromic suffix length.
    return longest;
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

        /*
            L = Length of the longest palindromic suffix.

            We can append the reverse of the remaining
            prefix to make the entire string a palindrome.

            Original length = N
            Palindromic suffix length = L
            Characters to append = N - L

            Final palindrome length:

                N + (N - L)

                = 2 * N - L
        */

        int L = manacher(s);

        cout << "Case " << tc << ": "
             << 2 * n - L << '\n';
    }

    return 0;
}
