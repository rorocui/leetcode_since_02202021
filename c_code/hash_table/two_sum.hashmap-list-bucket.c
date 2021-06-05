#define SIZE 100001
#define DELTA 1000000000
#define BUCKET_SIZE 10000
#define ERROR_CODE 0xFFFFFFFF
#define MIN_INT_32 0xFFFFFFFF

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
void myLinkedListAddAtTail(MyLinkedList* obj, int key, int val) {
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    if(obj)
    {
        end = myLinkedListCreate();
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->val = val;
        ptr->key = key;
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        ptr->key = key;

    }
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* temp = NULL;
    int i;

    if(obj)
    {
        if(index > 0)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(ptr->next)
                {
                    ptr = ptr->next;
                    i++;
                }
                else
                    break;
            }
            if(i == index - 1)
            {
                if(ptr->next)
                {
                    temp = ptr->next;
                    ptr->next = temp->next;
                }
                free(temp);
            }
        }
        else
        {
            if(obj->next)
            {
                ptr = obj->next;
                obj->next = ptr->next;
                obj->val = ptr->val;
                obj->key = ptr->key;
                free(ptr);
            }
            else
            {
                obj->key = obj->val = MIN_INT_32;
            }
        }
    }

}

/** check if list contains key
 *  return list node  index **/
int myLinkedListContain(MyLinkedList* obj, int key)
{
    //printf("%s: 0x%x: key=%d\n", __func__, obj, key);
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key) return index;
    }
    return ERROR_CODE;
}

/** Get the value of the index-th node in the linked list.
 * If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) 
{
    MyLinkedList* ptr = NULL;
    int i;

    //printf("%s:0x%x:%d\n", __func__, obj, index);
    if(obj)
        ptr = obj;
    else
        return ERROR_CODE;
    for(i = 0; i < index;)
    {
        if(ptr->next)
        {
            ptr = ptr->next;
            i++;
        }
        else
            break;
    }
    //printf("%s:0x%x\n", __func__, obj);
    //printf("i=%d\n", i);
    if(i == index && ptr)
    {
        //printf("%s:%d\n", __func__, ptr->val);
        return ptr->val;
    }
    else
    {
        return ERROR_CODE;
    }
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

void myLinkedListPrint(MyLinkedList* obj)
{
    MyLinkedList* ptr = obj;
    printf("Linked list(0x%x):", obj);
    while(ptr)
    {
       printf("%d->", ptr->val); 
       ptr = ptr->next; 
    }
    printf("\n");
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
    for(j = 0; j < BUCKET_SIZE; j++)    
    {
        obj->arr[j] = myLinkedListCreate();
    }
    return obj;
}

int myHashMapFun(int key)
{
    return (key + DELTA) % BUCKET_SIZE;
}

void myHashMapPut(MyHashMap* obj, int key, int val) 
{
    //printf("%s:%d\n", __func__, key);
    myLinkedListAddAtTail(obj->arr[myHashMapFun(key)], key, val);
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) 
{
    int index = 0; 

    index = myLinkedListContain(obj->arr[myHashMapFun(key)],key);
    //printf("%s:index=%d\n", __func__, index);
    if(index != ERROR_CODE)
        return myLinkedListGet(obj->arr[myHashMapFun(key)], index);
    else
    {
        //printf("failed to find key\n");
        return ERROR_CODE;
    }
}


void myHashMapRemove(MyHashMap* obj, int key) 
{
    int index = 0; 

    index = myLinkedListContain(obj->arr[myHashMapFun(key)],key);
    if(index != ERROR_CODE)
        myLinkedListDeleteAtIndex(obj->arr[myHashMapFun(key)], index);
}

void myHashMapFree(MyHashMap* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < BUCKET_SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int* ret = NULL;
    int i, temp;
    MyHashMap* new = NULL;

    new = myHashMapCreate();
    ret = malloc(2 * sizeof(int));
    ret[0] = ret[1] = MIN_INT_32;
    *returnSize = 2;
    for(i = 0; i < numsSize; i++)
    {
        temp = myHashMapGet(new, nums[i]);
        if(temp != ERROR_CODE)
        {
            ret[0] = temp;
            ret[1] = i;
            break;
        }
        else
            myHashMapPut(new, target - nums[i], i);
    }

    myHashMapFree(new);
    return ret;

}


/* 54-92(<17%)-40.8, on Jun 5nd, 2021 */
