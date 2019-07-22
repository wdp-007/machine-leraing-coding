/********************************************************************************** 
* 
* Given a collection of numbers, return all possible permutations.
* 
* For example,
* [1,2,3] have the following permutations:
* [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
#include <set>
using namespace std;



void helper(int index, vector<int>& nums, vector<int>& tmp, vector<vector<int> >& result, vector<int>& s) {
    if(index >= nums.size()) {
        cout << "reach last" << endl;
        vector<int> ans(tmp);
        result.push_back(ans);
        return;
    }
    cout << "get into helper" << endl;
    for(int i = 0; i < nums.size(); i++) {
        if(s[i] != 0) continue;
        tmp.push_back(nums[i]);
        s[i] = 1;
        helper(index+1, nums, tmp, result, s);
        tmp.pop_back();
        s[i] = 0;
    }
}

vector<vector<int> > permute(vector<int>& nums) {
    vector<vector<int> > result;
    if(nums.size() <= 0) return result;
    if(nums.size() == 1) {
        result.push_back(nums);
        return result;
    }

    vector<int> s(nums.size(), 0);
    vector<int> tmp;
    helper(0, nums, tmp, result, s);
    return result;
}

int main() {
    vector<int> nums{1,2,3};
    permute(nums);
    return 0;
}