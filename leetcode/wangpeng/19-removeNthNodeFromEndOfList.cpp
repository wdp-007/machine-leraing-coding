/********************************************************************************** 
* 
* Given a linked list, remove the nth node from the end of list and return its head.
* 
* For example,
* 
*    Given linked list: 1->2->3->4->5, and n = 2.
* 
*    After removing the second node from the end, the linked list becomes 1->2->3->5.
* 
* Note:
* Given n will always be valid.
* Try to do this in one pass.
* 
*               
**********************************************************************************/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};


ListNode *removeNthFromEnd(ListNode *head, int n) {
    if(head == NULL || head->next == NULL) return NULL;
    int length = 0;
    ListNode *cur = head;
    while(cur != NULL) {
        length++;
        cur = cur -> next;
    }
    int k = n%length;
    if(k == 0) {
        return head -> next;
    }
    int tmp = 1;
    cur = head;
    while(tmp < (length - k)) {
        tmp++;
        cur = cur -> next;
    }
    ListNode *rm = cur -> next;
    cur -> next = rm -> next;
    return head;
}

int main() {
    return 0;
}