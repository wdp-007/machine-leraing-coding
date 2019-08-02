/********************************************************************************** 
* 
* The set [1,2,3,…,n] contains a total of n! unique permutations.
* 
* By listing and labeling all of the permutations in order,
* We get the following sequence (ie, for n = 3):
* 
* "123"
* "132"
* "213"
* "231"
* "312"
* "321"
* 
* Given n and k, return the kth permutation sequence.
* 
* Note: Given n will be between 1 and 9 inclusive.
*               
**********************************************************************************/
#include <iostream>
#include <vector>
using namespace std;


string getPermutation(int n, int k) {
    if(n <= 0) return "";
    if(n == 1) return "1";
    string result = "";
    vector<int> pSum(n, 0);
    vector<int> usedIndex(n, 0);
    pSum[n-1] = 1;
    for(int i = n-2; i > -1; i--) {
        pSum[i] = -1*(i-n) * pSum[i+1];
    }

    for(int i = 0; i < n-1; i++) {
        int quo = k/pSum[i+1];
        int remain = k%pSum[i+1];
        if(remain == 0) {
            quo = quo - 1;
            remain = pSum[i+1];
        } 
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(usedIndex[i] == 0) cnt++;
            if(cnt == quo+1) {
                result[i] = (i+1) + '0';
                break;
            }
        }
    }

    return result;
}

int main() {
    string s = getPermutation(4, 1);
    cout << s << endl;
    return 0;
}