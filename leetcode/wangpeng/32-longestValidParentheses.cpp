/********************************************************************************** 
* 
* Given a string containing just the characters '(' and ')', 
* find the length of the longest valid (well-formed) parentheses substring.
* 
* For "(()", the longest valid parentheses substring is "()", which has length = 2.
* 
* Another example is ")()())", where the longest valid parentheses substring is "()()", 
* which has length = 4.
* 
*               
**********************************************************************************/
#include <iostream>


using namespace std;

int longestValidParentheses1(string s) {
    if(s.empty() || s.size() < 2) return 0;
    bool dp[s.size()+1][s.size()+1]; 
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < s.size(); j++) {
            dp[i][j] = false;
        }
    } 
    int max_length = -1;
    for(int i = 1; i < s.size(); i++) {
        for(int j = i+1; j < s.size(); j++) {
            if(s[i-1] == '(' && s[j-1] == ')') {
                if(i+1 > j-1) {
                    dp[i][j] = true;
                } else{
                    dp[i][j] = dp[i+1][j-1];
                }
                
            }
            if(dp[i][j] && (j-i+1) > max_length) max_length = j-i+1;
            cout << "i:" << i << " j:" << j << "  dp[i][j]:" << dp[i][j] << "  s[i-1]:" << s[i-1] << endl; 
        }
    }
    return max_length;
}

int longestValidParentheses(string s) {
    if(s.empty() || s.size() < 2) return 0;
    int dp[s.size()]; 
    dp[0] = 0;
    int max_length = -1;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == ')' && (i-dp[i-1]-1) >= 0 && s[i-dp[i-1]-1] == '(') {
            if(i-dp[i-1]-2 >= 0) {
                dp[i] = 2 + dp[i-1] + dp[i-dp[i-1]-2];
            } else {
                dp[i] = 2 + dp[i-1];
            }
        }
        if(max_length < dp[i]) {
            max_length = dp[i];
        } 
    }
    return max_length;
}

int main() {
    string s = ")()";
    int result = longestValidParentheses(s);
    cout << result << endl;
    return 0;
}