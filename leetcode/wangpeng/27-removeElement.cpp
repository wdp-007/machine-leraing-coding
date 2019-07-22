/********************************************************************************** 
* 
* Given an array and a value, remove all instances of that value in place and return the new length.
* 
* The order of elements can be changed. It doesn't matter what you leave beyond the new length.
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int val) {
    if(nums.size() <= 0) return 0;
    int left = -1;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] != val) {
            left += 1;
            nums[left] = nums[i];
        }
    } 
    return left + 1;
}

int main() {
    return 0;
}