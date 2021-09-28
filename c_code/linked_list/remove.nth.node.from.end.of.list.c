/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    struct ListNode *listPtrLeft = NULL;
    struct ListNode *listPtrRight = NULL;
    struct ListNode *listPtrTemp = NULL;
    int i = 0, listLength = 1;
    
    listPtrLeft = head;
    while(listPtrLeft->next != NULL)
    {
        listLength++;
        listPtrRight = listPtrLeft->next;
        if(listPtrRight->next != NULL)
        {
            listPtrLeft = listPtrLeft->next;
        }
        else
        {
            break;
        }
    }
    //printf("list length=%d,listPtrLeft=%d\n", listLength, listPtrLeft->val);
    if(n == 1)
    {
        if(listPtrLeft == head && listPtrLeft->next == NULL)
        {
            if(head != NULL) free(head);
            head = NULL;
        }
        else
        {
            if(listPtrLeft->next != NULL) free(listPtrLeft->next);
            listPtrLeft->next = NULL;
        }
        return head;
    }
    if(listLength == n)
    {
        listPtrLeft = head->next;
        head->next = listPtrLeft->next; 
        head->val = listPtrLeft->val;
        if(listPtrLeft != NULL) free(listPtrLeft);
        return head;
    }
    listPtrLeft = head;
    listPtrRight = head;
    for(i = 0; i < n - 1; i++)
    {
        //printf("for loop: L-R=%d-%d\n", listPtrLeft->val, listPtrRight->val);
        listPtrRight = listPtrRight->next;
    }
    //printf("before loop: L-R=%d-%d\n", listPtrLeft->val, listPtrRight->val);
    if(listPtrRight != NULL)
    {
        listPtrRight = listPtrRight->next;
        while(listPtrRight->next != NULL)
        {
            //printf("L-R=%d-%d\n", listPtrLeft->val, listPtrRight->val);
            listPtrLeft = listPtrLeft->next;
            listPtrRight = listPtrRight->next;
        }
    }
    listPtrTemp = listPtrLeft->next;
    listPtrLeft->next = listPtrTemp->next;
    free(listPtrTemp);       
    
    return head;    
    /* 208 cases in 6ms */
    /* 208 - 4(<55%) - 5.8MB, on Sep 21sth, 2021 */
