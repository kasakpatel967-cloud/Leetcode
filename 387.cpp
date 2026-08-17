class Solution {
public:
    int firstUniqChar(string s) {

        // Count the frequency of every character
        int freq[26] = {0};

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Find the first character whose frequency is 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }

        return -1;
    }
};