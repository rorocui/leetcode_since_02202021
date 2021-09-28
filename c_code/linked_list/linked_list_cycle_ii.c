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

    startPtr = slowPtr = fastPtr = head;
    while(slowPtr && fastPtr && fastPtr->next)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if(slowPtr == fastPtr)
            break;
    }
    if(slowPtr != fastPtr) return NULL;
    printf("%d-%d\n", slowPtr->val, fastPtr->val);
    while(startPtr != slowPtr)
    {
        startPtr = startPtr->next;
        slowPtr = slowPtr->next;
    }
    return startPtr;
    
}
/* 16 cases in 4ms, beats 94.90% on March 6th, 2021 */
/* 16  - 9(<29%), on Sep 20th, 2021 */
