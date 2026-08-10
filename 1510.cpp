class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[i] = true means the current player can win
        // when there are i stones.

        for (int i = 1; i <= n; i++) {

            // Try removing every possible square number
            for (int j = 1; j * j <= i; j++) {

                // If after removing j*j stones,
                // the opponent is in a losing position,
                // then current player can win.
                if (dp[i - j * j] == false) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};