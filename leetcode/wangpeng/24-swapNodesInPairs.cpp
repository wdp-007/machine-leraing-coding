/********************************************************************************** 
* 
* Given a linked list, swap every two adjacent nodes and return its head.
* 
* For example,
* Given 1->2->3->4, you should return the list as 2->1->4->3.
* 
* Your algorithm should use only constant space. You may not modify the values in the list, 
* only nodes itself can be changed.
* 
*               
**********************************************************************************/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr) {}
};

void printNode(ListNode* head, ListNode* tail) {
    while(head != tail) {
        cout << head -> val ;
        head = head -> next;
    }
    if(tail) cout << tail -> val;
    cout << endl;
}

ListNode* reverseKNodes(ListNode* head, ListNode* tail) {
    ListNode* pre = head;
    ListNode* cur = head -> next;
    pre -> next = nullptr;
    while(cur != tail) {
        ListNode* tmp = cur -> next;
        cur -> next = pre;
        pre = cur;
        cur = tmp;
    }
    tail -> next = pre;
    printNode(tail, nullptr);
    return tail;
}

ListNode* swapPairs(ListNode* head) {
    if(!head || !head->next) return head;
    int k = 1;
    ListNode* newHead = nullptr;
    ListNode* preTail = nullptr;
    ListNode* begin = head;
    ListNode* cur = head;
    int i = 0;
    while(cur) {
        i++;
        //cout << "i: " << i << endl;
        //cout << "cur: " << cur -> val << endl;
        ListNode* next = cur->next;
        if(i == k) {
            //ListNode* newEnd = cur;
            ListNode* newBegin = reverseKNodes(begin, cur);
            if(!newHead) newHead = newBegin;
            if(preTail) preTail -> next = newBegin;
            //newEnd -> next = nullptr;
            preTail = begin;
            begin = next;
            i = 0;
        }
        cur = next;
        
    }
    if(preTail) preTail -> next = begin;
    printNode(newHead, nullptr);
    return newHead;
}

int main() {
    ListNode* l1 = new ListNode(1);
    l1 -> next = new ListNode(2);
    l1 -> next -> next = new ListNode(3);
    l1 -> next -> next -> next = new ListNode(4);
    // l1 -> next -> next -> next -> next = new ListNode(5);
    //l1 -> next -> next -> next -> next -> next = new ListNode(6);
    ListNode* head = swapPairs(l1);
    printNode(head, nullptr);
    return 0;
}