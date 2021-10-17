
typedef struct 
{
    int *arr;
} MyHashSet;

#define HASH_INIT
#define SIZE 26

MyHashSet* myHashSetCreate() 
{
    MyHashSet* obj = malloc(sizeof(MyHashSet));
#ifdef HASH_INIT
    int i; 
    

    obj->arr = malloc(sizeof(int) * SIZE);
    for(i = 0; i < SIZE; i++)
        obj->arr[i] = 0;
#else
    obj->arr = calloc(SIZE, sizeof(int));
#endif
    return obj;
}

void myHashSetAdd(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    obj->arr[key] += 1;
}

void myHashSetMinus(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    obj->arr[key] -= 1;
}

bool myHashSetContainsNoZero(MyHashSet* obj) 
{
    //printf("%s:%d\n", __func__, key);
    int i;
    
    for(i = 0; i < SIZE; i++)
        if(obj->arr[i] != 0)
            return false;
    return true;
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 


bool isAnagram(char * s, char * t)
{
    int size;
    int i;
    MyHashSet* hashset_ptr = NULL;
    bool ret = false;

    hashset_ptr = myHashSetCreate();
    size = strlen(s);
    if(size != strlen(t))
        return ret;

    for(i = 0; i < size; i++)
    {
        myHashSetAdd(hashset_ptr, s[i] - 'a');
        myHashSetMinus(hashset_ptr, t[i] - 'a');
    }

    ret = myHashSetContainsNoZero(hashset_ptr);

    myHashSetFree(hashset_ptr);

    return ret;

}
/* 35 - 4 (<64%) - 5.9MB, on Oct 17th, 2021 */

