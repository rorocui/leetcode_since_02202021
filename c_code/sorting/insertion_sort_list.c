/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/* Search the sorted linked list from head, and insert the new one before the node, 
 * whose value is bigger than new's one */
struct ListNode* insertANodeInList(struct ListNode* head, struct ListNode* new){
    struct ListNode* p_insert_position = NULL;
    /* Checking NULL pointer of new outside of this function */

    p_insert_position = head;
    while( p_insert_position &&
            p_insert_position->val < new->val) {
        //printf("p_position->val=%d\n", p_insert_position->val);
        if(p_insert_position->next && p_insert_position->next->val < new->val) 
            p_insert_position = p_insert_position->next;
        else    
            break;
    }
    if(p_insert_position == head && head->val > new->val) {
        // Replace head with new node p_insert_position 
        new->next = head;
        head = new;
    }
    else {
        //printf("new=%d, p_i=%d\n", new->val, p_insert_position->val);
        new->next = p_insert_position->next;
        p_insert_position->next = new;
    }

    return head;
}
void print_list(struct ListNode* head){
    struct ListNode* temp = head;
    while(temp){
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");

}

struct ListNode* insertionSortList(struct ListNode* head){
    struct ListNode* p1 = NULL;
    struct ListNode* p_insert_element = NULL;

    p1 = head->next;
    /* Divide linked list to 2 parts, first has only  head
     * Second part has the left nodes */
    head->next = NULL;
    while(p1) {
        //printf("p1->val=%d\n", p1->val);
        p_insert_element = p1;
        p1 = p1->next;
        p_insert_element->next = NULL;
        head = insertANodeInList(head, p_insert_element);
        //print_list(head);
    }
    return head;
}
/* beat 62% on Sep 20th, 2022 */
