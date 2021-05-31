typedef struct {
    int val;
    struct MyLinkedList* next;   
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = 0x7FFFFFFF;
    new->next = NULL;
    return new; 
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    
    //printf("%s:0x%lx,0x%lx\n", __func__, obj, obj->next);
    
    end = myLinkedListCreate();
    if(obj->next)
    {
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;    
        }
        ptr->next = end;
        ptr->val = val;
    }
    else
    {
        obj->val = val;
        obj->next = end;
        
    }
    
    /*debug only*/
    /*
    ptr = obj;
    printf("link list(0x%lx):", obj);
    while(ptr)
    {
        printf("%d |", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
    */
    
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
} MinStack;

/** Initialize your data structure here. */

MinStack* minStackCreate() {
    //printf("%s\n", __func__);
    MinStack *new = NULL;
    
    new = (MinStack*)malloc(sizeof(MinStack));

    new->list = myLinkedListCreate();
    new->currentSize = 0;

    return new;
}

/** Push element x onto stack. */
void minStackPush(MinStack* obj, int x) {

    //printf("stack_push:0x%x,%d\n", obj, x);
    myLinkedListAddAtTail(obj->list, x);
    obj->currentSize++;
}

/** Removes the element on top of the stack and returns that element. */
int minStackPop(MinStack* obj) {
    int ret = 0;

    if(obj->currentSize > 0)
    {
        ret = myLinkedListGet(obj->list, obj->currentSize - 1);
        //printf("stack_pop = %d\n", ret);
        myLinkedListDeleteAtIndex(obj->list, obj->currentSize - 1);
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
int minStackTop(MinStack* obj) {
    
    return myLinkedListGet(obj->list, obj->currentSize - 1);
}

int minStackGetMin(MinStack* obj) {
    int min = 0x7FFFFFFF;
    MyLinkedList* new = obj->list;
    
    while(new)
    {
        min = (min < new->val) ? min : new->val;
        if(new->next) new = new->next;
        else break;
    }

    return min;
}

/** Returns whether the stack is empty. */
bool minStackEmpty(MinStack* obj) {
    if(obj->currentSize > 0)
        return false;
    else
        return true;
}

void minStackFree(MinStack* obj) {
    if(obj->list) myLinkedListFree(obj->list);
    free(obj);
}
/* 31 test cases in 364ms(<9%) in 12.8MB, on May 16th, 2021 */
