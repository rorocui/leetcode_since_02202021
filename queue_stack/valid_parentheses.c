typedef struct MyLinkedList{
    char val;
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
    //printf('%s\n', __func__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));

    new->val = -1;
    new->next = new->prev = NULL;
    return new; 
}

void myLinkedListFree(MyLinkedList* obj) {
    //printf('%s\n', __func__);
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
    //printf('%s\n', __func__);
    MinStack* new = NULL;

    new = (MinStack*)malloc(sizeof(MinStack));
    new->current = new->list = NULL;
    new->currentSize = 0;
    
    return new;
}

void minStackPush(MinStack* obj, char val) {
    //printf('%s-%d\n', __func__, val);
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
    ////printf('%s-%d\n', __func__, obj->currentSize);
}

void minStackPop(MinStack* obj) {
    //printf('%s\n', __func__);
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
    ////printf('%s-%d\n', __func__, obj->currentSize);
}

char minStackTop(MinStack* obj) {
    //printf('%s-%d\n', __func__, obj->current->val);

    if(obj->current)
        return obj->current->val;
    else
        return 0;
}
void minStackFree(MinStack* obj) {
    //printf('%s\n', __func__);

    if(obj->list) myLinkedListFree(obj->list);
    if(obj) free(obj);
}

bool isValid(char * s)
{
    MinStack *stack_ptr = NULL;
    int i;
    char top_char;
    bool return_false = false;

    stack_ptr = minStackCreate();
    for(i = 0; i < strlen(s); i++)
    {
        switch(s[i])
        {
            case ')':
                top_char = minStackTop(stack_ptr);
                if(top_char != '(')
                    return_false = true;
                else
                    minStackPop(stack_ptr);
                break;
            case ']':
                top_char = minStackTop(stack_ptr);
                if(top_char != '[')
                    return_false = true;
                else
                    minStackPop(stack_ptr);
                break;
            case '}':
                top_char = minStackTop(stack_ptr);
                if(top_char != '{')
                    return_false = true;
                else
                    minStackPop(stack_ptr);
                break;
            default:
                minStackPush(stack_ptr, s[i]);
        }/* end of switch */
        if(return_false) break;
    }/* end of for */
    
    if(return_false)
    {
        minStackFree(stack_ptr);
        return false;
    }

    if(stack_ptr->currentSize)
    {
        minStackFree(stack_ptr);
        return false;
    }
    else
    {
        minStackFree(stack_ptr);
        return true;
    }
}

/* 91 cases in 4ms with 5.8MB memory, on April 29th, 2021 */

