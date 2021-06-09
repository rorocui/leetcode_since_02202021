#define SIZE        26
//#define DELTA 1000000000
//#define BUCKET_SIZE 10000
#define INIT_NUM    0
#define ERROR_CODE  0x80000000
#define MIN_INT_32  0x80000000
#define MAX_INT     100001
#define INIT        -1

typedef struct {
    int* ptr;
    int index;
    
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
    /* update val(index) to first accurrance charator */
    if(obj->ptr[key] == 0)
        obj->ptr[key] = val;
    else
        /*if accurance happens, set mapping val to MIN_INT_32 for Not used flag */
        obj->ptr[key] = MIN_INT_32;
}

/** find minimium index(val) in current array, except 0 and MIN_INT_32 **/
int myHashMapFindMinVal(MyHashMap* obj)
{
    int i;
    int ret = MAX_INT;

    for(i = 0; i < SIZE; i++)
    {
        if(obj->ptr[i] != 0 && obj->ptr[i] != MIN_INT_32)
            ret = ret < obj->ptr[i] ? ret : obj->ptr[i];
    }

    return ret;
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

int firstUniqChar(char *s)
{
    MyHashMap* hash_new = NULL;
    int i;
    int ret = INIT;

    hash_new = myHashMapCreate();
    for(i = 0; i < strlen(s); i++)
    {
        myHashMapPut(hash_new, s[i], i);
    }

    ret = myHashMapFindMinVal(hash_new);
    myHashMapFree(hash_new);

    return ret;
}

/* 36-164(<26%)-187.9 , on May 30th, 2021 */

