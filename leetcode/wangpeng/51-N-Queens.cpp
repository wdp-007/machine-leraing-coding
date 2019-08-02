/******************************
 * 
 The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
*********************************/

#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<vector<string> >& result, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

void printString(vector<string>& result, int n) {
    for(int i = 0; i < n; i++) {
        cout << result[i] << endl;
    }
}

bool helper(vector<vector<string> >& result, int index, int n, vector<string>& tmp, vector<int>& row, vector<int>& col, vector<int>& slash1, vector<int>& slash2) {
    if(index >= n) {
        vector<string> ans(tmp);
        result.push_back(ans);
        printString(ans, 4);
        return true;
    }
    cout << index << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(row[i] == 0 && col[j] == 0 && slash1[i+j] == 0 && slash2[j-i+n-1] == 0) {
                row[i] = 1;
                col[j] = 1;
                slash1[i+j] = 1;
                slash2[j-i+n-1] = 1;
                tmp[i][j] = 'Q';
                cout << index << endl;
                //printVector(tmp, 4);
                if(!helper(result, index+1, n, tmp, row, col, slash1, slash2)) return false;
                row[i] = 0;
                col[j] = 0;
                slash1[i+j] = 0;
                slash2[j-i+n-1] = 0;
                tmp[i][j] = '.';          
            }
        }
    }
    return false;
}

vector<vector<string> > solveNQueens(int n) {
    //vector<vector<string> > result(n, vector<string>(n, "."));
    vector<vector<string> > result;
    if(n <= 0) return result;
    if(n == 1) {
        vector<string> tmp{"Q"};
        result.push_back(tmp);
        return result;
    }
    vector<int> row(n, 0);
    vector<int> col(n, 0);
    vector<int> slash1(2*n - 1, 0); 
    vector<int> slash2(2*n - 1, 0);
    vector<string> cur(n, ".");
    helper(result, 0, n, cur, row, col, slash1, slash2);
    // vector<vector<string> > last;
    // for(int i = 0; i < n; i++) {
    //     vector<string> tmp;
    //     for(int j = 0; j < n; j++) {
    //         tmp.push_back(result[i][j]);
    //     }
    //     last.push_back(tmp);
    // }
    return result;
}



int main() {
    vector<vector<string> > result = solveNQueens(4);
    cout << endl;
    printVector(result, 4);
    return 0;
}