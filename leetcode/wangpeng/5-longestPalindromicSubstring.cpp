/********************************************************************************** 
* 
* Given a string S, find the longest palindromic substring in S. 
* You may assume that the maximum length of S is 1000, 
* and there exists one unique longest palindromic substring.
*               
**********************************************************************************/

#include <iostream>
#include <string>

using namespace std;

string longestPalindrome(string s) {
    if(s.empty() || s.size() <= 1) return s;
    string result = string(1, s[0]);
    bool dp[s.size()+1][s.size()+1];
    dp[0][0] = true;
    for(int i = 1; i < sizeof(dp[0]); i++) {
        dp[s.size()][i] = false;
    }

    int length = s.size()+1;
    dp[length-1][length-1] = true;
    for(int i  = length-2; i >= 0; i--) {
        for(int j = length - 1; j >= i; j--) {
            dp[i][j] = false;
            if(i == j) {
                dp[i][j] = true;
                continue;
            }
            if(s[i] == s[j]) {
                if(j - i >1) {
                    dp[i][j] = dp[i+1][j-1];
                } else {
                    dp[i][j] = true;
                }

            } else {
                dp[i][j] = false;
            }
            if(dp[i][j] && (j-i+1) > result.size()) {
                result = s.substr(i, j-i+1);
            }
        }
    }

    return result;
}

int main() {
    string s  = "cbbd";
    string result = longestPalindrome(s);
    cout << result << endl;
    return 0;
}