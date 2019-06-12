/********************************************************************************** 
* 
* Given an array S of n integers, find three integers in S such that the sum is 
* closest to a given number, target. Return the sum of the three integers. 
* You may assume that each input would have exactly one solution.
* 
*     For example, given array S = {-1 2 1 -4}, and target = 1.
* 
*     The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int closestSum = (nums[0] + nums[1] + nums[2]);
    for(int i = 0; i < nums.size() - 2; i++) {
        int left = i + 1;
        int right = nums.size() - 1;
        while(left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            int distance = abs(sum - target);
            if(distance < abs(closestSum - target)) {
                cout << nums[i] << " " << nums[left] << " " << nums[right] <<endl;
                closestSum = sum;
            }
            if(sum <= target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return closestSum;
}

int main() {
    vector<int> nums{-1,2,1,-4};
    int result = threeSumClosest(nums, 1);
    cout << result << endl;
    return 0;
}