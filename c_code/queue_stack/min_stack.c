
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
    //printf("%s-%d\n", __func__, val);
    if(obj->list)
    {
        obj->current->next = myLinkedListCreate();
        obj->current->next->prev = obj->current;
        obj->current = obj->current->next;
    }
    else
        obj->list = obj->current = myLinkedListCreate();

    obj->current->val = val;
    obj->currentSize++;
    ////printf("%s-%d\n", __func__, obj->currentSize);
}

void minStackPop(MinStack* obj) {
    //printf("%s\n", __func__);
    MyLinkedList* new = NULL;

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
    ////printf("%s-%d\n", __func__, obj->currentSize);
}

int minStackTop(MinStack* obj) {
    //printf("%s-%d\n", __func__, obj->current->val);

    return obj->current->val;
}

int minStackGetMin(MinStack* obj) {
    //printf("%s\n", __func__);
    int min = 0x7FFFFFFF;
    MyLinkedList* new = obj->list;
    
    //printf("%d\n", new->val);

    while(new)
    {
        //printf("0x%lx-%d,next:0x%lx\n", new, new->val, new->next);
        
        min = (min < new->val) ? min : new->val;
        if(new->next) new = new->next;
        else break;
    }

    return min;
}

void minStackFree(MinStack* obj) {
    //printf("%s\n", __func__);

    if(obj->list) myLinkedListFree(obj->list);
    if(obj) free(obj);
}

/* 31 cases in 216ms, uses 13MB, beats 8% on April 28th, 2021 */

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
