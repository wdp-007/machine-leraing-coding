/********************************************************************************** 
* 
* Divide two integers without using multiplication, division and mod operator.
* 
* If it is overflow, return MAX_INT. 
*
**********************************************************************************/
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

int divide(int dividend, int divisor) {
    int imax = numeric_limits<int>::max();
    int imin = numeric_limits<int>::min();
    if(divisor == 1) return dividend;
    if(dividend == imin && divisor == -1) return numeric_limits<int>::max();
    if(divisor == -1) return -dividend;
    if(dividend == 0) return 0;
    int symbol = 1;
    if((divisor > 0 && dividend < 0) || (divisor < 0 && dividend > 0)) symbol = -1;
    long a = abs((long)dividend);
    long b = abs((long)divisor);
    int result = 0;
    while(a >= b) {
        int cnt = 0;
        long tmp = 0;
        while(tmp < a) {
            cnt++;
            tmp = b << cnt;
            cout << "tmp: " << tmp << " cnt:" << cnt << endl;
        }
        result += (1 << (cnt - 1));
        a -= (b << (cnt-1)); 
        cout << "result: " << result << " dividend:" << a << endl;
    }
    if(symbol == -1) return -result;
    return result;
}

int main() {
    int result = divide(2147483647, 2);
    cout << result << endl;
    return 0;
}