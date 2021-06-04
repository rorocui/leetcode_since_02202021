//#define HASH_INIT
#define SIZE 1001

typedef struct 
{
    int *arr;
} MyHashSet;

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



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    MyHashSet* new = NULL;
    MyHashSet* found = NULL;
    int i;
    int* ret = NULL;

    *returnSize = 0;
    ret = calloc(SIZE, sizeof(int));
    new = myHashSetCreate();
    found = myHashSetCreate();
    for(i = 0; i < nums1Size; i++)
        if(!myHashSetContains(new, nums1[i]))
            myHashSetAdd(new, nums1[i]);

    for(i = 0; i < nums2Size; i++)
    {
        if(myHashSetContains(new, nums2[i]) && !myHashSetContains(found, nums2[i]))
        {
            myHashSetAdd(found, nums2[i]);
            ret[*returnSize] = nums2[i];
            (*returnSize)++;
        }
    }
    
    //printf("retSize=%d\n", *returnSize);

    return ret;
}


/* 55-8(<47%)-7.2, on Jun 3rd, 2021 */
