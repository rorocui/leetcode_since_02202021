/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *slowPtr = NULL;
    struct ListNode *fastPtr = NULL;
    struct ListNode *startPtr = NULL;

    if(head == NULL || head->next == NULL) return NULL;

    slowPtr = head;
    fastPtr = head;
    startPtr = head;

    while(fastPtr->next != NULL)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next;
        if(fastPtr->next == NULL)
        {
            return NULL;
        }
        else
            fastPtr = fastPtr->next;
        if(slowPtr == fastPtr)
            break;
    }
    if(slowPtr != fastPtr) return NULL;
    
    while(startPtr != slowPtr)
    {
        startPtr = startPtr->next;
        slowPtr = slowPtr->next;
    }
    return startPtr;
    /* 16 cases in 8ms, beats 35.03% on March 6th, 2021 */
    
}
