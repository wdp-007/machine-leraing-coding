/********************************************************************************** 
* 
* Write a program to solve a Sudoku puzzle by filling the empty cells.
* 
* Empty cells are indicated by the character '.'.
* 
* You may assume that there will be only one unique solution.
* 
* A sudoku puzzle...
* 
* ...and its solution numbers marked in red.
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int arr1[9][9] = {0};
int arr2[9][9] = {0};
int arr3[9][9] = {0};

bool getResult(int i, int j, vector<vector<char> >& board) {
    if(j >= 9 && i >= 9) return true;
    if(j >= 9) {
        i++;
        j = 0;
    }
    if(board[i][j] != '.') return getResult(i, j+1, board); 
    int k = i/3 * 3 + j/3;
    for(int x = 0; x < 9; x++) {
        if(arr1[i][x] || arr2[j][x] || arr3[k][x]) continue;
        arr1[i][x] = 1;
        arr2[j][x] = 1;
        arr3[k][x] = 1;
        board[i][j] = x + '1';
        if(getResult(i, j+1, board)) return true;
        arr1[i][x] = 0;
        arr2[j][x] = 0;
        arr3[k][x] = 0;
        board[i][j] = '.';         
    }
    return false;
}

void solveSudoku(vector<vector<char> >& board) {

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(board[i][j] != '.') {
                int k = i/3 * 3 + j/3;
                int num = board[i][j] - '0' - 1;
                arr1[i][num] = 1;
                arr2[j][num] = 1;
                arr3[k][num] = 1;
            }
        }
    }
    getResult(0, 0, board);
}

int main() {
    return 0;
}