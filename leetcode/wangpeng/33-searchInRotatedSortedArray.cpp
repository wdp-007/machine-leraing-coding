/********************************************************************************** 
* 
* Suppose a sorted array is rotated at some pivot unknown to you beforehand.
* 
* (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
* 
* You are given a target value to search. If found in the array return its index, otherwise return -1.
* 
* You may assume no duplicate exists in the array.
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target) {
    if(nums.empty()) return -1;
    int left = 0;
    int right = nums.size()-1;
    while(left < right) {
        int mid = left + (right - left)/2;
        if(nums[mid] == target) return mid;
        if(nums[mid] > nums[left]) {
            if(target > nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else if(target == nums[left]) {
                return left;
            } else {
                left = mid + 1;
            }
        } else {
            if(target < nums[right] && target > nums[mid]) {
                left = mid + 1;
            } else if(target == nums[right]) {
                return right;
            } else {
                right = mid - 1;
            }
        }
    }
    if(nums[left] == target) return left;
    return -1;
}

int main() {
    return 0;
}