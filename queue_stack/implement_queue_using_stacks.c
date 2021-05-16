typedef struct MyLinkedList{
    int val;
    struct MyLinkedList *next;   
    struct MyLinkedList *prev;   
} MyLinkedList;

typedef struct {
    MyLinkedList* list;
    MyLinkedList* current;
    unsigned int currentSize;
} MinStack;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __func__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));

    new->val = -1;
    new->next = new->prev = NULL;
    return new; 
}

void myLinkedListFree(MyLinkedList* obj) {
    //printf("%s\n", __func__);
    MyLinkedList* ptr = NULL;
    
    while(!obj && !obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);
    
}

MinStack* minStackCreate() {
    //printf("%s\n", __func__);
    MinStack* new = NULL;

    new = (MinStack*)malloc(sizeof(MinStack));
    new->current = new->list = NULL;
    new->currentSize = 0;
    
    return new;
}

void minStackPush(MinStack* obj, int val) {
    //printf("%s-obj:0x%lx,val:%d\n", __func__, obj, val);
    //printf("%s-val:%d\n", __func__, val);
    if(obj->list)
    {
        //printf("%s-list:0x%lx\n", __func__, obj->list);
        //printf("%s-current:0x%lx\n", __func__, obj->current);
        obj->current->next = myLinkedListCreate();
        obj->current->next->prev = obj->current;
        obj->current = obj->current->next;
        //printf("%s-after_current:0x%lx\n", __func__, obj->current);
    }
    else
    {
        obj->list = obj->current = myLinkedListCreate();
        //printf("%s-after_list:0x%lx\n", __func__, obj->list);
        //printf("%s-after_current:0x%lx\n", __func__, obj->current);
    }
    

    obj->current->val = val;
    obj->currentSize++;
    //printf("\n");
    ////printf("%s-%d\n", __func__, obj->currentSize);
}

int minStackPop(MinStack* obj) {
    //printf("%s-obj:0x%lx\n", __func__, obj);
    MyLinkedList* new = NULL;
    int ret = 0;

    ret = obj->current->val;
    if(obj->current != obj->list)
    {
        new = obj->current;
        obj->current = obj->current->prev;
        obj->current->next = NULL;
        free(new);
    }
    else
    {
        free(obj->current);
        obj->list = obj->current = NULL;
    }
    obj->currentSize--;
    
    //printf("%s-%d\n", __func__, ret);
    return ret;
    //printf("%s-%d\n", __func__, obj->currentSize);
}

int minStackTop(MinStack* obj) {
    //printf("%s-%d\n", __func__, obj->current->val);

    if(obj->current)
        return obj->current->val;
    else
    {
        printf("Empty Stack\n");
        return -1;
    }
}

void minStackFree(MinStack* obj) {
    //printf("%s\n", __func__);

    if(obj->list) myLinkedListFree(obj->list);
    if(obj) free(obj);
}

typedef struct {
    MinStack *stack_que;
    MinStack *stack_swap;
    int  currentSize;

} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
    MyQueue* new = NULL;

    new = (MyQueue*)malloc(sizeof(MyQueue));
    new->currentSize = 0;
    new->stack_que = minStackCreate();
    new->stack_swap = minStackCreate();

    return new;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    if(obj->currentSize != 0)
    {
        /* swap all items in obj->stack_que to obj->stack_swap */
        while(!minStackIsEmpty(obj->stack_que))
            minStackPush(obj->stack_swap, minStackPop(obj->stack_que));
        minStackPush(obj->stack_que, x);
        /* swap back */
        while(!minStackIsEmpty(obj->stack_swap))
            minStackPush(obj->stack_que, minStackPop(obj->stack_swap));
    }
    else
        minStackPush(obj->stack_que, x);
    obj->currentSize++;
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {

    if(obj->currentSize > 0)
    {
        obj->currentSize--;
        return minStackPop(obj->stack_que);
    }
    else
    {
        printf("empty Queue, can't pop, error \n");
        return -1;
    }
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {

    return minStackTop(obj->stack_que);

}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if(obj->currentSize > 0)
        return false;
    else
        return true;
}

void myQueueFree(MyQueue* obj) {

    if(obj->stack_que) minStackFree(obj->stack_que);
    if(obj->stack_swap) minStackFree(obj->stack_swap);
    if(obj) free(obj);
}
