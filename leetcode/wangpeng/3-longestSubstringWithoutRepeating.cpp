/********************************************************************************** 
* 
* Given a string, find the length of the longest substring without repeating characters. 
* For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
* which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int longestSubstringWithoutRepeating(string s) {
    if(s.empty() || s.size() <= 0) return 0;
    if(s.size() == 1) return 1;
    int result = 0;

    int array[256]; //每个字符最后一次出现的位置
    fill_n(array, 256, -1);
    int left = -1; //代表最近一次出现重复字符的位置
    int right = 0;
    while(right < s.size()) {
        if(array[s[right]] != -1) {
            left = max(array[s[right]], left);
        }
        int length = right - left;
        result = length > result? length: result;
        cout << "left:" << left << " right:" << right << " len:" << result << endl;
        array[s[right]] = right;
        right++;
    }
    
    return result;
}

int main() {
    string s = "tmmzuxt";
    int result = longestSubstringWithoutRepeating(s);
    cout << result << endl;
    return 0;
}