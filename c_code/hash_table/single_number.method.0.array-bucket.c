typedef struct 
{
    int *arr;
} MyHashSet;

/*#define HASH_INIT */
#define SIZE 60001
#define DELTA 30000

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

int singleNumber(int* nums, int numsSize)
{
    MyHashSet *new = NULL;
    int i;
    int ret;

    ret = 30001;
    new = myHashSetCreate();
    for(i = 0; i < numsSize; i++)
    {
        new->arr[nums[i] + DELTA]++;
    }
    for(i = 0; i < SIZE; i++)
    {
        if(new->arr[i] == 1)
        {
            myHashSetFree(new);
            return (i - DELTA);
        }
    }
    printf("failed to find single one, return 30001\n");
    return ret;

}
/* 61-20(<34%)-10.6, on Jun 3rd, 2021 */
