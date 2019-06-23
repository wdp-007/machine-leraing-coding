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
    if(s.empty() || s.size() < 1) return true;
    if(s.size()%2 != 0) return false; 
    stack<char> mystack;
    for(int i = 0; i < s.size(); i++) {
        char cur = s[i];
        if(cur == '(' || cur == '[' || cur == '{') {
            mystack.push(cur); 
            continue;
        }
        if(mystack.empty()) return false;
        char tmp = mystack.top();
        mystack.pop();
        if(cur == ')') {
            if(tmp != '(') return false;
            continue;
        }
        if(cur == ']') {
            if(tmp != '[') return false;
            continue;
        }
        if(cur == '}') {
            if(tmp != '{') return false;
        }
    }
    if(mystack.empty()) return true;
    return false;
}

int main() {
    return 0;
}