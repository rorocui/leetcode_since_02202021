typedef struct 
{
    int *arr;
} MyHashSet;

#define SIZE 2000000001
#define DELTA 1000000000

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
    obj->arr[key + DELTA] = 1;
}

void myHashSetRemove(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    obj->arr[key + DELTA] = 0;
}

bool myHashSetContains(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    if(obj->arr[key + DELTA] == 1)
        return true;
    return false;
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

bool containsDuplicate(int* nums, int numsSize)
{
    MyHashSet* obj = NULL;
    int i;

    obj = myHashSetCreate();
    for(i = 0; i < numsSize; i++)
    {
        if(myHashSetContains(obj, nums[i]))
        {
            myHashSetFree(obj);
            return true;
        }
        else
            myHashSetAdd(obj, nums[i]);
    }

    myHashSetFree(obj);
    return false;
}

/* 32-88(<52%)-43.4, on May 30th, 2021 */
