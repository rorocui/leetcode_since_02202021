typedef struct 
{
    int *arr;
} MyHashSet;

//#define HASH_INIT
#define SIZE 256

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
    obj->arr[key]++;
}

int myHashGet(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    return obj->arr[key];
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

int numJewelsInStones(char *jewels, char *stone)
{
    int i; 
    MyHashSet * hash_set = NULL;
    int count = 0; 


    hash_set = myHashSetCreate();
    for(i = 0; i < strlen(stone); i++)
        myHashSetAdd(hash_set, (int)(stone[i] - 'A'));

    for(i = 0; i < strlen(jewels); i++)
        count += myHashGet(hash_set, (int)(jewels[i] - 'A'));

    myHashSetFree(hash_set);

    return count;
}

/* 32-88(<52%)-43.4, on May 30th, 2021 */
