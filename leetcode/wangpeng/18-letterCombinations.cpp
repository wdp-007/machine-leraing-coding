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

void getResult(string digits, string s[], int index, string tmp, vector<string>& result) {
    if(index > (digits.size()-1)) {
        //cout << "get one: " << tmp << endl;
        result.push_back(tmp);
        return;
    }
    int dig = digits[index] - '0';
    cout << "dig is " << dig << endl;
    string cur = s[dig];
    cout << "cur is " << cur << endl;
    if(cur == "") {
        getResult(digits, s, index+1, tmp, result);
        return;
    }
    for(int i = 0; i < cur.size(); i++) {
        getResult(digits, s, index+1, tmp+cur[i], result);
    } 

}

vector<string> letterCombinations(string digits) {
    vector<string> result;
    if(digits.size() <= 0) return result;
    string s[] = {"", "", "abc", "def", "ghi", "jkl", "mno","pqrs","tuv", "wxyz"};
    getResult(digits, s, 0, "", result);
    return result;
}

void printVector(vector<string>& ss){
    cout << "{ ";
    for(int i=0; i<ss.size(); i++){
        if (i>0) cout << ", "; 
        cout << ss[i];
    }
    cout << " }" << endl;
}

int main() {
    string d = "23";
    vector<string> result = letterCombinations(d);
    printVector(result);
    return 0;
}