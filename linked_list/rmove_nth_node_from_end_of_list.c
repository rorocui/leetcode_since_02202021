
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    
    struct ListNode *listPtrLeft = NULL;
    struct ListNode *listPtrRight = NULL;
    int i = 0;
    
    listPtrLeft = head;
    listPtrRight = head;
    for(i = 0; i < n - 1; i++)
    {
        listPtrRight = listPtrRight->next;
    }
    
    while(listPtrRight != NULL)
    {
        listPtrLeft = listPtrLeft->next;
        listPtrRight = listPtrRight->next;
    }
    
    printf("Left->next=%d\n", listPtrLeft->next->val);
    listPtrRight = listPtrLeft->next;
    listPtrLeft = listPtrRight->next;
    free(listPtrRight);
    return head;    
}
