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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes)
{
    MinStack* stack_sr = NULL;
    MinStack* stack_sc = NULL;
    int i,j;
    int old_color = -1;

    if(image[sr][sc] == newColor) return image;

    stack_sr = minStackCreate();
    stack_sc = minStackCreate();
    *returnColumnSizes = malloc(sizeof(int) * imageSize);

    for(i = 0; i < imageSize; i++)
    {
        //printf("imageColSize[%d]=%d\n", i, imageColSize[i]);
        (*returnColumnSizes)[i] = imageColSize[i];
    }

    *returnSize = imageSize;
    old_color = image[sr][sc];
    minStackPush(stack_sr, sr);
    minStackPush(stack_sc, sc);

    while(!minStackEmpty(stack_sr))
    {
        i = minStackPop(stack_sr);
        j = minStackPop(stack_sc);
        if(image[i][j] == old_color)
            image[i][j] = newColor;
        /* check left */
        if((i - 1) >= 0 && image[i - 1][j] == old_color)
        {
            minStackPush(stack_sr, i - 1);
            minStackPush(stack_sc, j);
        }
        /* check right */
        if((i + 1) < imageSize && image[i + 1][j] == old_color)
        {
            minStackPush(stack_sr, i + 1);
            minStackPush(stack_sc, j);
        }
        /* check up */
        if((j - 1) >= 0 && image[i][j - 1] == old_color)
        {
            minStackPush(stack_sr, i);
            minStackPush(stack_sc, j - 1);
        }
        /* check down */
        if((j + 1) < imageColSize[i] && image[i][j + 1] == old_color)
        {
            minStackPush(stack_sr, i);
            minStackPush(stack_sc, j + 1);
        }

    }

    minStackFree(stack_sr);
    minStackFree(stack_sc);

    /*
    for(i = 0; i < imageSize; i++)
    {
        printf("[");
        for(int j = 0; j < (*returnColumnSizes)[i]; j++)
            printf("%d ", image[i][j]);
        printf("]\n");

    }
    */

    return image;
}

/* 277 test cases in 20ms(<86%) in 8.3MB, on May 23th, 2021 */
