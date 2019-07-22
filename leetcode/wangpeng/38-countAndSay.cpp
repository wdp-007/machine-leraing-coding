/********************************************************************************** 
* 
* The count-and-say sequence is the sequence of integers beginning as follows:
* 1, 11, 21, 1211, 111221, ...
* 
* 1 is read off as "one 1" or 11.
* 11 is read off as "two 1s" or 21.
* 21 is read off as "one 2, then one 1" or 1211.
* 
* Given an integer n, generate the nth sequence.
* 
* Note: The sequence of integers will be represented as a string.
* 
*               
**********************************************************************************/

#include <iostream>


using namespace std;

string countAndSay(int n) {
    if(n == 1) return "1";
    string cur = "1";
    string next = "";
    for(int j = 2; j <= n; j++) {
        next = "";
        int count = 1;
        for(int i = 1; i < cur.size(); i++) {
            if(cur[i] != cur[i-1]) {
                next += to_string(count);
                next += cur[i-1];
                count = 1;
            } else {
                count++;
            }
        }
        next += to_string(count);
        next += cur[cur.size()-1];
        cur = next;
    }

    return cur;
}

int main() {
    string result = countAndSay(4);
    cout << result << endl;
    return 0;
}