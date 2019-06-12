/********************************************************************************** 
* 
* Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
* Find all unique triplets in the array which gives the sum of zero.
* 
* Note:
* 
* Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
* The solution set must not contain duplicate triplets.
* 
*     For example, given array S = {-1 0 1 2 -1 -4},
* 
*     A solution set is:
*     (-1, 0, 1)
*     (-1, -1, 2)
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector< vector<int> > threeSum(vector<int>& nums) {
    vector< vector<int> > result;
    if(nums.empty() || nums.size() < 3) return result;
    sort(begin(nums), end(nums));
    for(int i = 0; i < nums.size()-2; i++) {
        cout << i << endl;
        if(i > 0 && nums[i] == nums[i-1]) continue; 
        int left = i + 1;
        int right = nums.size() - 1;
        while(left < right) {
            if(left > i+1 && nums[left] == nums[left-1]) {
                left++;
                continue;
            }
            int sum = nums[left] + nums[right];
            if(sum < -nums[i]) {
                left++;
            } else if(sum > -nums[i]) {
                right--;
            } else {
                cout << "left: " << left << " right: " << right << endl;
                vector<int> tmp{nums[i], nums[left], nums[right]};
                result.push_back(tmp);
                left++;
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums{0,0,0,0};
    vector< vector<int> > result = threeSum(nums);
    return 0;
}