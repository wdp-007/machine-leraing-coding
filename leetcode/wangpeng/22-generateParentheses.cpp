/********************************************************************************** 
* 
* Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
* 
* For example, given n = 3, a solution set is:
* 
* "((()))", "(()())", "(())()", "()(())", "()()()"
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

void getResult(int left, int right, vector<string>& result, string curStr, int index, int total) {
    if(index == total) {
        result.push_back(curStr);
    }
    cout << curStr << endl;
    if(left > right) return;
    if(left > 0) {
        getResult(left-1, right, result, curStr+"(", index+1, total);
    }
    if(right > 0) {
        getResult(left, right-1, result, curStr+")", index+1, total);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    if(n <= 0) return result;
    getResult(n, n, result, "", 0, 2*n);
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
    int n = 1;
    vector<string> result = generateParenthesis(n);
    printVector(result);
    return 0;
}