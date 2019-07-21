/********************************************************************************** 
* 
* You are given an n x n 2D matrix representing an image.
* Rotate the image by 90 degrees (clockwise).
* Follow up:
* Could you do this in-place?
*               
**********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void rotate(vector<vector<int> >& matrix) {
    int n = matrix.size();
    if(n <= 1) return;
    int leftX = 0;
    int leftY = 0;
    int rightX = n-1;
    int rightY = n-1;
    while(leftX < rightX) {
        for(int i = 0; i + leftY < rightY; i++) {
            int tmp = matrix[leftX][leftY+i];
            matrix[leftX][leftY+i] = matrix[rightX-i][leftY];
            matrix[rightX-i][leftY] = matrix[rightX][rightY-i];
            matrix[rightX][rightY-i] = matrix[leftX+i][rightY];
            matrix[leftX+i][rightY] = tmp;
        }
        leftX++;
        leftY++;
        rightX--;
        rightY--;
    }
}