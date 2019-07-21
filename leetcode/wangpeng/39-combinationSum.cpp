/********************************************************************************** 
* 
* Given a set of candidate numbers (C) and a target number (T), find all unique combinations 
* in C where the candidate numbers sums to T. 
* 
* The same repeated number may be chosen from C unlimited number of times.
* 
* Note:
* 
* All numbers (including target) will be positive integers.
* Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
* The solution set must not contain duplicate combinations.
* 
* For example, given candidate set 2,3,6,7 and target 7, 
* A solution set is: 
* [7] 
* [2, 2, 3] 
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

void getResult(vector<vector<int> >& result, int target, vector<int>& array, int index, int curSum, vector<int>& tmp) {
    if(curSum == target) {
        vector<int> ans(tmp);
        result.push_back(ans);
        return;
    }
    if(curSum > target || index > array.size()-1) return;
    for(int i = index; i < array.size(); i++) {
        tmp.push_back(array[i]);
        getResult(result, target, array, i, curSum+array[i], tmp);
        tmp.pop_back();
    }
}

vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
    vector<vector<int> > result;
    if(candidates.size() <= 0 || target <= 0) return result;
    sort(candidates.begin(), candidates.end());
    vector<int> tmp;
    getResult(result, target, candidates, 0, 0, tmp);
    return result;
}

int main() {
    return 0;
}