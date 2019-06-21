/********************************************************************************** 
* 
* Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
* determine if the input string is valid.
* 
* The brackets must close in the correct order, "()" and "()[]{}" are all valid 
* but "(]" and "([)]" are not.
* 
*               
**********************************************************************************/

#include <iostream>
#include <string>
#include <stack>

using namespace std;


bool isValid(string s) {
    if(s.empty() || s.size() < 2 || s.size()%2 != 0) return false; 
    stack<string> mystack;
    for(int i = 0; i < s.size(); i++) {
        char cur = s[i];
        if(cur == '(' || cur == '[' || cur == '{') mystack.push(cur); 
    }

}

int main() {
    return 0;
}