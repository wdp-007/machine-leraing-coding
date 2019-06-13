/********************************************************************************** 
* 
* Given a digit string, return all possible letter combinations that the number could represent.
* 
* A mapping of digit to letters (just like on the telephone buttons) is given below.
* 
* Input:Digit string "23"
* Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
* 
* Note:
* Although the above answer is in lexicographical order, your answer could be in any order you want.
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> letterCombinations(string digits) {
    vector<string> result;
    if(digits.size() <= 0) return result;
    string s[] = {"", "", "abc", "def", "ghi", "jkl", "mno","pqrs","tuv", "wxyz"};

}

void getResult(string digits, string s[], int index, string tmp, vector<string> result) {
    if(index > (digits.size()-1)) {
        result.push_back(tmp);
        return;
    }
    

}

int main() {
    return 0;
}