/********************************************************************************** 
* 
* Given a list, rotate the list to the right by k places, where k is non-negative.
* 
* For example:
* Given 1->2->3->4->5->NULL and k = 2,
* return 4->5->1->2->3->NULL.
*               
**********************************************************************************/
#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};


ListNode* rotateRight(ListNode* head, int k) {
    if(!head || !head->next || k<=0 ) return head;
    int length = 0;
    ListNode* last = head;
    while(last->next) {
        length++;
        last = last -> next;
    }
    length++;
    cout <<"length:" << length << endl;
    cout <<"last:" << last->val << endl;
    k = k%length;
    if(k == 0) return head;
    int cnt = 1;
    ListNode* pre = head;
    while(cnt < length-k) {
        cnt++;
        pre = pre -> next;
    }
    cout <<"pre:" << pre->val << endl;
    ListNode* newHead = pre -> next;
    pre -> next = nullptr;
    last -> next = head;
    return newHead;
}

int main() {
    ListNode* head = new ListNode(1);
    head -> next = new ListNode(2);
    head -> next -> next = new ListNode(3);
    head -> next -> next -> next = new ListNode(4);
    head -> next -> next -> next -> next = new ListNode(5);
    rotateRight(head, 2);
    return 0;
}