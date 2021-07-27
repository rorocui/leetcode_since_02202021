#define SIZE        128
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

bool myHashMapContains(MyHashMap* obj, int key)
{
    if(obj->ptr[key] == 0)  return false;
    else                    return true;
}
/** Count value accounting key and current count*/
void myHashMapPut(MyHashMap* obj, int key) 
{
    obj->ptr[key] = 1;
}

/** Count value accounting key and current count*/
void myHashMapRemove(MyHashMap* obj, int key) 
{
    obj->ptr[key] = 0;
}

int myHashMapGetNthValidKey(MyHashMap* obj, int index)
{
    int i;
    int count = index;

    for(i = 0; i < SIZE, count >= 0; i++)
        if(obj->ptr[i] == 1) count--;

    return i;
}

void myHashMapFree(MyHashMap* obj) {
    if(obj)
    {
        if(obj->ptr) free(obj->ptr);
        free(obj);
    }
}


typedef struct {
    MyHashMap* hash_map;
    int count;
} RandomizedSet;

RandomizedSet* randomizedSetCreate()
{
    RandomizedSet* new = NULL;
    
    new = malloc(sizeof(RandomizedSet));
    new->hash_map = myHashMapCreate();
    new->count = 0;
    
    return new;
}

bool randomizedSetInsert(RandomizedSet* obj, int val)
{
    if(myHashMapContains(obj->hash_map, val))
        /* already contains this val */
        return false;
    else
    {
        myHashMapPut(obj->hash_map, val);
        obj->count += 1;
        return true;
    }
}

bool randomizedSetRemove(RandomizedSet* obj, int val)
{
    if(myHashMapContains(obj->hash_map, val))
        /* already contains this val */
        return false;
    else
    {
        myHashMapRemove(obj->hash_map, val);
        obj->count -= 1;
        return true;
    }
}

int randomizedSetGetRandom(RandomizedSet* obj)
{
    return myHashMapGetNthValidKey(obj, (rand() % (obj->count)) + 1);
}

void randomizedSetFree(RandomizedSet* obj)
{
    myHashMapFree(obj->hash_map);
    free(obj);
}

/* 
 ==43==ERROR: AddressSanitizer: requested allocation size 0xfffffffffffffffc (0x800 after adjustments for alignment, red zones etc.) exceeds maximum supported size of 0x10000000000 (thread T0)
    #0 0x7f804f9e6bc8 in malloc (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8)
    #5 0x7f804eda10b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
==43==HINT: if you don't care about these errors you may set allocator_may_return_null=1
SUMMARY: AddressSanitizer: allocation-size-too-big (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8) in malloc
==43==ABORTING
*/
