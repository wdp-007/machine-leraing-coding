/********************************************************************************** 
* 
* Reverse digits of an integer.
* 
* Example1: x =  123, return  321
* Example2: x = -123, return -321
* 
* 
* Have you thought about this?
* 
* Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
* 
* > If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
* 
* > Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, 
*   then the reverse of 1000000003 overflows. How should you handle such cases?
* 
* > Throw an exception? Good, but what if throwing an exception is not an option? 
*   You would then have to re-design the function (ie, add an extra parameter).
* 
*               
**********************************************************************************/

#include <iostream>
#include <string>
#include <limits>

using namespace std;


int reverse(int x) {
    int imax = numeric_limits<int>::max();
    int imin = numeric_limits<int>::min();
    if(x < 10 && x > -10) return x;
    int result = 0;
    int tmp = x;
    while(tmp != 0) {
        cout << result << endl;
        if(result > (imax/10) || result < (imin/10)) return 0;
        result = result*10 + tmp%10;
        tmp = tmp/10;
    }
    return result;
}

int main() {
    int x= -2147483412;
    int result= reverse(x);
    return 0;
}