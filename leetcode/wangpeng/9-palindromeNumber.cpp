/********************************************************************************** 
* 
* Determine whether an integer is a palindrome. Do this without extra space.
* 
* 
* Some hints:
* 
* Could negative integers be palindromes? (ie, -1)
* 
* If you are thinking of converting the integer to string, note the restriction of using extra space.
* 
* You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", 
* you know that the reversed integer might overflow. How would you handle such case?
* 
* There is a more generic way of solving this problem.
* 
*               
**********************************************************************************/

#include <iostream>
#include <limits>

using namespace std;

int reverse(int x) {
    int imax = numeric_limits<int>::max();
    int result = 0;
    int tmp = x;
    while(tmp > 0) {
        if(result > imax/10) return x-1;
        result = result * 10 + tmp%10;
        tmp = tmp/10;
    }
    return result;
}

bool isPalindrome(int x) {
    if(x < 0) return false;
    if(x < 10) return true;
    return reverse(x) == x;
}

int main() {
    return 0;
}