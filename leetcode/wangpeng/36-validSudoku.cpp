/********************************************************************************** 
* 
* Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
* 
* The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
* 
* A partially filled sudoku which is valid.
* 
* Note:
* > A valid Sudoku board (partially filled) is not necessarily solvable. 
*   Only the filled cells need to be validated.
* 
*               
**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

bool isValidSudoku(vector<vector<char> >& board) {
    int arr1[9][9] = {0};
    int arr2[9][9] = {0};
    int arr3[9][9] = {0};
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] == '.') continue;
            int num = board[i][j] - '0' - 1;
            int k = i/3 * 3+ j/3;
            if(arr1[i][num] || arr2[j][num] || arr3[k][num]) return false;
            arr1[i][num] = 1;
            arr2[j][num] = 1;
            arr3[k][num] = 1;
        }
    }
    return true;
}

int main() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j< 9; j++) {
            int k = i/3 * 3+ j/3;
            cout << k << " ";
        }
        cout << endl;
    }
    return 0;
}