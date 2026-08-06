class Solution {
public:
    int smallestNumber(int n, int t) {

        while (true)
        {
            int num = n;
            int product = 1;

            // Find product of digits
            while (num > 0)
            {
                product *= (num % 10);
                num /= 10;
            }

            // Check divisibility
            if (product % t == 0)
                return n;

            n++;
        }
    }
};