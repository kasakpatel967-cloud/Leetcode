class Solution {
public:
    int arraySign(vector<int>& nums) {
        int negative = 0;

        for (int num : nums) {
            if (num == 0) {
                return 0;
            }

            if (num < 0) {
                negative++;
            }
        }

        if (negative % 2 == 0) {
            return 1;
        } else {
            return -1;
        }
    }
};