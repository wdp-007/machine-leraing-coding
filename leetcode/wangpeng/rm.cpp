#include <iostream>

using namespace std;

int revertInteger(int n) {
    int result = 0;
    while(n > 0) {
        int tmp = n % 10;
        result = result * 10 + tmp;
        n = n/10;
    }
    return result;
}

int main() {
    int result = revertInteger(321);
    cout << result << endl;
    return 0;
}