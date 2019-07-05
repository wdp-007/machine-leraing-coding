/********************************************************************************** 
* 
* You are given a string, S, and a list of words, L, that are all of the same length. 
* Find all starting indices of substring(s) in S that is a concatenation of each word 
* in L exactly once and without any intervening characters.
* 
* For example, given:
* S: "barfoothefoobarman"
* L: ["foo", "bar"]
* 
* You should return the indices: [0,9].
* (order does not matter).
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
#include <map>

using namespace std;


vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    if(s.empty() || words.empty()) return result;
    map<string, int> map_words;
    int word_length = words[0].size();
    int words_length = word_length*words.size();
    if(s.size() < words_length) return result;
    for(string word : words) {
        if(map_words.find(word) == map_words.end()) {
            map_words[word] = 1;
        } else {
            map_words[word] = map_words[word] + 1;
        }
    }
    for(int i = 0; i <= (s.size() - words_length); i++) {
        string cur = s.substr(i, word_length);
        if(map_words.find(cur) != map_words.end()) {
            map<string, int> helper(map_words);
            int cnt = words.size();
            for(int j = i; j < i + words_length; j += word_length) {
                string str = s.substr(j, word_length);
                if(helper.find(cur) != helper.end()) {
                    helper[str] = helper[str] - 1;
                    if(helper[str] < 0) break;
                    cnt--;
                } else {
                    break;
                }
            }
            if(cnt == 0) result.push_back(i);
        }
    }
    return result;
}

int main() {
    return 0;
}