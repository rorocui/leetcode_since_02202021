/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head)
{
    struct ListNode* top = NULL;
    struct ListNode* bottom = NULL;
    struct ListNode* pre_bottom = NULL;
    
    /* handle null list, and 1 onde list */
    if(!head || !head->next) return head;
    top = head;
    bottom = head->next;
    if(bottom->next)
    {
       while(bottom->next)
       {
           pre_bottom = bottom;
           bottom = bottom->next; 
       }
       pre_bottom->next = NULL;
       bottom->next = reverseList(head->next);
       pre_bottom = top->next;
       while(pre_bottom->next)
           pre_bottom = pre_bottom->next;
       top->next = NULL;
       pre_bottom->next = top;
    }
    else /* handle 2 nodes list */
    {
        bottom->next = top;
        top->next = NULL; 
    }
    
    return bottom;
}
/* 28 test cases in 28ms, in 6.4MB on May 29th, 2021 */
