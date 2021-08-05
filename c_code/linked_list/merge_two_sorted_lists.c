/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *l1ptr = NULL; 
    struct ListNode *l1Prevptr = NULL; 
    struct ListNode *l2ptr = NULL; 
    struct ListNode *tmptr = NULL; 
    
    if(!l1) return l2;
    if(!l2) return l1;
    l1ptr = l1;
    l2ptr = l2;
    while(l1ptr && l2ptr)
    {
        if(l2ptr->val < l1ptr->val)
        {
            if(l1Prevptr)
            {
                l1Prevptr->next = l2ptr;
                l1Prevptr = l2ptr;
                l2ptr = l2ptr->next;
                l1Prevptr->next = l1ptr;
            }
            else /* first node of l2 is less than first node of l1 */
            {
                l1 = l1Prevptr = l2ptr;
                l2ptr = l2ptr->next;
                l1Prevptr->next = l1ptr;
            }
        }
        else
        {
            l1Prevptr = l1ptr;
            l1ptr = l1ptr->next;
        }
    }
    /* add left nodes of l2ptr to end of l1 */
    if(!l1ptr) l1Prevptr->next = l2ptr;
    return l1;
    /* 208 cases in 4ms, beats 84.81% on March 15th, 2021 */
}
