/********************************************************************************** 
* 
* Write a function to find the longest common prefix string amongst an array of strings.
* 
*               
**********************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string twostringCommonPrefix(string str1, string str2) {
    if(str1.empty() || str1 == "") return "";
    if(str2.empty() || str2 == "") return "";
    string tmp1 = str1.size() <= str2.size() ? str1 : str2;
    string tmp2 = tmp1 == str1 ? str2 : str1;
    cout << tmp1 << "  " << tmp2 << endl;
    for(int i  = 0; i < tmp1.size(); i++) {
        if(tmp1[i] != tmp2[i]) return tmp1.substr(0,i);
    }
    return tmp1;
}

string longestCommonPrefix(vector<string>& strs) {
    if(strs.size() <= 0) return ""; 
    if(strs.size() == 1) return strs[0];
    string result = strs[0];
    for(int i = 1; i < strs.size(); i++) {
        result = twostringCommonPrefix(result, strs[i]);
    }
    return result;
}


int main() {
    vector<string> strs{"aa", "a"};
    cout << longestCommonPrefix(strs) << endl;
    return 0;
}