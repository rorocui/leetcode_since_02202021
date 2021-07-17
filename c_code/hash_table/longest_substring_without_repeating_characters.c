//#define DELTA 1000000000
//#define BUCKET_SIZE 10000
#define SIZE        256
#define INIT_NUM    -1
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

void myHashMapReset(MyHashMap* obj)
{
    for(int i = 0; i < SIZE; i++)
        obj->ptr[i] = INIT_NUM;
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) 
{
    //printf("key = %d\n", key);
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
    //printf("put: key-val = %d-%d\n", key, val);
    obj->ptr[key] = val;
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

int lengthOfLongestSubstring(char * s)
{
    int start, end;
    int i;
    int ret;
    int count; 
    MyHashMap *hash_map = NULL;

    if(strlen(s) == 0) return 0;
    hash_map = myHashMapCreate();
    start = end = count = 0;

    for(i = 0; i < strlen(s); i++)
    {
        ret = myHashMapGet(hash_map, (int)s[i]);
        //printf("(%c)i = %d, start = %d, end = %d, ret = %d, count = %d\n", s[i], i, start, end, ret, count);
        if(ret == INIT_NUM)
            myHashMapPut(hash_map, (int)s[i], i);
        else
        {
            //printf("count=%d(%d-%d)\n", count, end, start);
            count = count > (end - start + 1) ? count : (end - start + 1);
            //printf("count=%d\n", count);
            i = ret;
            start = ret + 1;
            myHashMapReset(hash_map);
        }
        //printf("i=%d\n", i);
        end = i;
    }
    //printf("count=%d(%d-%d)\n", count, end, start);
    count = count > (end - start + 1) ? count : (end - start + 1);

    myHashMapFree(hash_map);

    return count;

}

/* 987-1352(n/a)-7.4 , on July 16th, 2021 */
