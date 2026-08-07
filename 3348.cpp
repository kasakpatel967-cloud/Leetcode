class Solution {
public:

    // factor[digit][prime]
    // prime order = 2, 3, 5, 7
    int factor[10][4] = {
        {0, 0, 0, 0}, // 0
        {0, 0, 0, 0}, // 1
        {1, 0, 0, 0}, // 2
        {0, 1, 0, 0}, // 3
        {2, 0, 0, 0}, // 4
        {0, 0, 1, 0}, // 5
        {1, 1, 0, 0}, // 6
        {0, 0, 0, 1}, // 7
        {3, 0, 0, 0}, // 8
        {0, 2, 0, 0}  // 9
    };

    int B, C, D;

    vector<int> dp;

    // Convert 4 dimensions into one index
    int getId(int a, int b, int c, int d) {
        return (((a * (B + 1) + b) * (C + 1) + c)
                * (D + 1) + d);
    }

    /*
        Returns the minimum number of digits required
        to provide the required prime factors.
    */
    int minDigits(int a, int b, int c, int d) {

        // Nothing is required
        if (a == 0 && b == 0 && c == 0 && d == 0)
            return 0;

        int id = getId(a, b, c, d);

        if (dp[id] != -1)
            return dp[id];

        int ans = 1000000;

        // Try digits 2 to 9.
        // We don't need digit 1 because it contributes nothing.
        for (int digit = 2; digit <= 9; digit++) {

            int na = max(0, a - factor[digit][0]);
            int nb = max(0, b - factor[digit][1]);
            int nc = max(0, c - factor[digit][2]);
            int nd = max(0, d - factor[digit][3]);

            // IMPORTANT:
            // The chosen digit must actually reduce
            // at least one required factor.
            if (na == a &&
                nb == b &&
                nc == c &&
                nd == d) {
                continue;
            }

            ans = min(ans,
                      1 + minDigits(na, nb, nc, nd));
        }

        return dp[id] = ans;
    }

    /*
        Build the smallest possible number having exactly
        'len' positions and satisfying the required factors.
    */
    string build(int len, int a, int b, int c, int d) {

        string ans = "";

        for (int pos = 0; pos < len; pos++) {

            for (int digit = 1; digit <= 9; digit++) {

                int na = max(0, a - factor[digit][0]);
                int nb = max(0, b - factor[digit][1]);
                int nc = max(0, c - factor[digit][2]);
                int nd = max(0, d - factor[digit][3]);

                int remaining = len - pos - 1;

                /*
                    Can the remaining positions satisfy
                    the remaining factors?
                */
                if (minDigits(na, nb, nc, nd) <= remaining) {

                    ans += char('0' + digit);

                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;

                    break;
                }
            }
        }

        return ans;
    }

    string smallestNumber(string num, long long t) {

        // ----------------------------------------
        // STEP 1: Factorize t
        // ----------------------------------------

        int need2 = 0;
        int need3 = 0;
        int need5 = 0;
        int need7 = 0;

        while (t % 2 == 0) {
            need2++;
            t /= 2;
        }

        while (t % 3 == 0) {
            need3++;
            t /= 3;
        }

        while (t % 5 == 0) {
            need5++;
            t /= 5;
        }

        while (t % 7 == 0) {
            need7++;
            t /= 7;
        }

        // If anything remains, t has another prime factor.
        if (t != 1)
            return "-1";

        // ----------------------------------------
        // STEP 2: Initialize DP
        // ----------------------------------------

        B = need3;
        C = need5;
        D = need7;

        long long totalStates =
            1LL * (need2 + 1)
            * (need3 + 1)
            * (need5 + 1)
            * (need7 + 1);

        dp.assign(totalStates, -1);

        int n = num.size();

        // ----------------------------------------
        // STEP 3: Check if num itself works
        // ----------------------------------------

        bool zeroFree = true;

        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;

        for (char ch : num) {

            int digit = ch - '0';

            if (digit == 0) {
                zeroFree = false;
                break;
            }

            a += factor[digit][0];
            b += factor[digit][1];
            c += factor[digit][2];
            d += factor[digit][3];
        }

        if (zeroFree &&
            a >= need2 &&
            b >= need3 &&
            c >= need5 &&
            d >= need7) {

            return num;
        }

        // ----------------------------------------
        // STEP 4: Prefix factor counts
        // ----------------------------------------

        vector<array<int, 4>> pref(n + 1);
        vector<bool> zero(n + 1, false);

        for (int i = 0; i < n; i++) {

            pref[i + 1] = pref[i];
            zero[i + 1] = zero[i];

            int digit = num[i] - '0';

            if (digit == 0) {
                zero[i + 1] = true;
            }
            else {
                for (int j = 0; j < 4; j++) {
                    pref[i + 1][j] += factor[digit][j];
                }
            }
        }

        // ----------------------------------------
        // STEP 5:
        // Try to create an answer with the same length.
        // ----------------------------------------

        for (int pos = n - 1; pos >= 0; pos--) {

            // Prefix cannot contain zero
            if (zero[pos])
                continue;

            // Factors already provided by prefix
            int a = max(0, need2 - pref[pos][0]);
            int b = max(0, need3 - pref[pos][1]);
            int c = max(0, need5 - pref[pos][2]);
            int d = max(0, need7 - pref[pos][3]);

            int original = num[pos] - '0';

            // Make this digit larger than num[pos]
            for (int digit = original + 1;
                 digit <= 9;
                 digit++) {

                int na = max(0, a - factor[digit][0]);
                int nb = max(0, b - factor[digit][1]);
                int nc = max(0, c - factor[digit][2]);
                int nd = max(0, d - factor[digit][3]);

                int remaining = n - pos - 1;

                // Can the suffix be completed?
                if (minDigits(na, nb, nc, nd)
                    <= remaining) {

                    string answer = num.substr(0, pos);

                    answer += char('0' + digit);

                    answer += build(
                        remaining,
                        na,
                        nb,
                        nc,
                        nd
                    );

                    return answer;
                }
            }
        }

        // ----------------------------------------
        // STEP 6:
        // Same length is impossible.
        // Find the minimum required length.
        // ----------------------------------------

        int requiredLength =
            minDigits(
                need2,
                need3,
                need5,
                need7
            );

        int length = max(n + 1, requiredLength);

        return build(
            length,
            need2,
            need3,
            need5,
            need7
        );
    }
};