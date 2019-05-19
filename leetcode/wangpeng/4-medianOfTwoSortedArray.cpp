/********************************************************************************** 
* 
* There are two sorted arrays A and B of size m and n respectively. 
* Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int getKthOfTwoArray(vector<int> &nums1, int start1, int end1, vector<int> &nums2, int start2, int end2, int k) {
    if(start1 > end1) {
        return nums2[start2 + k -1];
    }
    if(start2 > end2) {
        return nums1[start1 + k -1];
    }
    if(k==1) {
        return nums1[start1] > nums2[start2]? nums2[start2] : nums1[start1];
    }
    int tmp = k/2;
    int imax = numeric_limits<int>::max();
    //int value1 = tmp > end1 ? imax : nums1[tmp];
    //int value2 = tmp > end2 ? imax : nums2[tmp];
    int index1 = tmp > (end1 - start1 + 1) ? (end1 - start1 + 1) : tmp;
    int index2 = tmp > (end2 - start2 + 1) ? (end2 - start2 + 1) : tmp;
    k = k - tmp;
    
    return 0;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    
}

int main() {
    return 0;
}