typedef struct {
    int val;
    struct MyLinkedList* next;   
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = -1;
    new->next = NULL;
    return new; 
}

/** Add a node of value val before the first element of the linked list. 
 * After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {    
    MyLinkedList* head = NULL;
    
    head = myLinkedListCreate();
    head->val = obj->val;
    head->next = obj->next;
    obj->val = val;
    obj->next = head;    
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    
    if(obj)
    {
        end = myLinkedListCreate();
        end->val = val;
        end->next = NULL;
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;    
        }
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        
    }
}

/** Add a node of value val before the index-th node in the linked list. 
 * If index equals to the length of linked list, the node will be appended to the end of linked list. 
 * If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* new = NULL;
    int i;
    if( index == 0 )
            myLinkedListAddAtHead(obj, val);
    else
    {
        new = myLinkedListCreate();
        new->val = val;
        if(obj)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(ptr->next)
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
                if(ptr->next) new->next = ptr->next;
                ptr->next = new;
            } 
        }
    }
    
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* temp = NULL;
    int i;
    
    if(obj)
    {
        if(index > 0)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(ptr->next)
                {
                    ptr = ptr->next;
                    i++;
                }
                else
                    break;
            }
            if(i == index - 1)
            {
                if(ptr->next)
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
  
}

/** Get the value of the index-th node in the linked list. 
 * If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    int i;
    
    if(obj)
        ptr = obj;
    else
        return -1;
    for(i = 0; i < index;)
    {
        if(ptr->next)
        {
            ptr = ptr->next;
            i++;
        }
        else
            break;
    }
    if(i == index && ptr)
    {
        return ptr->val;
    }
    else
    {
        return -1;   
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;
    
    while(obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);
    
}


typedef struct {
    MyLinkedList *list;
    int currentSize;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
    //printf("%s\n", __func__);
    MyStack *new = NULL;
    
    new = (MyStack*)malloc(sizeof(MyStack));

    new->list = myLinkedListCreate();
    new->currentSize = 0;

    return new;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {

    myLinkedListAddAtTail(obj->list, x);
    obj->currentSize++;
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    int ret = 0;

    if(obj->currentSize > 0)
    {
        ret = myLinkedListGet(obj->list, obj->currentSize);
        myLinkedListDeleteAtIndex(obj->list, obj->currentSize);
        obj->currentSize--;
        return ret;
    }
    else
    {
        printf("Can't pop on empty stack \n");
        return -1;
    }

}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    
    return myLinkedListGet(obj->list, obj->currentSize);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    if(obj->currentSize > 0)
        return false;
    else
        return true;
}

void myStackFree(MyStack* obj) {
    if(obj->list) myLinkedListFree(obj->list);
    free(obj);
}

/* 16 test cases in 0ms, 6.2MB(<24%) on May 15th, 2021 */
