/********************************************************************************** 
* 
* Find the contiguous subarray within an array (containing at least one number) 
* which has the largest sum.
* 
* For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
* the contiguous subarray [4,−1,2,1] has the largest sum = 6.
* 
* More practice:
* 
* If you have figured out the O(n) solution, try coding another solution using 
* the divide and conquer approach, which is more subtle.
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(vector<int>& nums) {
    if(nums.size() <= 0) return 0;
    if(nums.size() == 1) return nums[0];
    int result = nums[0];
    int pre = nums[0];
    for(int i = 1; i < nums.size(); i++) {
        if(pre <= 0) {
            pre = nums[i];
        } else {
            pre = pre + nums[i];
        }
        if(pre > result) result = pre;
    } 
    return result;
}