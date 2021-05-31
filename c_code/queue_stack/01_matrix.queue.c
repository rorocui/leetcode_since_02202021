typedef struct {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = -1;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    //printf("%s:0x%x:%d\n", __func__, obj, val);
    if(obj)
    {
        end = myLinkedListCreate();
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->val = val;
        ptr->next = end;
    }
    else
    {
        obj->val = val;

    }
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* temp = NULL;
    int i;

    //printf("%s:%d\n", __func__, val);
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

    //printf("%s:0x%x\n", __func__, obj);
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
    //printf("%s:0x%x\n", __func__, obj);
    if(i == index && ptr)
    {
        //printf("%s:%d\n", __func__, ptr->val);
        return ptr->val;
    }
    else
    {
        return -1;
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;

    //while(!EmptyList(obj->next))
    while(obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);

}

typedef struct {
    MyLinkedList* que;
    int  currentSize;
} MyCQue;


MyCQue* myCQueCreate() {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->que = myLinkedListCreate();
    obj->currentSize = 0;
    
    return obj;
}

bool myCQueEnQue(MyCQue* obj, int value) {
    //printf("EnQue-%d\n", value);
    myLinkedListAddAtTail(obj->que, value);
    obj->currentSize++;
    return true;
}

int myCQueDeQue(MyCQue* obj) {
    int ret = 0;

    if(obj->currentSize > 0)
    {
        obj->currentSize--;
        ret = myLinkedListGet(obj->que, 0);
        myLinkedListDeleteAtIndex(obj->que, 0);
        //printf("DeQue-%d\n", ret);
        return ret;
    }
    else
    {
        //printf(" Empty queue, can't Deque\n");
        return -1;
    }

}

bool myCQueIsEmpty(MyCQue* obj) {
    if(obj->currentSize)
        return false;
    else
        return true;
}

void myCQueFree(MyCQue* obj) {
    if(obj->que) myLinkedListFree(obj->que);
    if(obj) free(obj);
}

int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes)
{
    //printf("%s:%d\n", __func__, matSize);
    MyCQue *queue_i = NULL;
    MyCQue *queue_j = NULL;
    int i = 0, j = 0;
    int m = 0, n = 0;
    int len = 0;
    int** ret = NULL;
    int visited = 2;
    int step = 0;

    queue_i = myCQueCreate();
    queue_j = myCQueCreate();


    *returnColumnSizes = malloc(sizeof(int) * matSize);
    ret = (int**)malloc(sizeof(int*) * matSize);

    for(i = 0; i < matSize; i++)
    {
        (*returnColumnSizes)[i] = matColSize[i];
        *(ret + i) = malloc(sizeof(int) * matColSize[i]);
        for(j = 0; j < matColSize[i]; j++)
        {
            //if(i == 0) printf("mat[%d][%d]=%d\n", i, j, mat[i][j]);
            if(mat[i][j] == 0)
            {
                ret[i][j] = 0;
            }
            else
            {
	            myCQueEnQue(queue_i, i);
	            myCQueEnQue(queue_j, j);
	            len = 0;
                visited++;
                step = 1;
	
	            //if(i == 0) printf("BW:new search visited = %d, mat[%d][%d] = %d\n", visited, i, j, mat[i][j]);
	            while(!myCQueIsEmpty(queue_i))
	            {

                    m = myCQueDeQue(queue_i);
                    n = myCQueDeQue(queue_j);
                    step--;
                    
	                //if(i == 0) printf("new search %d,%d = [%d][%d]\n", i, j, m, n);
	                //if(i == 0) printf("new search matColSize[%d] = %d\n", i, matColSize[i]);
                    /* Current step search done */
                    if(step == 0)
                    {
                        len++;
                        //if(i == 0) printf("len = %d\n", len);
                    }

                    /* check up */
                    if(m >= 1 && mat[m -1][n] == 0)
                        break;
                    if(m >=1 && mat[m - 1][n] != visited)
                    {
                        myCQueEnQue(queue_i, m - 1);
                        myCQueEnQue(queue_j, n);
                        mat[m - 1][n] = visited;
                    }
                    /* check down */
                    if((m + 1) <  matSize && mat[m + 1][n] == 0)
                        break;
                    if((m + 1) < matSize && mat[m + 1][n] != visited)
                    {
                        myCQueEnQue(queue_i, m + 1);
                        myCQueEnQue(queue_j, n);
                        mat[m + 1][n] = visited;
                    }
                    /* check left */
                    if(n >= 1 && mat[m][n - 1] == 0)
                        break;
                    if(n >= 1 && mat[m][n - 1] != visited)
                    {
                        myCQueEnQue(queue_i, m);
                        myCQueEnQue(queue_j, n - 1);
                        mat[m][n - 1] = visited;
                    }
                    /* check right */
                    if((n + 1) <  matColSize[i] && mat[m][n + 1] == 0)
                        break;
                    if((n + 1) < matColSize[i] && mat[m][n + 1] != visited)
                    {
                        myCQueEnQue(queue_i, m);
                        myCQueEnQue(queue_j, n + 1);
                        mat[m][n + 1] = visited;
                    }
                    if(step == 0)
                    {
                        step = queue_i->currentSize;
                        //if(i == 0) printf("step = %d\n", step);
                    }
	
	            } /* end while */
                if(step != 0) len++;
                ret[i][j] = len;
	            while(!myCQueIsEmpty(queue_i))
	            {
                    myCQueDeQue(queue_i);
                    myCQueDeQue(queue_j);
                }
            } /* end of if mat[i][j] == 0, else */

        } /* end of for j */

    } /* end of for i */
    *returnSize = matSize;

    myCQueFree(queue_i);
    myCQueFree(queue_j);

    return ret;

}


/* 48 test cases in 216ms in 48.4MB, on May 26th, 2021 */

