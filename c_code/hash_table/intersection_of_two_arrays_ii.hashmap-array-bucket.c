#define SIZE        1001
#define INIT_NUM    0
#define ERROR_CODE  0x80000000
#define MIN_INT_32  0x80000000

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
void myHashMapPut(MyHashMap* obj, int key, int operator) 
{
    obj->ptr[key] += operator;
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key) {
    if(obj)
        obj->ptr[key] = INIT_NUM;
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
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    MyHashMap* hash_nums1 = NULL;
    MyHashMap* hash_nums2 = NULL;
    int i, len, repeat, appear1, appear2;
    int* ret = NULL;
    int* num = NULL;

    hash_nums1 = myHashMapCreate();
    hash_nums2 = myHashMapCreate();
    ret = malloc(SIZE * sizeof(int));
    *returnSize = 0;

    for(i = 0; i < nums1Size; i++)
        myHashMapPut(hash_nums1, nums1[i], 1);
    for(i = 0; i < nums2Size; i++)
        myHashMapPut(hash_nums2, nums2[i], 1);
    if(nums1Size < nums2Size)
    {
        len = nums1Size;
        num = nums1;
    }
    else
    {
        len = nums2Size;
        num = nums2;
    }

    //printf("len = %d(%d?%d)\n", len, nums1Size, nums2Size);
    for(i = 0; i < len; i++)
    {
        appear1 = myHashMapGet(hash_nums1, num[i]);
        appear2 = myHashMapGet(hash_nums2, num[i]);
        myHashMapPut(hash_nums1, num[i], -1 * appear1);
        repeat = appear1 < appear2 ? appear1 : appear2;
        //printf("%d,%d,%d\n", repeat, appear1, appear2);
        while(repeat > 0)
        {
            *(ret + *returnSize) = num[i];
            (*returnSize)++;
            repeat--;
        }
    }

    myHashMapFree(hash_nums1);
    myHashMapFree(hash_nums2);
    return ret;

}
/* 55-4(93)-7 , on Jun 10th, 2021 */
