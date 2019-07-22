/********************************************************************************** 
* 
* Given a sorted array, remove the duplicates in place such that each element appear 
* only once and return the new length.
* 
* Do not allocate extra space for another array, you must do this in place with constant memory.
* 
* For example,
* Given input array A = [1,1,2],
* 
* Your function should return length = 2, and A is now [1,2].
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates1(vector<int>& nums) {
    if(nums.size() < 2) return nums.size();
    int left = 1;
    int right = nums.size() - 1;
    while(left < right) {
        cout << "left: " << left << " right: " << right << endl;
        if(nums[left] == nums[left - 1]) {
            int tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;
            right--;
        } else {
            left++;
        }
    } 
    cout << "final left: " << left << endl;
    if(nums[left] == nums[left - 1]) return left;
    return left + 1;
}

int removeDuplicates(vector<int>& nums) {
    if(nums.size() < 2) return nums.size();
    int left = 1;
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] != nums[i-1]) {
            nums[left] = nums[i];
            left++;
        }
    }
    cout << "final left: " << left << endl;
    return left;
}

int main() {
    vector<int> nums{0,0,1,1,1,2,2,3,3,4};
    removeDuplicates(nums);
    return 0;
}