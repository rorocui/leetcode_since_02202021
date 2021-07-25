#define DELTA 50000
//#define BUCKET_SIZE 10000
#define SIZE        100000
#define INIT_NUM    0
#define ERROR_CODE  0x80000000
#define MIN_INT_32  0x80000000
#define MAX_INT     100001

typedef struct {
    int* ptr;
} MyHashMap;

/** Initialize your data structure here. */

MyHashMap* myHashMapCreate() 
{
    int i;
    MyHashMap* ret = malloc(sizeof(MyHashMap));
    
    ret->ptr = malloc(sizeof(int) * SIZE);
    for(i = 0; i < SIZE; i++)
        ret->ptr[i] = INIT_NUM;
    
    return ret;
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) 
{
    if(obj)
    {
        return obj->ptr[key];
    }
    else
        return ERROR_CODE;
  
}

/** Count value accounting key and current count*/
void myHashMapPut(MyHashMap* obj, int key, int val) 
{
    obj->ptr[key] = val;
}

/** Count value accounting key and current count*/
void myHashMapUpdate(MyHashMap* obj, int key) 
{
    (obj->ptr[key])++;
}

void myHashMapFree(MyHashMap* obj) {
    if(obj)
    {
        if(obj->ptr) free(obj->ptr);
        free(obj);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    int i;
    int count;
    int k_count;
    int num;
    int* ret = NULL;
    MyHashMap *hash_map = NULL;
    MyHashMap *sort_count = NULL;

    num = k_count = count = 0;
    ret = malloc(k * sizeof(int));
    hash_map = myHashMapCreate();
    sort_count = myHashMapCreate();
    for(i = 0; i < numsSize; i++)
    {
        myHashMapUpdate(hash_map, nums[i] + DELTA);
    }
    for(i = 0; i < SIZE; i++)
    {
        count = myHashMapGet(hash_map, i);
        if(count != 0)
        {
            printf("%d\n", count);
            myHashMapPut(sort_count, count, i);
        }
    }
    for(i = SIZE - 1; i >= 0 && k_count < k; i--)
    {
       num = myHashMapGet(sort_count, i);
       if(num != 0)
       {
           printf("%d\n", num);
           ret[k_count++] = num - DELTA;
       }
    }

    *returnSize = k;

    myHashMapFree(hash_map);
    myHashMapFree(sort_count);

    return ret;
}


/* failed on test case
 [1,2]
2
on July 19th, 2021*/

