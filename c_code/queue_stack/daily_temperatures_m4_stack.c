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
    //printf("%s-%d\n", __func__, obj->currentSize);
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
    MinStack* index_stack = NULL;
    int i;

    index_stack = minStackCreate();
    new = (int*)calloc(TSize, sizeof(int));
    *returnSize = TSize;

    for(i = TSize - 1; i >= 0; i--)
    {
        while(!minStackIsEmpty(index_stack) && T[i] >= T[minStackTop(index_stack)])
        {
            minStackPop(index_stack);
        }
        if(!minStackIsEmpty(index_stack))
            new[i] = minStackTop(index_stack) - i;
        minStackPush(index_stack, i);
    }

    if(index_stack) minStackFree(index_stack);

    return new;
}

/* 38 cases in 212ms(<15%), 43MB (<7%) on May 5th, 2021 */
