#define BUCKET_SIZE     100000
#define ERROR_CODE      0x80000000
#define MIN_INT_32      0x80000000
#define MAX_INT_32      0x7FFFFFFF
#define FALSE_CODE      0x80000000
#define MULTI_KEYS      100001
#define ZERO            0

typedef struct {
    int key;
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->key = MIN_INT_32;
    new->val = ZERO;
    new->next = NULL;
    return new;
}

void myLinkedListUpdate(MyLinkedList* obj, int key)
{
    //printf("%s:0x%x-%d-%d\n", __func__, obj, key);
    //printf("obj->val:%d\n", obj->val);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key)
    {
        (ptr->val)++;
        return;
    }
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key)
        {
            (ptr->val)++;
            return;
        }
    }
    
    /* not existing key, add it to list */
    if(obj->key != MIN_INT_32)
    {
        end = myLinkedListCreate();
        ptr->val = 1;
        ptr->key = key;
        ptr->next = end;
    }
    else
    {
        obj->val = 1;
        obj->key = key;
    }
}

int myLinkedListGetVal(MyLinkedList* obj, int key)
{
    //printf("%s:%#x,%d\n", __func__, obj, key)
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key) return ptr->val;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key) return ptr->val;
    }
    return ERROR_CODE;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddCountKey(MyLinkedList* obj, int key, int val) 
{
    //printf("%s:0x%x-%d-%d\n", __func__, obj, key, val);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    
    if(obj && obj->key != MIN_INT_32)
    {
        end = myLinkedListCreate();
        end->val = val;
        end->key = key;
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        obj->key = key;
    }
}

/* return val, if key is unique, otherwise return MULTI_KEYS */
int myLinkedListCountGetVal(MyLinkedList* obj, int key)
{
    if(obj->key != MIN_INT_32 && obj->next) return MULTI_KEYS;
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key) return ptr->val;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key) return ptr->val;
    }
    return ERROR_CODE;
}

int myLinkedListGetMultiVal(MyLinkedList* obj, int key, int* val)
{
    MyLinkedList* ptr = obj;
    int index = 0;

    while(ptr)
    {
        val[index++] = ptr->val;
        ptr = ptr->next;
    }
    return index;
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;

    //while(!EmptyList(obj->next))
    while(obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);

}

typedef struct 
{
    MyLinkedList** arr;
    int count;
    int* key_array;
} MyHashMap;

MyHashMap* myHashMapCreate(int size) 
{
    //printf("%s\n", __FUNCTION__);
    MyHashMap* obj = malloc(sizeof(MyHashMap));
    int j; 
    int init_num;

    obj->arr = malloc(sizeof(MyLinkedList*) * size);
    for(j = 0; j < size; j++)    
    {
        obj->arr[j] = myLinkedListCreate();
    }
    obj->count = 0;
    obj->key_array = (int*)calloc(size, sizeof(int));
    
    return obj;
}

int myHashMapFun(int key, int* count, int* key_array)
{
    int i;
    
    /*
    if(*count == -1) 
    {
        printf("return 0\n");
        key_array[0] = key;
        *count = 1;
        return 0;
    }
    */
    for(i = 0; i < *count; i++)
    {
        if(key_array[i] == key)
        {
            return i;
        }
    }
    key_array[*count] = key;
    (*count)++;
    return *count - 1;
}

void myHashMapUpdate(MyHashMap* obj, int key) 
{
    myLinkedListUpdate(obj->arr[myHashMapFun(key, &(obj->count), obj->key_array)], key);
}

int myHashMapGet(MyHashMap* obj, int key)
{
   return myLinkedListGetVal(obj->arr[myHashMapFun(key, &(obj->count), obj->key_array)], key);
}

/* this is for count hashmap, the key in [1,5000] */
void myHashMapCountPut(MyHashMap* obj, int key, int val) 
{
   myLinkedListAddCountKey(obj->arr[key], key, val);
}
/* return number if key is unique, return MULTI_KEYS if not */
int myHashMapCountGet(MyHashMap* obj, int key)
{
   return myLinkedListCountGetVal(obj->arr[key], key);
}

/* return numbers size */
int myHashMapCountMultiGet(MyHashMap* obj, int key, int* val)
{
   return myLinkedListGetMultiVal(obj->arr[key], key, val);
}

void myHashMapFree(MyHashMap* obj, int size) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < size; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj->key_array) free(obj->key_array);
    if(obj) free(obj);
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
    int max1, min1, max2;
    MyHashMap *hash_map = NULL;
    MyHashMap *sort_count = NULL;

    num = k_count = count = 0;
    max1 = max2 = MIN_INT_32;
    min1 = MAX_INT_32;
    ret = (int*)malloc((k + 1) * sizeof(int));
    for(i = 0; i < numsSize; i++)
    {
        //printf("[%d]%d\n", i, nums[i]);
        max1 = nums[i] > max1 ? nums[i] : max1;
        min1 = nums[i] < min1 ? nums[i] : min1;
    }
    hash_map = myHashMapCreate(max1 - min1 + 1);
    sort_count = myHashMapCreate(SORT_SIZE);
    for(i = 0; i < numsSize; i++)
    {
        //printf("[%d]%d\n", i, nums[i]);
        myHashMapUpdate(hash_map, nums[i]);
    }
    //printf("min1=%d,max1=%d\n", min1, max1);
    for(i = min1; i <= max1; i++)
    {
        count = myHashMapGet(hash_map, i);
        //printf("[%d]%d\n", i, count);
        if(count != ERROR_CODE)
        {
            //printf("[%d]%d\n", i, count);
            myHashMapCountPut(sort_count, count, i);
            max2 = count > max2 ? count : max2;
        }
    }
    //printf("max2=%d\n", max2);
    for(i = max2; i >= 0 && k_count < k; i--)
    {
       num = myHashMapCountGet(sort_count, i);
       //printf("[%d]%d\n",i , num);
       if(num == MULTI_KEYS)
       {
           //printf("Multi:[%d]%d\n",i , num);
           //printf("Multi:[k_count:%d]%d\n",k_count, ret[k_count]);
           k_count += myHashMapCountMultiGet(sort_count, i, &ret[k_count]);
           //printf("Multi:[k_count:%d]%d\n",k_count, ret[k_count]);
       }
       else if(num != ERROR_CODE)
       {
           //printf("Count:[%d]%d\n",i , num);
           ret[k_count++] = num;
       }
    }

    *returnSize = k_count;
    //printf("ret size %d, ret = %d\n", *returnSize, ret[0]);

    myHashMapFree(hash_map, k);
    myHashMapFree(sort_count, SORT_SIZE);

    return ret;
}

/* 21 - 516ms(n/a) - 121.3MB on July 24th, 2021 */
