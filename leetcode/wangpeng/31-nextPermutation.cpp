/********************************************************************************** 
* 
* Implement next permutation, which rearranges numbers into the lexicographically next 
* greater permutation of numbers.
* 
* If such arrangement is not possible, it must rearrange it as the lowest possible order 
* (ie, sorted in ascending order).
* 
* The replacement must be in-place, do not allocate extra memory.
* 
* Here are some examples. Inputs are in the left-hand column and its corresponding outputs 
* are in the right-hand column.
*
*   1,2,3 → 1,3,2
*   3,2,1 → 1,2,3
*   1,1,5 → 1,5,1
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

void reverseArray(vector<int>& nums, int start, int end) {
    while(start < end) {
        int tmp = nums[start];
        nums[start] = nums[end];
        nums[end] = tmp;
        start++;
        end--;
    }
}

void nextPermutation(vector<int>& nums) {
    if(nums.size() <= 1) return;
    if(nums.size() == 2) {
        int tmp = nums[0];
        nums[0] = nums[1];
        nums[1] = tmp;
        return;
    }
    int first_index = -1;
    for(int i = nums.size() - 2; i >= 0; i--) {
        if(nums[i] < nums[i+1]) {
            first_index = i;
            break;
        }
    }
    if(first_index == -1) {
        reverseArray(nums, 0, nums.size()-1);
        return;
    }
    for(int i = nums.size() - 1; i >= 0; i--) {
        if(nums[i] > nums[first_index]) {
            int tmp = nums[first_index];
            nums[first_index] = nums[i];
            nums[i] = tmp;
            break;
        }
    }
    reverseArray(nums, first_index+1, nums.size()-1);
}

int main() {
    return 0;
}
