/********************************************************************************** 
* 
* Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
* 
* If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
* 
* You may not alter the values in the nodes, only nodes itself may be changed.
* 
* Only constant memory is allowed.
* 
* For example,
* Given this linked list: 1->2->3->4->5
* 
* For k = 2, you should return: 2->1->4->3->5
* 
* For k = 3, you should return: 3->2->1->4->5
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
    while(cur && cur != tail) {
        ListNode* tmp = cur -> next;
        cur -> next = pre;
        pre = cur;
        cur = tmp;
    }
    tail -> next = pre;
    printNode(tail, nullptr);
    return tail;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || !head->next || k == 1) return head;
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
    if(newHead) return newHead;
    return head; // k的长度大于链表的长度
}

int main() {
    ListNode* l1 = new ListNode(1);
    l1 -> next = new ListNode(2);
    l1 -> next -> next = new ListNode(3);
    l1 -> next -> next -> next = new ListNode(4);
    l1 -> next -> next -> next -> next = new ListNode(5);
    //l1 -> next -> next -> next -> next -> next = new ListNode(6);
    ListNode* head = reverseKGroup(l1, 2);
    printNode(head, nullptr);
    return 0;
}