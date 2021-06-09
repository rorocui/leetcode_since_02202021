#define SIZE 50000
//#define DELTA 1000000000
//#define BUCKET_SIZE 10000
#define INIT_NUM 0
#define ERROR_CODE 0xFFFFFFFF
#define MIN_INT_32 0xFFFFFFFF

typedef struct {
    int* ptr;
    int count;
    
} MyHashMap;

/** Initialize your data structure here. */

MyHashMap* myHashMapCreate() 
{
    int i;
    MyHashMap* ret = malloc(sizeof(MyHashMap));
    
    ret->ptr = malloc(sizeof(int) * SIZE);
    for(i = 0; i < SIZE; i++)
        ret->ptr[i] = INIT_NUM;
    count = 0;
    
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
void myHashMapPut(MyHashMap* obj, int key) 
{
    int ret = 0;

    ret = myHashMapGet(obj, key);
    if(ret == 0)
    {
        obj->count++;
        obj->ptr[key] = obj->count;
    }
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

/* 36-164(<26%)-187.9 , on May 30th, 2021 */

