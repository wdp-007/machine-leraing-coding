/********************************************************************************** 
 * 
 * Given an array of strings, group anagrams together.
 * 
 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
 * Return:
 * 
 * [
 *   ["ate", "eat","tea"],
 *   ["nat","tan"],
 *   ["bat"]
 * ]
 * 
 * Note:
 * 
 All inputs will be in lowercase.
The order of your output does not matter.
 * 
 **********************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<string> > groupAnagrams(vector<string>& strs) {
    vector<vector<string> > result;
    if(strs.size() <= 0) return result;
    if(strs.size() == 1) {
        result.push_back(strs);
        return result;
    }
    map<string, vector<string> > m;
    for(int i = 0; i < strs.size(); i++) {
        string s = strs[i];
        sort(s.begin(), s.end());
        if(m.find(s) != m.end()) {
            m[s].push_back(strs[i]);
        } else {
            vector<string> tmp{strs[i]};
            m[s] = tmp;
        }
    }

    for(map<string, vector<string> >::iterator i = m.begin(); i != m.end(); i++) {
        result.push_back(i->second);
    }
    return result;
}

int main() {
    string s = "123";
    string c = s;
    c = "456";
    cout << s << " " << c << endl;
    return 0;
}