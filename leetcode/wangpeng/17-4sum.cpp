/********************************************************************************** 
* 
* Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? 
* Find all unique quadruplets in the array which gives the sum of target.
* 
* Note:
* 
* Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
* The solution set must not contain duplicate quadruplets.
* 
*     For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
* 
*     A solution set is:
*     (-1,  0, 0, 1)
*     (-2, -1, 1, 2)
*     (-2,  0, 0, 2)
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector< vector<int> > fourSum(vector<int>& nums, int target) {
    vector< vector<int> > result;
    if(nums.size() < 4) return result;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size()-3; i++) {
        if(i > 0 && nums[i] == nums[i-1]) continue;
        int first = i;
        for(int j = first + 1; j < nums.size()-2; j++) {
            if(j > (first + 1) && nums[j] == nums[j-1]) continue;
            int second = j;
            int left = second + 1;
            int right = nums.size() - 1;
            while(left < right) {
                if(left > (second + 1) && nums[left] == nums[left-1]) {
                    left++;
                    continue;
                }
                int sum = nums[first] + nums[second] + nums[left] + nums[right];
                if(sum == target) {
                    vector<int> tmp{nums[first], nums[second], nums[left], nums[right]};
                    result.push_back(tmp);
                    left++;
                } else if(sum > target) {
                    right--;
                } else {
                    left++;
                }
            } 
        }
    }
    return result; 
}

int main() {
    return 0;
}