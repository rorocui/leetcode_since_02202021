/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode* ptr = node;
    struct ListNode* pre_ptr = NULL;
    while(ptr->next)
    {
        ptr->val = ptr->next->val;
        pre_ptr = ptr;
        ptr = ptr->next;
    }
    pre_ptr->next = NULL;
    free(ptr);
}
/* 41 - 4ms(<93%) - 6.6MB, on Oct 6th, 2021 */
