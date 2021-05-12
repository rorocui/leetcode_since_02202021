#define OUT_RANGE  -210

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
    int i;
    int operand_a, operand_b, operator;
    bool operator_ready = false;


    operand_a = operand_b = OUT_RANGE;
    operand_stack = minStackCreate();

    for(i = 0; i < tokensSize - 1; i++)
    {
        switch(tokens[i][0])
        {
            case 0x2A: /* multiple */
            case 0x2F: /* division */
            case 0x2B: /* addition */ 
            case 0x2D: /* subtraction */
                operator_ready = true;
                operater = tokens[i][0];
                break;
            default:
                if(operand_a == OUT_RANGE)
                {
                    operand_a = operand_a stringToShort(tokens[i]);
                    minStackPush(operand_stack, operand_a);
                }
                else if(operand_b == OUT_RANGE)
                {
                    operand_b = operand_a stringToShort(tokens[i]);
                    minStackPush(operand_stack, operand_b);
                }
                else
                {
                    operand_a = operand_b;
                    operand_b = operand_a stringToShort(tokens[i]);
                    minStackPush(operand_stack, operand_b);
                }
                break;
        }/* end of switch tokens[i][0] */

        if(operator_ready)
        {
	        switch(operator)
	        {
	            case 0x2A: /* multiple 42 */
                    operand_a *= operand_b
	                break;
	            case 0x2F: /* division 47 */
	                operand_a /= operand_b;
	                break;
	            case 0x2B: /* addition 43 */ 
	                operand_a += operand_b;
	                break;
	            case 0x2D: /* subtraction 45*/
	                operand_a -= operand_b;
	                break;
	            default:
	                printf("Not correct operator -%d \n", operator);
	        }/*end swith operator*/

            operator_ready = false;
            minStackPop(operand_stack);
            minStackPop(operand_stack);
            if(minStackIsEmpty)
            {
                operand_b = OUT_RANGE;
                minStackPush(operand_stack, operand_a);
            }
            else
            {
                operand_b = operand_a;
                operand_a = minStackTop(operand_stack);
                minStackPush(operand_stack, operand_b);
            }
        }/* end of if operator_ready */
    
    }/* end of for */
    
    if(operand_stack) minStackFree(operand_stack); 

    return operand_a;

}
