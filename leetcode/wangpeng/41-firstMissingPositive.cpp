/********************************************************************************** 
* 
* Given an unsorted integer array, find the first missing positive integer.
* 
* For example,
* Given [1,2,0] return 3,
* and [3,4,-1,1] return 2.
* 
* Your algorithm should run in O(n) time and uses constant space.
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int firstMissingPositive(vector<int>& nums) {
    if(nums.size() <=0 ) return 1;
    if(nums.size() == 1) {
        int result = nums[0] == 1 ? 2:1;
        return result;
    }
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] == i+1) continue;
        while(nums[i] != (i+1) && nums[i] > 0 && nums[i]-1 < nums.size() && nums[nums[i]-1] != nums[i]) {
            int tmp = nums[nums[i]-1];
            nums[nums[i]-1] = nums[i];
            nums[i] = tmp;
        }
    }
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] != i+1) return i+1;
    }
    return nums.size();
}

int main() {
    return 0;
}