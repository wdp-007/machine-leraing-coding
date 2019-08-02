/********************************************************************************** 
* 
* Given a string s consists of upper/lower-case alphabets and empty space characters ' ', 
* return the length of last word in the string.
* 
* If the last word does not exist, return 0.
* 
* Note: A word is defined as a character sequence consists of non-space characters only.
* 
* For example, 
* Given s = "Hello World",
* return 5.
* 
*               
**********************************************************************************/
#include <iostream>

using namespace std;

int lengthOfLastWord(string s) {
    if(s.size() <= 0) return 0;
    int last = s.size()-1;
    while(last >= 0 && s[last] == ' ') {
        last--;
    }
    if(last < 0) return 0;
    int result = 0;
    while(last >= 0 && s[last] != ' ') {
        result++;
        last--;
    }
    return result;
}