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

    myLinkedListAddAtTail(obj->list, x);
    obj->currentSize++;
}

/** Removes the element on top of the stack and returns that element. */
int minStackPop(MinStack* obj) {
    int ret = 0;

    if(obj->currentSize > 0)
    {
        ret = myLinkedListGet(obj->list, obj->currentSize - 1);
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

int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes)
{
    MinStack *stack_i = NULL;
    MinStack *stack_j = NULL;
    int i = 0, j = 0;
    int m = 0, n = 0;
    int len = 0;
    int** ret = NULL;
    int visited = 2;

    stack_i = minStackCreate();
    stack_j = minStackCreate();


    *returnColumnSizes = malloc(sizeof(int) * matSize);
    *ret = malloc(sizeof(int*) * matSize)

    for(i = 0; i < matSize; i++)
    {
        (*returnColumnSizes)[i] = matColSize[i];
        (*ret)[i] = malloc(sizeof(int) * matColSize[i]);
        for(j = 0; j < matColSize[i]; j++)
        {
            if(mat[i][j] == 0)
            {
                ret[i][j] = 0;
            }
            else
            {
	            minStackPush(stack_i, i);
	            minStackPush(stack_j, j);
	            len = 0;
                visited++;
	
	            while(!minStackEmpty(stack_i))
	            {
                    m = minStackPop(stack_i);
                    n = minStackPop(stack_j);
                    len++;
                    /* check left */
                    if(m >= 1 && mat[m -1][n] == 0)
                        break;
                    if(m >=1 && mat[m - 1][n] != visited)
                    {
                        minStackPush(stack_i, m - 1);
                        minStackPush(stack_j, n);
                        mat[m - 1][n] = visited
                    }
                    /* check right */
                    if((m + 1) <  matColSize[i] && mat[m + 1][n] == 0)
                        break;
                    if((m + ) < matColSize[i] && mat[m + 1][n] != visited)
                    {
                        minStackPush(stack_i, m + 1);
                        minStackPush(stack_j, n);
                        mat[m + 1][n] = visited
                    }
                    /* check up */
                    if(n >= 1 && mat[m][n - 1] == 0)
                        break;
                    if(m >=1 && mat[m][n - 1] != visited)
                    {
                        minStackPush(stack_i, m);
                        minStackPush(stack_j, n - 1);
                        mat[m][n - 1] = visited
                    }
                    /* check down */
                    if((n + 1) <  matColSize[i] && mat[m][n + 1] == 0)
                        break;
                    if((n + 1) < matColSize[i] && mat[m][n + 1] != visited)
                    {
                        minStackPush(stack_i, m);
                        minStackPush(stack_j, n + 1);
                        mat[m][n + 1] = visited
                    }
	
	            } /* end while */
                ret[m][n] = len;
            } /* end of if mat[i][j] == 0, else */

        } /* end of for j */

    } /* end of for i */
    *returnSize = matSize;

    minStackFree(stack_i);
    minStackFree(stack_j);

    return ret;

}


