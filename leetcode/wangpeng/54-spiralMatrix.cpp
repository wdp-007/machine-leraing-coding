/********************************************************************************** 
* 
* Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
* 
* For example,
* Given the following matrix:
* 
* [
*  [ 1, 2, 3 ],
*  [ 4, 5, 6 ],
*  [ 7, 8, 9 ]
* ]
* 
* You should return [1,2,3,6,9,8,7,4,5].
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>
using namespace std;


vector<int> spiralOrder(vector<vector<int> >& matrix) {
    vector<int> result;
    if(matrix.size() <= 0) return result;
    int m = matrix.size();
    int n = matrix[0].size();
    //if(m == 1) return  
    int topX = 0;
    int topY = 0;
    int bootX = m-1;
    int bootY = n-1;
    while(topX <= bootX && topY <= bootY) {
        if(topX == bootX) {
            for(int i = topY; i <= bootY; i++) {
                result.push_back(matrix[topX][i]);
            }
        } else if(topY == bootY) {
            for(int i = topX; i <= bootX; i++) {
                result.push_back(matrix[i][topY]);
            }
        } else {
            for(int i = topY; i < bootY; i++) {
                result.push_back(matrix[topX][i]);
            }
            for(int i = topX; i < bootX; i++) {
                result.push_back(matrix[i][bootY]);
            }
            for(int i = bootY; i > topY; i--) {
                result.push_back(matrix[bootX][i]);
            }
            for(int i = bootX; i > topX; i--) {
                result.push_back(matrix[i][topY]);
            }
        }
        topX++;
        topY++;
        bootX--;
        bootY--;
    }
    return result;
}