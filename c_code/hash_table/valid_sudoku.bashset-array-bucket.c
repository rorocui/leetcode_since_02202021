typedef struct 
{
    int *arr;
} MyHashSet;

#define SIZE        9
#define HASH_NUM    27
#define ERROR_CODE  -1

MyHashSet* myHashSetCreate() 
{
    MyHashSet* obj = malloc(sizeof(MyHashSet));
#ifdef HASH_INIT
    obj->arr = (int**)malloc(sizeof(int) * SIZE * HASH_NUM);
    for(int i = 0; i < SIZE * HASH_NUM; i++)
        obj->arr[i] = 0;
#else
    obj->arr = calloc(SIZE * HASH_NUM, sizeof(int));
#endif
    return obj;
}

/* convert matrix coodination to interget */
/* 0 <= row,col <= 2 */
int matrixToInt(int row, int col)
{
    if( 0 <= row && row <= 2 && 0 <= col && col <= 2) return 0;
    else if( 3 <= row && row <= 5 && 0 <= col && col <= 2) return 1;
    else if( 6 <= row && row <= 8 && 0 <= col && col <= 2) return 2;
    /* 2nd 3-row && row */
    else if( 0 <= row && row <= 2 && 3 <= col && col <= 5) return 3;
    else if( 3 <= row && row <= 5 && 3 <= col && col <= 5) return 4;
    else if( 6 <= row && row <= 8 && 3 <= col && col <= 5) return 5;
    /* 3rd 3-row && row */
    else if( 0 <= row && row <= 2 && 6 <= col && col <= 8) return 6;
    else if( 3 <= row && row <= 5 && 6 <= col && col <= 8) return 7;
    else if( 6 <= row && row <= 8 && 6 <= col && col <= 8) return 8;
    else
    {
            printf("error, invalid cordination \n");
            return ERROR_CODE;
    }
}

void myHashSetAdd(MyHashSet* obj, int key, int i, int j) 
{
    //printf("%s:[%d][%d]-%d\n", __func__, i, j, key);
    /* would map and line up 9 3x3 squares to 0-8 in array
     * 9 rows to 9-17 in array
     * 9 columns to 18-26 in array */
    /* Define row : i vs col : j */
    
    /* 9 squares */
    //if(key == 5) printf("%d\n", matrixToInt(i, j) * SIZE + key);
    obj->arr[matrixToInt(i, j) * SIZE + key - 1] = 1;
    /* 9 rows */
    //if(key == 5) printf("%d\n", (SIZE + i) * SIZE + key);
    obj->arr[(SIZE + i) * SIZE + key - 1] = 1;
    /* 9 columns */
    //if(key == 5) printf("%d\n", (SIZE + SIZE + i) * SIZE + key);
    obj->arr[(SIZE + SIZE + j) * SIZE + key - 1] = 1;

}


bool myHashSetContains(MyHashSet* obj, int key, int i, int j) 
{
    //printf("%s:[%d][%d]-%d\n", __func__, i, j, key);
    //printf("matrix=%d\n", matrixToInt(i,j));
    /* 9 squares */
    //if(key == 5) printf("%d\n", matrixToInt(i, j) * SIZE + key);
    if(obj->arr[matrixToInt(i, j) * SIZE + key - 1] == 1) 
    {
        //printf("1:[%d][%d]-%d\n", i, j, key);
        return true;
    }
    /* 9 rows */
    //if(key == 5) printf("%d\n", (SIZE + i) * SIZE + key);
    if(obj->arr[(SIZE + i) * SIZE + key - 1] == 1) 
    {
        //printf("2:[%d][%d]-%d\n", i, j, key);
        return true;
    }
    /* 9 columns */
    //if(key == 5) printf("%d\n", (SIZE + SIZE + j) * SIZE + key);
    if(obj->arr[(SIZE + SIZE + j) * SIZE + key - 1] == 1)
    {
        //printf("3:[%d][%d]-%d\n", i, j, key);
        return true;
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{
    MyHashSet* hash_new = NULL;
    int i = 0, j = 0;

    hash_new = myHashSetCreate();
    for(i = 0; i < boardSize; i++)
        for(j = 0; j < boardColSize[i]; j++)
        {
            if(board[i][j] != '.')
            {
                //printf("[%d][%d]=%c\n", i, j, board[i][j]);
                if(myHashSetContains(hash_new, (int)(board[i][j] - '0'), i, j))
                {
                    myHashSetFree(hash_new);
                    return false;
                }
                else
                    myHashSetAdd(hash_new, (int)(board[i][j] - '0'), i, j);
            }

        }

    myHashSetFree(hash_new);
    return true;
}

/* 507-12(<31%)-6.7, on Jun 21st, 2021 */
