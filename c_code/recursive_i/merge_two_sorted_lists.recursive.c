/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


void mergeTwoListsRecursion(struct ListNode* new_l, struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* new = NULL;

    new = (struct ListNode*)malloc(sizeof(struct ListNode));
    new->next = NULL;
    new_l->next = new;
    if(!l1)
    {
        new_l->val = l2->val;
        l2 = l2->next;
    }
    else if(!l2)
    {
        new_l->val = l1->val;
        l1 = l1->next;
    }
    else if(l1->val > l2->val)
    {
        new_l->val = l2->val;
        l2 = l2->next;
    }
    else
    {
        new_l->val = l1->val;
        l1 = l1->next;
    }
    if(!l1 && !l2)
    {
        new_l->next = NULL;
        free(new);
        return;
    }
    mergeTwoListsRecursion(new_l->next, l1, l2);
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* new = NULL;
    struct ListNode* ptr = NULL;

    if(!l1 && !l2) return new;

    new = ptr = (struct ListNode*)malloc(sizeof(struct ListNode));
    new->next = NULL;
    mergeTwoListsRecursion(ptr, l1, l2);

    return new;
}

/* 208 - 4(<84%) - 6.5, on Aug 4th, 2021 */
