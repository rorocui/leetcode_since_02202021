/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head){
    /* O(n^2) 
    struct ListNode *endPtr = NULL;
    struct ListNode *searchPtr = NULL;
    struct ListNode *newhead = NULL;

    if( !head || !head->next) return head;
    
    endPtr = head;
    searchPtr = head;
    while(endPtr->next) endPtr = endPtr->next;
    newhead = endPtr;
    //printf("end=%d\n", endPtr->val);
    while(endPtr != head)
    {
        while(searchPtr->next != endPtr) searchPtr = searchPtr->next;
        //printf("search=%d\n", searchPtr->val);
        endPtr->next = searchPtr;
        endPtr = searchPtr;
        searchPtr = head;
        //printf("head=%d\n", head->val);
    }
    head->next = NULL;
    return newhead;
    28 cases in 28ms on March 9th, 2021 */
    
    /* O(n) */
    struct ListNode *prevPtr = NULL;
    struct ListNode *currPtr = NULL;
    struct ListNode *nextPtr = NULL;
    
    if( !head || !head->next) return head;
    currPtr = head;
    nextPtr = head->next;
    while(currPtr)
    {
        //printf("%lx,%lx,%lx\n", prevPtr, currPtr, nextPtr);
        currPtr->next = prevPtr;
        prevPtr = currPtr;
        currPtr = nextPtr;
        if(currPtr) nextPtr = currPtr->next;
    }
    head = prevPtr;
    return head;
    /* 28 cases in 4ms, beats 84.79% on March 9th, 2021 */
}
