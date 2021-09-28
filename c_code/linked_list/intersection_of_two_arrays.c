/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    int countA = 0, countB = 0, i = 0; 
    struct ListNode *Aptr = NULL;
    struct ListNode *Bptr = NULL;
    
    Aptr = headA;
    Bptr = headB;
    while(Aptr != NULL)         
    {
        countA++;
        Aptr = Aptr->next;
    }
    
    while(Bptr != NULL)         
    {
        countB++;
        Bptr = Bptr->next;
    }
    
    if(countA != 0 && countB != 0)
    {
        Aptr = headA;
        Bptr = headB;
        if(countA > countB)
            for(i = 0; i < (countA - countB); i++)
                Aptr = Aptr->next;    
        else
            for(i = 0; i < (countB - countA); i++)
                Bptr = Bptr->next;
        for(i = 0; i< countA; i++)
        {
            if(Aptr == Bptr) return Aptr;
            Aptr = Aptr->next;
            Bptr = Bptr->next;
            //printf("0x%lx=0x%lx\n", Aptr, Bptr);
        }
    }
    return NULL;
     
}
/* 16 - 9(<29%) - 7.1MB, on Sep 20th, 2021 */
