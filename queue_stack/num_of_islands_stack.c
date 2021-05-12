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


void print_grid(char** grid, int i, int j)
{
    /* print out grid */
    for(int m = 0; m < i; m++)
    {
        printf("[");
        for(int n = 0; n < j; n++)
            printf(" %c", grid[m][n]);
        printf("]\n");
    }
    printf("\n\n");
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    int num = 0;
    int i, j;
    int row_ptr = -1, col_ptr = -1;
    MinStack *row = NULL, *col = NULL;
    
    
    row = minStackCreate();
    col = minStackCreate();
    //printf("row stack 0x%lx, col 0x%lx\n", row, col);
    
    //printf("gridSize=%d, gridColSize=%d\n", gridSize, *gridColSize);
    
    
    /* row index*/
    for(i = 0; i < gridSize; i++)
    {
        /* column index*/
        for(j = 0; j < *gridColSize; j++) 
        {
            if(grid[i][j] == 49)
            {
                num++;
                /* search Island boundary */
                if(!minStackIsEmpty(row) && !minStackIsEmpty(col)) 
                {
                    //printf("new island, no clean queue, error\n"); 
                    return -1;
                }
                minStackPush(row, i);
                minStackPush(col, j);
                /* search whole grid */
                while(!minStackIsEmpty(row))
                {
                    row_ptr = minStackPop(row);
                    col_ptr = minStackPop(col);
                    //printf("(i,j)=(%d,%d)\n", row_ptr, col_ptr);
                    /* search down horizontally */
                    if((row_ptr + 1) < gridSize)
                    {
                        //printf("try DH : (i,j)=(%d,%d)\n", row_ptr + 1, col_ptr);
	                    if(grid[row_ptr + 1][col_ptr] == 49)
	                    {
                            minStackPush(row, row_ptr + 1);
                            minStackPush(col, col_ptr);
	                    }
	                    grid[row_ptr + 1][col_ptr] = 48;
                    } /* end if down horizontally */
                    /* search up horizontally */
                    if((row_ptr - 1) >= 0)
                    {
                        //printf("try UH : (i,j)=(%d,%d)\n", row_ptr - 1, col_ptr);
	                    if(grid[row_ptr - 1][col_ptr] == 49)
	                    {
                            minStackPush(row, row_ptr - 1);
                            minStackPush(col, col_ptr);
	                    }
	                    grid[row_ptr - 1][col_ptr] = 48;
                    } /* end if up horizontally */
                    /* search right vertically */
                    if((col_ptr + 1) < *gridColSize)
                    {
                        //printf("try RV : (i,j)=(%d,%d)\n", row_ptr, col_ptr + 1);
	                    if(grid[row_ptr][col_ptr + 1] == 49)
	                    {
                            minStackPush(row, row_ptr);
                            minStackPush(col, col_ptr + 1);
	                    }
	                    grid[row_ptr][col_ptr + 1] = 48;
                    }
                    /* search left vertically */
                    if((col_ptr - 1) >= 0)
                    {
                        //printf("try LV : (i,j)=(%d,%d)\n", row_ptr, col_ptr - 1);
	                    if(grid[row_ptr][col_ptr - 1] == 49)
	                    {
                            minStackPush(row, row_ptr);
                            minStackPush(col, col_ptr - 1);
	                    }
	                    grid[row_ptr][col_ptr - 1] = 48;
                    } /* end if left vertically */
                    //print_grid(grid, gridSize, *gridColSize);
                }/* end while */
                //print_grid(grid, gridSize, *gridColSize);
            }/* end if check 1 or 0 */       
            /* mark grid node (i,j) as visited */
            //printf("try outside of while : (i,j)=(%d,%d)\n", i, j);
            grid[i][j] = 48;
        } /* end for j */
    } /* end for i */

    if(row) minStackFree(row);
    if(col) minStackFree(col);
    
    return num;
}

/* 48 test cases in 20ms <14%, in 11.8MB, on May 10th, 2021*/
