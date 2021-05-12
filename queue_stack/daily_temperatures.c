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
    printf("%s-obj:0x%lx\n", __func__, obj);
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
    
    return ret;
    ////printf("%s-%d\n", __func__, obj->currentSize);
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

bool minStackIsEmpty(MinStack* obj)
{
    printf("%s-%d\n", __func__, obj->currentSize);
    if(obj->currentSize) return false;
    else    return true;
}

void minStackFree(MinStack* obj) {
    //printf("%s\n", __func__);

    if(obj->list) myLinkedListFree(obj->list);
    if(obj) free(obj);
}

int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
    int* new = NULL;
    MinStack* stack_ptr = NULL;
    MinStack* stack_cache = NULL;
    int i, j = 0;
    int min_value = 29;

    stack_ptr = minStackCreate();
    stack_cache = minStackCreate();
    //printf("%s-stack-ptr:ox%lx\n", __func__, stack_ptr);
    //printf("%s-stack-cache:ox%lx\n", __func__, stack_cache);
    new = (int*)malloc(sizeof(int) * TSize);
    *returnSize = TSize;

    for(i = 0; i < TSize; i++)
    {
        //printf("[%d]-%d\n", i, T[i]);
        minStackPush(stack_ptr, T[i]);
    }

    for(i = TSize - 1; i >= 0; i--)
    {
        j = 0;
        printf("i=%d\n", i);
        while(minStackTop(stack_ptr) < min_value)
        {
            printf("j=%d,max=%d\n", j, min_value);
            j++;
            minStackPush(stack_cache, minStackPop(stack_ptr));
        }

        new[i] = j;
        while(!minStackIsEmpty(stack_cache))
        {
            minStackPush(stack_ptr, minStackPop(stack_cache));
        }
        min_value = minStackPop(stack_ptr);
    }

    if(stack_ptr) minStackFree(stack_ptr);
    if(stack_cache) minStackFree(stack_cache);

    return new;
}
