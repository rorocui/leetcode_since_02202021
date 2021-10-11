struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* new = NULL;

    if(!l1 && !l2) return new;

    if(!l1) return l2;
    if(!l2) return l1;

    if(l1->val < l2->val)
    {
        new = l1;
        l1->next = mergeTwoLists(l1->next, l2)
    }
    else
    {
        new = l2;
        l2->next = mergeTwoLists(l1, l2->next);
    }

    return new;
}
/* 208 - 8(<15%) - 6.3MB, on Oct 10th, 2021 */
