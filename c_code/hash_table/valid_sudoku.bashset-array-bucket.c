typedef struct 
{
    int **arr;
} MyHashSet;

#define SIZE        9
#define HASH_NUM    27
#define HASH_SIZE   9 /* 3*9 */
#define ERROR_CODE  -1

MyHashSet* myHashSetCreate() 
{
    MyHashSet* obj = malloc(sizeof(MyHashSet));
#ifdef HASH_INIT
    int i; 
    

    obj->arr = (int**)malloc(sizeof(int) * HASH_SIZE * HASH_NUM);
    for(i = 0; i < HASH_SIZE * HASH_NUM; i++)
        obj->arr[i] = -1;
#else
    obj->arr = calloc(HASH_SIZE * HASH_NUM, sizeof(int));
#endif
    return obj;
}

/* convert matrix coodination to interget */
/* 0 <= row,col <= 2 */
int matrixToInt(int row, int col)
{
    
    switch(10 * row + col)
    {
        /* 1st row */
        case 0: // 00
            return 0;
        case 10:
            return 1;
        case 20:
            return 2;
        /* 2nd row */
        case 1: // 01
            return 3;
        case 11:
            return 4;
        case 21:
            return 5;
        /* 3rd row */
        case 2: // 02
            return 6;
        case 12:
            return 7;
        case 22:
            return 8;
        default:
            printf("error, invalid cordination \n");
            return ERROR_CODE;
    }
}

void myHashSetAdd(MyHashSet* obj, int key, int i, int j) 
{
    //printf("%s:%d\n", __func__, key);
    /* would map and line up 9 3x3 squares to 0-8 in array
     * 9 rows to 9-17 in array
     * 9 columns to 18-26 in array */
    /* Define row : i vs col : j */
    
    /* 9 squares */
    obj->arr[matrixToInt(i, j) + key] = 1;
    /* 9 rows */
    obj->arr[SIZE + i + key] = 1;
    /* 9 columns */
    obj->arr[SIZE + SIZE + i + key] = 1;

}


bool myHashSetContains(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    if(obj->arr[key] == 1)
        return true;
    return false;
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

/* 32-88(<52%)-43.4, on May 30th, 2021 */
