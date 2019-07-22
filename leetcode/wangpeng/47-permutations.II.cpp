/********************************************************************************** 
* 
* Given a collection of numbers that might contain duplicates, return all possible unique permutations.
* 
* For example,
* [1,1,2] have the following unique permutations:
* [1,1,2], [1,2,1], and [2,1,1].
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

void printVector(vector<int>& ss){
    cout << "[ ";
    for(int i=0; i<ss.size(); i++){
        cout << ss[i] << " ";
    }
    cout << " ]" << endl;
}

map<int, int> m;

void helper(vector<int>& nums, vector<vector<int> >& result, int index, vector<int>& tmp) {
    if(index >= nums.size()) {
        vector<int> ans(tmp);
        //printVector(ans);
        result.push_back(ans);
        return;
    }
    for(int i = 0; i < nums.size(); i++) {
        if(i > 0 && nums[i] == nums[i-1]) continue;
        if(m[nums[i]] > 0) {
            m[nums[i]] = m[nums[i]] - 1;
            tmp.push_back(nums[i]);
            helper(nums, result, index+1, tmp);
            m[nums[i]] = m[nums[i]] + 1;
            tmp.pop_back();
        }
    }
}

vector<vector<int> > permuteUnique(vector<int>& nums) {
    vector<vector<int> > result;
    if(nums.size() <= 0) return result;
    if(nums.size() == 1) {
        result.push_back(nums);
        return result;
    }
    vector<int> tmp;
    for(int i = 0; i < nums.size(); i++) {
        if(m.find(nums[i]) == m.end()) {
            m[nums[i]] = 1;
        } else {
            m[nums[i]] = m[nums[i]] + 1;
        }
    }
    sort(nums.begin(), nums.end());
    helper(nums, result, 0, tmp);
    return result;
}



int main() {
    vector<int> nums{1,1,3};
    permuteUnique(nums);
    return 0;
}