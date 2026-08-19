class Solution {
public:
    int mostWordsFound(vector<string>& sentences) {

        int maximum = 0;

        for (string sentence : sentences) {

            int spaces = 0;

            for (char c : sentence) {
                if (c == ' ') {
                    spaces++;
                }
            }

            int words = spaces + 1;

            maximum = max(maximum, words);
        }

        return maximum;
    }
};