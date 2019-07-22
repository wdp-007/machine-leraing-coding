/********************************************************************************** 
* 
* Given an array of non-negative integers, you are initially positioned at the first index of the array.
* 
* Each element in the array represents your maximum jump length at that position. 
* 
* Determine if you are able to reach the last index.
* 
* For example:
* A = [2,3,1,1,4], return true.
* 
* A = [3,2,1,0,4], return false.
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

bool canJump(vector<int>& nums) {
    if(nums.size() <= 1) return true;
    int max_reach = nums[0];
    for(int i = 1; i < nums.size(); i++) {
        if(max_reach < i) return false;
        if(max_reach < nums[i] + i) max_reach = nums[i] + i;
    }
    return true;
}

int main() {
    return 0;
}