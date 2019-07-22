/********************************************************************************** 
* 
* Implement wildcard pattern matching with support for '?' and '*'.
* 
* '?' Matches any single character.
* '*' Matches any sequence of characters (including the empty sequence).
* 
* The matching should cover the entire input string (not partial).
* 
* The function prototype should be:
* bool isMatch(const char *s, const char *p)
* 
* Some examples:
* isMatch("aa","a") → false
* isMatch("aa","aa") → true
* isMatch("aaa","aa") → false
* isMatch("aa", "*") → true
* isMatch("aa", "a*") → true
* isMatch("ab", "?*") → true
* isMatch("aab", "c*a*b") → false
* Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Input:
s = "acdcb"
p = "a*c?b"
Output: false
*               
**********************************************************************************/
#include <iostream>

using namespace std;

bool helper(string s, string p, int index1, int index2) {
    if(index1 >= s.size() && index2 >= p.size()) return true;
    if(index1 == s.size() && index2 < p.size()) {
        for(int i = index2; i < p.size(); i++) {
            if(p[i] != '*') return false;
        }
        return true;
    }
    if(index1 >= s.size() || index2 >= p.size()) return false;
    if(s[index1] == p[index2] || p[index2] == '?') {
        return helper(s, p, index1+1, index2+1);
    }
    if(p[index2] == '*') {
        while(p[index2] == '*') index2++;
        if(index2 == p.size()) return true;
        for(int i = index1; i <= s.size(); i++) {
            if(helper(s, p, i, index2)) return true;
        }
    }
    return false;
}
123
bool isMatch(string s, string p) {
    if(p == "*") return true;
    if(s.size() <= 0 && p.size() <= 0) return true;
    if(s.size() <= 0 || p.size() <= 0) return false;
    return helper(s, p, 0, 0);
}

int main() {
    return 0;
}