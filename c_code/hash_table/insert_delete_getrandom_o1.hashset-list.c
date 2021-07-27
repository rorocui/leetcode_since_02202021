#define SIZE        128
#define MAX_INT_32  0x7FFFFFFF 

typedef struct {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = MAX_INT_32;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
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
        ptr->next = end;
    }
    else
    {
        obj->val = val;

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
                free(ptr);
            }
            else
            {
                obj->val = -1;
            }
        }
    }

}

/** check if list contains value */
int myLinkedListContain(MyLinkedList* obj, int value)
{
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->val == value) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->val == value) return index;
    }
    return -1;
}

/** Get the value of the index-th node in the linked list.
 * If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) 
{
    MyLinkedList* ptr = NULL;
    int i;

    //printf("%s:0x%x\n", __func__, obj);
    if(obj)
        ptr = obj;
    else
        return -1;
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
    if(i == index && ptr)
    {
        //printf("%s:%d\n", __func__, ptr->val);
        return ptr->val;
    }
    else
    {
        return -1;
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


typedef struct 
{
    MyLinkedList** arr;
    int* count;
} MyHashSet;


MyHashSet* myHashSetCreate() 
{
    //printf("%s\n", __FUNCTION__);
    MyHashSet* obj = malloc(sizeof(MyHashSet));
    int j; 

    obj->arr = malloc(sizeof(MyLinkedList*) * SIZE);
    for(j = 0; j < SIZE; j++)    
    {
        obj->arr[j] = myLinkedListCreate();
    }
    obj->count = (int*)calloc(SIZE, sizeof(int));
    return obj;
}

int myHashSetFun(int key)
{
    return abs(key) % SIZE;
}

bool myHashSetContains(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    if(myLinkedListContain(obj->arr[myHashSetFun(key)], key) == -1) return false;
    else    return true;
}

void myHashSetAdd(MyHashSet* obj, int key) 
{
    int key_index = 0;
    
    key_index = myHashSetFun(key);
    myLinkedListAddAtTail(obj->arr[myHashSetFun(key)], key);
    *(obj->count + key_index) += 1;
}

bool myHashSetRemove(MyHashSet* obj, int key) 
{
    int index = 0; 
    int key_index = 0;

    key_index = myHashSetFun(key);
    index = myLinkedListContain(obj->arr[key_index],key);
    if(index != -1)
    {
        myLinkedListDeleteAtIndex(obj->arr[key_index], index);
        *(obj->count + key_index) -= 1;
        return true;
    }
    else
        return false;
}

int myHashSetGetNthValidKey(MyHashSet* obj, int index)
{
    //printf("%s:%d\n", __func__, index);
    int i;
    int count = index;

    for(i = 0; i < SIZE, count >= 0; i++)
    {
        //printf("[%d]%d-%d\n", i, *(obj->count + i), count);
        if(*(obj->count + i) < count) 
            count -= *(obj->count + i);
        else
        {
            //printf("count < count:[%d]%d\n", i, count);
            break;
        }
    }
    //printf("[%d]%d\n", i, count);
    return myLinkedListGet(obj->arr[i], count - 1);
}


void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj->count) free(obj->count);
    if(obj) free(obj);
} 

typedef struct {
    MyHashSet* hash_set;
    int count;
} RandomizedSet;

RandomizedSet* randomizedSetCreate()
{
    //printf("%s\n", __func__);
    RandomizedSet* new = NULL;
    
    new = malloc(sizeof(RandomizedSet));
    new->hash_set = myHashSetCreate();
    new->count = 0;
    
    return new;
}

bool randomizedSetInsert(RandomizedSet* obj, int val)
{
    //printf("%s\n", __func__);
    if(myHashSetContains(obj->hash_set, val))
        /* already contains this val */
        return false;
    else
    {
        myHashSetAdd(obj->hash_set, val);
        obj->count += 1;
        return true;
    }
}

bool randomizedSetRemove(RandomizedSet* obj, int val)
{
    //printf("%s\n", __func__);
    
    bool ret;
    
    ret = myHashSetRemove(obj->hash_set, val);
    if(ret) obj->count -= 1; 
    return ret;
}


int randomizedSetGetRandom(RandomizedSet* obj)
{
    //printf("%s:%d\n", __func__, obj->count);
    return myHashSetGetNthValidKey(obj->hash_set, (rand() % (obj->count)) + 1);
}

void randomizedSetFree(RandomizedSet* obj)
{
    //printf("%s\n", __func__);
    myHashSetFree(obj->hash_set);
    free(obj);
}
/* 19-300(<38%)-78.8, on July 265h,2021 */

