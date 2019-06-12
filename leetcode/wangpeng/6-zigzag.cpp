/********************************************************************************** 
* 
* The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
* (you may want to display this pattern in a fixed font for better legibility)
* 
* P   A   H   N
* A P L S I I G
* Y   I   R
* 
* And then read line by line: "PAHNAPLSIIGYIR"
* 
* Write the code that will take a string and make this conversion given a number of rows:
* 
* string convert(string text, int nRows);
* 
* convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
* 
*               PAHNAPLSIIGYIR
**********************************************************************************/

#include <iostream>
#include <string>

using namespace std;

string convert(string s, int numRows) {
    if(s.empty() || s.size() <= 1) return s;
    if(numRows <= 1) return s;
    string result = "";

    int step1 = 2 * (numRows - 1);
    for(int i = 1; i < numRows+1; i++) {
        if(i == 1 || i == numRows) {
            int cur = i - 1;
            while(cur < s.size()) {
                result += s[cur];
                cur += step1;
            }
        } else {
            int cur = i - 1;
            int step2 = 2 * (numRows - 1) - 2*(i-1);
            while(cur < s.size()) {
                result += s[cur];
                if((cur + step2) < s.size()) result += s[cur + step2];
                cur += step1;
            }
        }
    }
    return result;
}

int main() {
    string result = convert("PAYPALISHIRING", 4);
    cout << result << endl;
    return  0;
}