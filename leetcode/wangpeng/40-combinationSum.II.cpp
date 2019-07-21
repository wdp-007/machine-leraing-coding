/********************************************************************************** 
* 
* Given a collection of candidate numbers (C) and a target number (T), find all 
* unique combinations in C where the candidate numbers sums to T.
* 
* Each number in C may only be used once in the combination.
* 
* Note:
* 
* > All numbers (including target) will be positive integers.
* > Elements in a combination (a1, a2, … , ak) must be in non-descending order. 
*   (ie, a1 ≤ a2 ≤ … ≤ ak).
* > The solution set must not contain duplicate combinations.
* 
* For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
* A solution set is: 
* [1, 7] 
* [1, 2, 5] 
* [2, 6] 
* [1, 1, 6] 
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

void getResult(vector<vector<int> >& result, vector<int>& array, int target, int index, int curSum, vector<int> tmp) {
    if(curSum == target) {
        vector<int> ans(tmp);
        result.push_back(tmp);
        return;
    }
    if(curSum > target || index > array.size()-1) return;
    for(int i = index; i < array.size(); i++) {
        if(i > index && array[i] == array[i-1]) continue;
        tmp.push_back(array[i]);
        getResult(result, array, target, i+1, curSum+array[i], tmp);
        tmp.pop_back();
    }
}

vector<vector<int> > combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int> > result;
    if(candidates.size() <= 0 || target <= 0) return result;
    sort(candidates.begin(), candidates.end());
    vector<int> tmp;
    getResult(result, candidates, target, 0, 0, tmp);
    return result;
}