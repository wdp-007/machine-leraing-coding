/********************************************************************************** 
* 
* Given n non-negative integers representing an elevation map where the width of each bar is 1, 
* compute how much water it is able to trap after raining. 
* 
* For example, 
* Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*   
*     ^                                             
*     |                                             
*   3 |                       +--+                  
*     |                       |  |                  
*   2 |          +--+xxxxxxxxx|  +--+xx+--+         
*     |          |  |xxxxxxxxx|  |  |xx|  |         
*   1 |   +--+xxx|  +--+xxx+--+  |  +--+  +--+      
*     |   |  |xxx|  |  |xxx|  |  |  |  |  |  |      
*   0 +---+--+---+--+--+---+--+--+--+--+--+--+----->
*       0  1   0  2  1   0  1  3  2  1  2  1        
* 
* The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 
* 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int trap(vector<int>& height) {
    int result = 0;
    if(height.size() <= 2) return 0;
    int max_hight = 0;
    int max_index = 0;
    for(int i = 0; i < height.size(); i++) {
        if(height[i] >= max_hight) {
            max_index = i;
            max_hight = height[i];
        }
    }

    //从左往右
    int left = 0;
    while(height[left] == 0 && left < height.size()) {
        left++;
    }
    if(left >= height.size()-2) return 0;
    int right = left + 1;
    int sum = 0;
    while(left <= max_index-1 && right <= max_index) {
        if(height[right] >= height[left]) {
            int area = (right -left -1) * height[left] - sum;
            result += area;
            sum = 0;
            left = right;
            right = left+1;
        } else {
            sum += height[right];
            right++;
        }
        cout << "left:" << left << "  right:" << right << "  result:" << result << endl;
    }

    //从右往左
    right = height.size()-1;
    while(height[right] == 0 && right >= 0) {
        right--;
    }
    if(right <= 1) return 0;
    left = right - 1;
    sum = 0;
    while(left >= max_index && right > max_index) {
        if(height[left] >= height[right]) {
            int area = (right -left -1) * height[right] - sum;
            result += area;
            sum = 0;
            right = left;
            left = right - 1;
        } else {
            sum += height[left];
            left--;
        }
        cout << "left:" << left << "  right:" << right << "  result1:" << result << endl;
    }
    return result;
}

int main() {
    vector<int> arr{4,2,3};
    trap(arr);
    return 0;
}