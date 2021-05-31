
typedef struct {
    int val;
    struct struct ListNode* next;   
} struct ListNode;

/** Initialize your data structure here. */

struct ListNode* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    struct ListNode* new = NULL;
    new = (struct ListNode*)malloc(sizeof(struct ListNode));
    new->val = -1;
    new->next = NULL;
    return new; 
}

bool EmptyList(struct ListNode* obj){
    /*
    if(obj != NULL)
    {
        printf("obj(0x%lx)->val=%d\n", obj, obj->val);
    }
    else
        printf("NULL obj\n");
    */ 
    if(obj == NULL || obj == 0xbebebebebebebebe || obj->val == -1 /* || obj == obj->next */)
    {
        //printf("+");
        return true;
    }
    else
    {
        return false;
        //printf("-");
        //printf("\n[0x%x]=%d\n", obj, obj->val);
    }
}

void printMyList(struct ListNode* obj) {
    /*
    struct ListNode* ptr = NULL;
    int i = 0; 
    
    //printf("print-0x%lx, %d\n", obj, obj->val);
    if(! EmptyList(obj))
    {
        ptr = obj;
        printf("[");
        while(! EmptyList(ptr->next))
        {
            if(i < 5)
                printf("%d->", ptr->val);
            //else
            //    printf(".");
            i++;
            ptr = ptr->next;
        }
        printf("%d(%d)]\n",ptr->val, ++i);
    }   
    else
        printf("empty list\n");
    */
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(struct ListNode* obj, int val) {    
    //printf("%s:obj=0x%lx, val=%d\n", __FUNCTION__, obj, val);
    //printMyList(obj);
    struct ListNode* head = NULL;
    head = myLinkedListCreate();
    head->val = obj->val;
    head->next = obj->next;
    obj->val = val;
    obj->next = head;    
    printMyList(obj);
    //printf("#################obj=0x%lx#############\n\n", obj);  
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(struct ListNode* obj, int val) {
    //printf("%s:obj=0x%lx, val=%d\n", __FUNCTION__, obj, val);
    printMyList(obj);
    struct ListNode* end = NULL;
    struct ListNode* ptr = NULL;

    
    if(! EmptyList(obj))
    {
        end = myLinkedListCreate();
        end->val = val;
        end->next = NULL;
        ptr = obj;
        while(! EmptyList(ptr->next))
        {
            ptr = ptr->next;    
        }
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        
    }
    printMyList(obj);
    //printf("#################obj=0x%lx#############\n\n", obj);  
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(struct ListNode* obj, int index, int val) {
    //printf("%s:obj=0x%lx, val=%d, index=%d\n", __FUNCTION__, obj, val, index);
    printMyList(obj);
    struct ListNode* ptr = NULL;
    struct ListNode* new = NULL;
    int i;
    if( index == 0 )
            myLinkedListAddAtHead(obj, val);
    else
    {
        new = myLinkedListCreate();
        new->val = val;
        if(!EmptyList(obj))
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(!EmptyList(ptr->next))
                {
                    ptr = ptr->next;
                    i++;
                }
                else
                    break;
            }
            printf("i=%d\n", i);
            if(i == index - 1)
            {
                if(!EmptyList(ptr->next)) new->next = ptr->next;
                ptr->next = new;
            } 
        }
    }
    
    
    printMyList(obj);
    //printf("#################obj=0x%lx#############\n\n", obj);  
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(struct ListNode* obj, int index) {
    //printf("%s:obj=0x%lx, index=%d\n", __FUNCTION__, obj, index);
    printMyList(obj);
    struct ListNode* ptr = NULL;
    struct ListNode* temp = NULL;
    int i;
    
    if(!EmptyList(obj))
    {
        if(index > 0)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(!EmptyList(ptr->next))
                {
                    ptr = ptr->next;
                    i++;
                }
                else
                    break;
            }
            //printf("i=%d\n", i);
            if(i == index - 1)
            {
                if(!EmptyList(ptr->next))
                {
                    temp = ptr->next;
                    ptr->next = temp->next;
                }
                free(temp);
            }
        }
        else
        {
            ptr = obj->next;
            obj->next = ptr->next;
            obj->val = ptr->val;
        }
    }
    printMyList(obj);
    //printf("#################obj=0x%lx#############\n\n", obj);  
  
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(struct ListNode* obj, int index) {
    //printf("%s:obj=0x%lx, index=%d\n", __FUNCTION__, obj, index);
    printMyList(obj);
    struct ListNode* ptr = NULL;
    //struct ListNode* temp = NULL;
    int i;
    
    if(! EmptyList(obj))
        ptr = obj;
    else
        return -1;
    for(i = 0; i < index;)
    {
        if(! EmptyList(ptr->next))
        {
            ptr = ptr->next;
            i++;
        }
        else
            break;
    }
    //printf("i=%d\n", i);
    if(i == index && !EmptyList(ptr))
    {
        //printf("#################obj=0x%lx(%d)#############\n\n", obj, ptr->val);  
        return ptr->val;
    }
    else
    {
        //printf("#################obj=0x%lx#############\n\n", obj);  
        return -1;   
    }
}

void myLinkedListFree(struct ListNode* obj) {
    //printf("%s\n", __FUNCTION__);
    struct ListNode* ptr = NULL;
    
    while(!EmptyList(obj->next))
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);
    
}

/**
 * Your struct ListNode struct will be instantiated and called as such:
 * struct ListNode* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
    irintf("i=%d\n", i);
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/

/* 59 cases in 40ms, beats 86.67% on March 6th, 2021 */
