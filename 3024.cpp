class Solution {
public:
    string triangleType(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        // Cannot form a triangle
        if (nums[0] + nums[1] <= nums[2]) {
            return "none";
        }

        // All three sides are equal
        if (nums[0] == nums[2]) {
            return "equilateral";
        }

        // Any two sides are equal
        if (nums[0] == nums[1] || nums[1] == nums[2]) {
            return "isosceles";
        }

        // All sides are different
        return "scalene";
    }
}