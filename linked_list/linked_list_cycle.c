
bool hasCycle(struct ListNode *head) {
    struct ListNode *slowPtr = NULL;
    struct ListNode *fastPtr = NULL;
    
    if(EmptyList(head)) return false;
    
    slowPtr = head;
    fastPtr = head;
    while(!EmptyList(fastPtr->next))
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next;
        if(EmptyList(fastPtr->next))
        {
            return false;
        }
        else
            fastPtr = fastPtr->next;
        if(slowPtr == fastPtr) return true;
    }
    return false;
    /* 19 cases in 8ms, beats 84.48% on March 6th, 2021*/
    
    /*
    struct ListNode *slowPtr = NULL;
    struct ListNode *fastPtr = NULL;
    
    if(EmptyList(head)) return false;
    
    slowPtr = head;
    fastPtr = head;
    while(fastPtr->next != NULL)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next;
        if(fastPtr->next == NULL)
        {
            return false;
        }
        else
            fastPtr = fastPtr->next;
        if(slowPtr == fastPtr) return true;
    }
    return false;
    */
    /* 19 cases in 12ms, beats 28.46% on March 6th, 2021 */
}
