
#define SIZE  2000000001
#define DELTA 1000000000

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
        ret->ptr[i] = -1;
    
    return ret;
}

/** value will always be non-negative. */
void myHashMapPut(MyHashMap* obj, int key, int value) 
{
    if(obj)
    {
        obj->ptr[key] = value;
    }
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) 
{
    if(obj)
    {
        return obj->ptr[key];
    }
    else
        return -1;
  
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key) {
    if(obj)
        obj->ptr[key] = -1;
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
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int* ret = NULL;
    int i, temp;
    MyHashMap* new = NULL;

    new = myHashMapCreate();
    ret = malloc(2, sizeof(int));
    ret[0] = ret[1] = -1;
    *returnSize = 2;
    for(i = 0; i < numsSize; i++)
    {
        temp = myHashMapGet(new, nums[i] + DELTA);
        if(temp != -1)
        {
            ret[0] = temp;
            ret[1] = i;
            break;
        }
        else
            myHashMapPut(new, target - nums[i] + DELTA, i);
    }

    myHashMapFree(new);
    return ret;

}

/* 36-164(<26%)-187.9 , on May 30th, 2021 */

=================================================================
==29==ERROR: AddressSanitizer: allocator is out of memory trying to allocate 0x1dcd65004 bytes
    #0 0x7f4fd8529bc8 in malloc (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8)
    #4 0x7f4fd78e40b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
==29==HINT: if you don't care about these errors you may set allocator_may_return_null=1
SUMMARY: AddressSanitizer: out-of-memory (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8) in malloc
==29==ABORTING
