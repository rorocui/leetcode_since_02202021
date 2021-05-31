typedef struct {
    int* queue;
    int  maxSize;
    int  front;
    int  rear;
    int  currentSize;
} MyCQue;


MyCQue* myCQueCreate(int k) {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->queue = (int*)malloc(sizeof(int) * k);
    obj->maxSize = k;
    obj->front = obj->rear = -1;
    obj->currentSize = 0;
    
    //printf("%s:%lx-%d\n", __func__, &obj, k);
    return obj;
}

bool myCQueEnQueue(MyCQue* obj, int value) {
    //printf("%s:%lx-%d\n", __func__, &obj, value);
    if(obj->currentSize == obj->maxSize) return false;
    /* if empty, need front++ */
    if(obj->currentSize == 0) obj->front++;

    if((++obj->rear) > (obj->maxSize - 1)) obj->rear = 0;
    //printf("%d-%d\n", obj->front, obj->rear);
    *(obj->queue + obj->rear) = value;
    obj->currentSize++;
    
    return true;
}

int myCQueDeQueue(MyCQue* obj) {
    //printf("%s:%lx-%d\n", __func__, obj, obj->currentSize);
    int ret = 0;

    if(!obj->currentSize) return -1;

    //printf("b:ret=%d\n", ret);
    //printf("b:%d-%d\n", obj->front, obj->rear);
    ret = *(obj->queue + obj->front);
    //printf("a:ret=%d\n", ret);
    if((++obj->front) > (obj->maxSize - 1)) obj->front = 0;
    obj->currentSize--;
    
    if(obj->currentSize == 0) obj->front = obj->rear = -1;
    //printf("a:%d-%d\n", obj->front, obj->rear);
    
    //printf("done:ret=%d\n", ret);
    return ret; 
}

bool myCQueIsEmpty(MyCQue* obj) {
    //printf("%s:%d\n", __func__, obj->currentSize);
    if(obj->currentSize)
        return false;
    else
        return true;
}

bool myCQueIsFull(MyCQue* obj) {
    //printf("%s:%d\n", __func__, obj->currentSize);
    if(obj->currentSize == obj->maxSize)
        return true;
    else
        return false;
}

void myCQueFree(MyCQue* obj) {
    if(obj->queue) free(obj->queue);
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
    MyCQue *row = NULL, *col = NULL;
    
    
    row = myCQueCreate(gridSize * 2);
    col = myCQueCreate(gridSize * 2);
    //printf("row queue 0x%lx, col 0x%lx\n", row, col);
    
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
                if(!myCQueIsEmpty(row) && !myCQueIsEmpty(col)) 
                {
                    //printf("new island, no clean queue, error\n"); 
                    return -1;
                }
                myCQueEnQueue(row, i);
                myCQueEnQueue(col, j);
                /* search whole grid */
                while(!myCQueIsEmpty(row))
                {
                    //printf("Row index queue size is %d\n", col->currentSize);
                    row_ptr = myCQueDeQueue(row);
                    col_ptr = myCQueDeQueue(col);
                    //printf("(i,j)=(%d,%d)\n", row_ptr, col_ptr);
                    /* search down horizontally */
                    if((row_ptr + 1) < gridSize)
                    {
                        //printf("try DH : (i,j)=(%d,%d)\n", row_ptr + 1, col_ptr);
	                    if(grid[row_ptr + 1][col_ptr] == 49)
	                    {
	
	                        if(!myCQueIsFull(row)) 
                                myCQueEnQueue(row, row_ptr + 1);
                            else
                            {
                                printf("Not enough space in Queue of Row to handle request\n");
                                return -1;
                            }
	                        if(!myCQueIsFull(col)) 
	                            myCQueEnQueue(col, col_ptr);
                            else
                            {
                                printf("Not enough space in Queue of Col to handle request\n");
                                return -1;
                            }
	                    }
	                    grid[row_ptr + 1][col_ptr] = 48;
                    } /* end if down horizontally */
                    /* search up horizontally */
                    if((row_ptr - 1) >= 0)
                    {
                        //printf("try UH : (i,j)=(%d,%d)\n", row_ptr - 1, col_ptr);
	                    if(grid[row_ptr - 1][col_ptr] == 49)
	                    {
	
	                        if(!myCQueIsFull(row)) 
                                myCQueEnQueue(row, row_ptr - 1);
                            else
                            {
                                printf("Not enough space in Queue of Row to handle request\n");
                                return -1;
                            }
	                        if(!myCQueIsFull(col)) 
	                            myCQueEnQueue(col, col_ptr);
                            else
                            {
                                printf("Not enough space in Queue of Col to handle request\n");
                                return -1;
                            }
	                    }
	                    grid[row_ptr - 1][col_ptr] = 48;
                    } /* end if up horizontally */
                    /* search right vertically */
                    if((col_ptr + 1) < *gridColSize)
                    {
                        //printf("try RV : (i,j)=(%d,%d)\n", row_ptr, col_ptr + 1);
	                    if(grid[row_ptr][col_ptr + 1] == 49)
	                    {
	                        if(!myCQueIsFull(row)) 
	                            myCQueEnQueue(row, row_ptr);
                            else
                            {
                                printf("Not enough space in Queue of Row to handle request\n");
                                return -1;
                            }
	                        if(!myCQueIsFull(col)) 
	                            myCQueEnQueue(col, col_ptr + 1);
                            else
                            {
                                printf("Not enough space in Queue of Col to handle request\n");
                                return -1;
                            }
	                    }
	                    grid[row_ptr][col_ptr + 1] = 48;
                    }
                    /* search left vertically */
                    if((col_ptr - 1) >= 0)
                    {
                        //printf("try LV : (i,j)=(%d,%d)\n", row_ptr, col_ptr - 1);
	                    if(grid[row_ptr][col_ptr - 1] == 49)
	                    {
	                        if(!myCQueIsFull(row)) 
	                            myCQueEnQueue(row, row_ptr);
                            else
                            {
                                printf("Not enough space in Queue of Row to handle request\n");
                                return -1;
                            }
	                        if(!myCQueIsFull(col)) 
	                            myCQueEnQueue(col, col_ptr - 1);
                            else
                            {
                                printf("Not enough space in Queue of Col to handle request\n");
                                return -1;
                            }
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

    myCQueFree(row);
    myCQueFree(col);
    
    return num;
}

/* 48 cases in 4ms in 7.9MB, beats 100% on April 19th, 2021 */

