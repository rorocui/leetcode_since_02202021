#define SIZE            128
#define ERROR_CODE      -1
#define MIN_INT_32      0x80000000
#define MAX_INT_32      0x7FFFFFFF

typedef struct {
    int key;
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->key = new->val = MIN_INT_32;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int key, int val) 
{
    //printf("%s:0x%x:%#x:%d\n", __func__, obj, key, val);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    if(obj->key != MIN_INT_32)
    {
        end = myLinkedListCreate();
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        end->val = val;
        end->key = key;
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        obj->key = key;
    }
}

/* update (key, val) -> val + 1 */
void myLinkedListUpdate(MyLinkedList* obj, int key)
{
    //printf("%s:0x%x,%#x\n", __func__, obj, key);
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
    printf("failed to find the key, error\n");
}    

int myLinkedListGetVal(MyLinkedList* obj, int key)
{
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

/** check if list contains key
 *  return list node  index **/
int myLinkedListContain(MyLinkedList* obj, int key)
{
    //printf("%s:0x%x,%d\n", __func__, obj, key);
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key)
    {
        return index;
    }
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key)
        {
            return index;
        }
    }
    return ERROR_CODE;
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
} MyHashMap;

MyHashMap* myHashMapCreate() 
{
    //printf("%s\n", __FUNCTION__);
    MyHashMap* obj = malloc(sizeof(MyHashMap));
    int j; 

    obj->arr = malloc(sizeof(MyLinkedList*) * SIZE);
    for(j = 0; j < SIZE; j++)    
    {
        obj->arr[j] = myLinkedListCreate();
    }
    return obj;
}

int myHashMapFun(int key)
{
    return abs(key) % SIZE;
}

void myHashMapPut(MyHashMap* obj, int key) 
{
    int index = 0; 

    index = myLinkedListContain(obj->arr[myHashMapFun(key)],key);
    if(index != ERROR_CODE)
        myLinkedListUpdate(obj->arr[myHashMapFun(key)], key);
    else
        myLinkedListAddAtTail(obj->arr[myHashMapFun(key)], key, 1);
}

int myHashMapGet(MyHashMap* obj, int key)
{
    
   return myLinkedListGetVal(obj->arr[myHashMapFun(key)], key);
}

void myHashMapFree(MyHashMap* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

int fourSumCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size)
{
    int i, j;
    int ret = 0;
    int count = 0;
    MyHashMap * hash_map = NULL;


    hash_map = myHashMapCreate();
    //printf("%#x,%#x\n", hash_set, hash_set->arr[0x1fff]);
    for(i = 0; i < nums1Size; i++)
        for(j = 0; j < nums2Size; j++)
    {
        myHashMapPut(hash_map, (nums1[i] + nums2[j]));
    }
    for(i = 0; i < nums3Size; i++)
        for(j = 0; j < nums4Size; j++)
    {
        count = myHashMapGet(hash_map, (-1 *(nums3[i] + nums4[j])));
        if(count != ERROR_CODE) 
            ret += count;
    }

    myHashMapFree(hash_map);
    return ret;
}

/* 132-1680(n/a)-237.7, on July 19th, 2021 */
/* mod fun  132-716ms(n/a)-236, on July 19th, 2021*/
/* SIZE=128 132-84ms(n/a)-8.5MB, on July 26th, 2021*/
