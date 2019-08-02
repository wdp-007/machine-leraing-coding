/********************************************************************************** 
* 
* Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
* 
* For example,
* Given n = 3,
* 
* You should return the following matrix:
* 
* [
*  [ 1, 2, 3 ],
*  [ 8, 9, 4 ],
*  [ 7, 6, 5 ]
* ]
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<vector<int> >& result, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int> > generateMatrix(int n) {
    vector<vector<int> > result(n, vector<int>(n));
    if(n <= 0) return result;
    if(n == 1) {
        result[0][0] = 1;
        return result;
    } 
    int leftX = 0;
    int leftY = 0;
    int rightX = n-1;
    int rightY = n-1;
    int cnt = 1;
    while(leftX <= rightX) {

        if(leftX == rightY) {
            result[leftX][leftY] = cnt;
            break;
        }

        for(int i = leftY; i < rightY; i++) {
            result[leftX][i] = cnt;
            cnt++;
        }
        for(int i = leftX; i < rightX; i++) {
            result[i][rightY] = cnt;
            cnt++;
        }
        for(int i = rightY; i > leftY; i--) {
            result[rightX][i] = cnt;
            cnt++;
        }
        for(int i = rightX; i > leftX; i--) {
            result[i][leftY] = cnt;
            cnt++;
        }
        leftX++;
        leftY++;
        rightX--;
        rightY--;
    }
    return result;
}

int main() {
    vector<vector<int> > result = generateMatrix(3);
    return 0;
}