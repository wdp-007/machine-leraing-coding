/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
};

ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    ListNode *new_head = new ListNode();
    ListNode *tail = new_head;
    ListNode *h1 = l1;
    ListNode *h2 = l2;
    int carry = 0;
    while(h1 || h2 ) {
        int x = h1 ? h1 -> val : 0;
        int y = h2 ? h2 -> val : 0;
        
    }
} 

int main() {
    return 0;
}