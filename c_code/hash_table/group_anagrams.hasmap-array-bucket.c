#define LETTER_SIZE     26
#define KEY_SIZE        26
#define LIST_SIZE       10000
#define STRING_SIZE     100
#define INIT_NUM        0
#define INIT_KEY        0x7F
#define DELTA           1000000000
#define BUCKET_SIZE     10000
#define NOT_FOUND       0x80000000
#define ERROR_CODE      0x80000000
#define MIN_INT_32      0x80000000
#define MAX_INT_32      0x7FFFFFFF
#define FALSE_CODE      0x80000000

typedef struct {
    int* ptr;
    int count;
    
} MyHashMap;

/** Initialize your data structure here. */

MyHashMap* myHashMapCreate() 
{
    int i;
    MyHashMap* ret = malloc(sizeof(MyHashMap));
    
    ret->ptr = malloc(sizeof(int) * LETTER_SIZE);
    for(i = 0; i < LETTER_SIZE; i++)
        ret->ptr[i] = INIT_NUM;
    ret->count = 0;
    
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
    //printf("%s:%d\n", __func__, key);
    (obj->count)++;
    (obj->ptr[key])++;
    //printf("%d:%d\n", obj->count, obj->ptr[key]);
}

void myHashMapFree(MyHashMap* obj) {
    if(obj)
    {
        if(obj->ptr) free(obj->ptr);
        free(obj);
    }
}


/* DEBUG purpose only */
void printKey(char* key)
{
    int len = strlen(key) < KEY_SIZE ? strlen(key) : KEY_SIZE;
    for(int i = 0; i < len; i++)
        if(key[i] > 0) printf("[%d]%d-", i, key[i]);
    printf("\n");
}

/* Definition for final quiz */

typedef struct {
    char* val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate(int size) 
{
    //printf("%s:%d\n", __func__, size);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val  = calloc(size, sizeof(char));
    new->val[0] = INIT_KEY;
    new->next = NULL;
    return new;
}

bool keyCmp(char* char1, char* char2)
{
    for(int i = 0; i < KEY_SIZE; i++)
    {
        if(char1[i] != char2[i])
            return false;
    }
    return true;
}

void keyCpy(char* dest, char* src)
{
    for(int i = 0; i < KEY_SIZE; i++)
        dest[i] = src[i];
}
int myLinkedListAddKey(MyLinkedList* obj, char* key) 
{
    //printf("%s:0x%x\n", __func__, obj);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    int index = 0;
    
    //printKey(key);
    //printKey(obj->val);
    //printf("val[0]=%d\n", obj->val[0]);
    if(obj && obj->val[0] != INIT_KEY)
    {
        //printf("cpy in new node\n");
        end = myLinkedListCreate(STRING_SIZE);
        keyCpy(end->val, key);
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
            index++;
        }
        ptr->next = end;
        index++;
    }
    else
    {
        //printf("cpy to root\n");
        keyCpy(obj->val, key);
        //printKey(obj->val);
    }

    return index;
}

/** Append a node of value val to the last element of the linked list. */
int myLinkedListAddAtTail(MyLinkedList* obj, char* val) 
{
    //printf("%s:0x%x\n", __func__, obj);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    int index = 0;
    
    //printKey(val);
    //printKey(obj->val);
    if(obj && obj->val[0] != INIT_KEY)
    {
        end = myLinkedListCreate(STRING_SIZE);
        strcpy(end->val, val);
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
            index++;
        }
        ptr->next = end;
        index++;
    }
    else
    {
        //printf("copy... %d:%d\n", strlen(obj->val), strlen(val));
        strcpy(obj->val, val);
        //printKey(obj->val);
    }

    return index;
}


/** check if list contains key
 *  return list node  index **/
int myLinkedListContain(MyLinkedList* obj, char* val)
{
    MyLinkedList* ptr = obj;
    int index = 0;

    //printf("%s:0x%x\n", __func__, obj);
    //printKey(val);
    //printKey(ptr->val);
    if(keyCmp(ptr->val, val)) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        //printKey(val);
        //printKey(ptr->val);
        if(keyCmp(ptr->val, val)) return index;
    }
    //printKey(obj->val);
    return NOT_FOUND;
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;

    while(obj)
    {
        ptr = obj->next;
        if(obj->val) free(obj->val);
        free(obj);
        obj = ptr;
    }
}

typedef struct 
{
    MyLinkedList** arr;
    int* count;
} AnagramsHashSet;

AnagramsHashSet* anagramsHashSetCreate() 
{
    //printf("%s\n", __FUNCTION__);
    AnagramsHashSet* obj = malloc(sizeof(AnagramsHashSet));
    int j; 

    obj->arr = malloc(sizeof(MyLinkedList*) * LIST_SIZE);
    obj->count = malloc(sizeof(int) * LIST_SIZE);
    for(j = 0; j < LIST_SIZE; j++)    
    {
        obj->arr[j] = myLinkedListCreate(STRING_SIZE);
        obj->count[j] = 0;
    }
    return obj;
}

static MyLinkedList* list_key;
static list_key_count;

/* key would be char[7] to present occurance numbers(0 <= n <= 100=0x64)
 * each low case letter could take two digits hex. and total 26 letters
 * need 52 hex, plus 4 hex alignment, that would 7 chars to pressent unique key 
 * of one string. return index of key stored in linked list - list_key */
int anagramsHashFun(char *str)
{
    MyHashMap* hash_fun = NULL;
    int i, index = 0, val = 0, len = 0;
    char*  ret = calloc(KEY_SIZE, sizeof(char));

    //printf("%s:%d:%s:0x%x:%d\n", __func__, __LINE__, str, str, strlen(str));
    hash_fun = myHashMapCreate();
    //printf("0x%x\n", hash_fun);
    //printf("%c\n", str[0]);
    //printf("%s:%d\n", __func__, __LINE__);
    //printf("%s:%d:%d:%c\n", __func__, __LINE__, strlen(str), str[0]);
    len = strlen(str);
    for(i = 0; i < len; i++)
    {
        //printf("%c.", str[i]);
        myHashMapPut(hash_fun, (int)(str[i] - 'a'));
    }
    for(i = 0; i < len; i++)
    {
        val = myHashMapGet(hash_fun, (int)(str[i] - 'a'));
        //printf("[%d]val=%d\n", (str[i] - 'a'), val);
        ret[(int)(str[i] - 'a')] = val;
    }
    //printKey(ret);
    
    /* check if key 'ret' stored in key list or not */
    index = myLinkedListContain(list_key, ret);
    //printf("Contain ret=%d(0x%x)\n", index, index);
    if(index == NOT_FOUND)
    {
        index = myLinkedListAddKey(list_key, ret);
        list_key_count++;
    }

    myHashMapFree(hash_fun);
    if(ret) free(ret);
    //printf("%s:index=%d\n", __func__, index);
    return index;
}


void anagramsHashSetAdd(AnagramsHashSet* obj, char* key) 
{
    //printf("%s####%s####0x%x:%d\n", __func__, key, key, strlen(key));
    int index = anagramsHashFun(key);
    myLinkedListAddAtTail(obj->arr[index], key);
    (obj->count[index])++;
}

void anagramsHashSetFree(AnagramsHashSet* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < LIST_SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj->count) free(obj->count);
    if(obj) free(obj);
} 

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    AnagramsHashSet* hash_words = NULL;
    int i, j;
    char*** ret = NULL;
    MyLinkedList* ptr = NULL;
    int* return_size = NULL;
    
    list_key = myLinkedListCreate(KEY_SIZE);
    hash_words = anagramsHashSetCreate();
    list_key_count = 0;
    for(i = 0; i < strsSize; i++)
        anagramsHashSetAdd(hash_words, strs[i]);

    ret = malloc(list_key_count * sizeof(char**));
    *returnSize = list_key_count;
    //printf("list_key_count=%d\n", list_key_count);
    return_size = calloc(list_key_count, sizeof(int));
    for(i = 0; i < list_key_count; i++)
    {
        return_size[i] = hash_words->count[i];
        //printf("[%d] count is %d\n", i, hash_words->count[i]);
        ret[i] = malloc(hash_words->count[i] * sizeof(char*));
        ptr = (hash_words->arr)[i];
        for(j = 0; j < hash_words->count[i]; j++)
        {
           ret[i][j] = malloc(STRING_SIZE * sizeof(char));
           strcpy(ret[i][j], ptr->val);
           //printf("[%d][%d]:%s->%s\n", i, j, ptr->val, ret[i][j]);
           ptr = ptr->next;
        }/*for hash_words->count[i] */
    }/* for list_key_count */
    

    *returnColumnSizes = return_size;
    anagramsHashSetFree(hash_words);
    myLinkedListFree(list_key);

    return ret;
}


/* 114-1288(n/a)-321.8 , on Jun 19, 2021 */

