/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* swapPairs(struct ListNode* head){
    struct ListNode *tmp = NULL;
    
    if(! head || !head->next) return head;
    tmp = head;
    head = head->next;
    tmp->next = head->next;
    head->next = tmp;
    tmp->next = swapPairs(tmp->next);
    
    return head;
}
/* 55 test cases in 0ms, in 5.8MB, on May 29th,2021 */
