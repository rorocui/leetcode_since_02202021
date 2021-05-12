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
    printf("%s-obj:0x%lx,val:%d\n", __func__, obj, val);
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
    
    printf("%s-0x%x-%d\n", __func__, obj, ret);
    return ret;
    //printf("%s-%d\n", __func__, obj->currentSize);
}

int minStackTop(MinStack* obj) {
    printf("%s-0x%x:%d\n", __func__, obj, obj->current->val);

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

int stringToShort(char *string)
{
    int i;
    int ret = 0;
    int str_len = strlen(string);
    int minus = 1;

    if(string[0] == '-')
        minus = -1;
    else
        ret = string[0] - '0';

    for(i = 1; i < str_len; i++)
        ret = ret * 10 + (string[i] - '0');

    return  ret * minus;
}


int evalRPN(char ** tokens, int tokensSize){
    MinStack *operand_stack = NULL;
    MinStack *operator_stack = NULL;
    int i, ret = 0;
    int operand;

    operand_stack = minStackCreate();
    operator_stack = minStackCreate();

    for(i = tokensSize - 1; i >=0; i--)
    {
        switch(tokens[i][0])
        {
            case 0x2A: /* multiple */
            case 0x2F: /* division */
            case 0x2B: /* addition */ 
            case 0x2D: /* subtraction */
                minStackPush(operator_stack, tokens[i][0]);
                break;
            default:
                operand = stringToShort(tokens[i]);
                minStackPush(operand_stack, operand);
                break;
        }
    
    }
    ret = minStackPop(operand_stack);
    while(!minStackIsEmpty(operand_stack))
    {
        operand = minStackPop(operand_stack);
        switch(minStackTop(operator_stack))
        {
            case 0x2A: /* multiple 42 */
                ret *= operand;
                break;
            case 0x2F: /* division 47 */
                ret /= operand;
                break;
            case 0x2B: /* addition 43 */ 
                ret += operand;
                break;
            case 0x2D: /* subtraction 45*/
                ret -= operand;
                break;
            default:
                printf("Not correct operator -%d \n", minStackTop(operator_stack));
        }
        minStackPop(operator_stack);
    }
    
    if(operand_stack) minStackFree(operand_stack); 
    if(operator_stack) minStackFree(operator_stack); 

    return ret;

}
