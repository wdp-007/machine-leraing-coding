/********************************************************************************** 
* 
* Merge two sorted linked lists and return it as a new list. The new list should be 
* made by splicing together the nodes of the first two lists.
*               
**********************************************************************************/

#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    ListNode* newHead = nullptr;
    if(l1 -> val < l2 -> val) {
        newHead = l1;
        l1 = l1 -> next;
    } else {
        newHead = l2;
        l2 = l2 -> next;
    }
    ListNode* tail = newHead;
    while(l1 && l2) {
        if(l1 -> val < l2 -> val) {
            tail -> next = l1;
            tail = l1;
            l1 = l1 -> next;
        } else {
            tail -> next = l2;
            tail = l2;
            l2 = l2 -> next;
        }
    }
    if(l1) tail -> next = l1;
    if(l2) tail -> next = l2;
    return newHead; 
}

int main() {
    return 0;
}