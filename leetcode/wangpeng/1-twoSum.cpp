/********************************************************************************** 
* 
* Given an array of integers, find two numbers such that they add up to a specific target number.
* 
* The function twoSum should return indices of the two numbers such that they add up to the target, 
* where index1 must be less than index2. Please note that your returned answers (both index1 and index2) 
* are not zero-based.
* 
* You may assume that each input would have exactly one solution.
* 
* Input: numbers={2, 7, 11, 15}, target=9
* Output: index1=1, index2=2
* 
*               
**********************************************************************************/

#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> result;
    map<int, int> map_tmp;
    for(int i = 0; i < nums.size(); i++) {
        if(map_tmp.find(target - nums[i]) == map_tmp.end()) {
            // not in map
            map_tmp[nums[i]] = i;
        } else {
            result.push_back(map_tmp[target - nums[i]]);
            result.push_back(i);
            break;
        }
    }
    return result;
} 

int main() {
    vector<int> nums{2,6,2,9,4};
    // nums.push_back(2);
    // nums.push_back(6);
    // nums.push_back(2);
    // nums.push_back(9);
    // nums.push_back(4);
    vector<int> result = twoSum(nums, 13);
    for(int i : result) {
        cout << i << endl;
    }
    return 0;
}