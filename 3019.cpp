class Solution {
public:
    int countKeyChanges(string s) {
        int count = 0;

        for (int i = 1; i < s.length(); i++) {
            char a = tolower(s[i - 1]);
            char b = tolower(s[i]);

            if (a != b) {
                count++;
            }
        }

        return count;
    }
};