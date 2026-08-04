class Solution {
public:
    vector<int> dp;

    int solve(int i, vector<int>& stoneValue)
    {
        if(i >= stoneValue.size())
            return 0;

        if(dp[i] != INT_MIN)
            return dp[i];

        int sum = 0;
        int ans = INT_MIN;

        for(int k = 0; k < 3 && i + k < stoneValue.size(); k++)
        {
            sum += stoneValue[i + k];
            ans = max(ans, sum - solve(i + k + 1, stoneValue));
        }

        return dp[i] = ans;
    }

    string stoneGameIII(vector<int>& stoneValue)
    {
        int n = stoneValue.size();

        dp.assign(n, INT_MIN);

        int diff = solve(0, stoneValue);

        if(diff > 0)
            return "Alice";

        if(diff < 0)
            return "Bob";

        return "Tie";
    }
};