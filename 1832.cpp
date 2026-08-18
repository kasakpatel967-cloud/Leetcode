class Solution {
public:
    bool checkIfPangram(string sentence) {
        bool alphabet[26] = {false};

        for(char ch : sentence) {
            alphabet[ch - 'a'] = true;
        }

        for(int i = 0; i < 26; i++) {
            if(alphabet[i] == false)
                return false;
        }

        return true;
    }
};