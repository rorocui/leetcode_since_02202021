typedef struct 
{
    int *arr;
} MyHashSet;

#define HASH_INIT
#define SIZE 1000

MyHashSet* myHashSetCreate() 
{
    MyHashSet* obj = malloc(sizeof(MyHashSet));
#ifdef HASH_INIT
    int i; 
    

    obj->arr = malloc(sizeof(int) * SIZE);
    for(i = 0; i < SIZE; i++)
        obj->arr[i] = -1;
#else
    obj->arr = calloc(SIZE, sizeof(int));
#endif
    return obj;
}

void myHashSetAdd(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    obj->arr[key] = 1;
}

void myHashSetRemove(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    obj->arr[key] = 0;
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

int numSquareNum(int n)
{
    int num = 0;

    while(n)
    {
        num += (n % 10) * (n % 10);
        n /= 10;
    }

    return num;
}

bool isHappy(int n)
{
    MyHashSet* new = NULL;

    new = myHashSetCreate();

    while(true)
    {
        n = numSquareNum(n);
        //printf("n=%d\n", n);
        if(n == 1)
        {
            myHashSetFree(new);
            return true;
        }
        if(myHashSetContains(new, n))
        {
            myHashSetFree(new);
            return false;
        }
        myHashSetAdd(new, n);
    }
}

/* 402-4(<16%)-7.8, on Jun 4th, 2021 */

