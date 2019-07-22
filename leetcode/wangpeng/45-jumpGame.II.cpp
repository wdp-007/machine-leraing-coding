/********************************************************************************** 
* 
* Given an array of non-negative integers, you are initially positioned at the first index of the array.
* 
* Each element in the array represents your maximum jump length at that position. 
* 
* Your goal is to reach the last index in the minimum number of jumps.
* 
* For example:
* Given array A = [2,3,1,1,4]
* 
* The minimum number of jumps to reach the last index is 2. 
* (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int jump(vector<int>& nums) {
    if(nums.size() <= 1) return 0;
    vector<int> helper(nums.size());
    helper[0] = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(helper[nums.size()-1] != 0) return helper[nums.size()-1];
        if(i != 0 && helper[i] == 0) return -1; 
        //for(int j = 1; j <= nums[i]; j++) {
        for(int j = 1; j <= nums[i] && (i+j) < nums.size(); j++) {
            if(helper[i+j] == 0) {
                helper[i+j] = helper[i] + 1;
            }
        }
    }
    return helper[nums.size()-1];
}