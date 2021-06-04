#define SIZE 200001
#define BUCKET_SIZE 10000
#define DELTA 1000000000
#define MAX 0x7FFFFFFF

typedef struct {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = MAX;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    //if(val == 14498) printf("%s:0x%x:%d\n", __func__, obj, val);
    //if(val == 14498) myLinkedListPrint(obj);
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
    //if(val == 14498) {printf("after:\n"); myLinkedListPrint(obj);}
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* temp = NULL;
    int i;

    //if(obj == 0x6020000ee4b0) printf("%s:0x%x:%d\n", __func__, obj, index);
    //if(obj == 0x6020000ee4b0) myLinkedListPrint(obj);
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
                obj->val = 0;
            }
        }
    }

}

/** check if list contains value */
int myLinkedListContain(MyLinkedList* obj, int value)
{
    //printf("%s:0x%lx:%d\n", __func__, obj, value);
    MyLinkedList* ptr = obj;
    int index = 0;
    //myLinkedListPrint(obj);

    //printf("%d\n", ptr->val);
    if(ptr->val == value) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        //printf("%d,index=%d\n", ptr->val, index);
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
    return obj;
}

int myHashSetFun(int key)
{
    return (key + DELTA) % BUCKET_SIZE;
}

bool myHashSetContains(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    if(myLinkedListContain(obj->arr[myHashSetFun(key)], key) == -1) return false;
    else    return true;
}

void myHashSetAdd(MyHashSet* obj, int key) 
{
    //printf("%s:%d\n", __func__, key);
    if(!myHashSetContains(obj, key))
        myLinkedListAddAtTail(obj->arr[myHashSetFun(key)], key);
}

void myHashSetRemove(MyHashSet* obj, int key) 
{
    //if(key == 14498) printf("%s:%d\n", __func__, key);
    int index = 0; 

    index = myLinkedListContain(obj->arr[myHashSetFun(key)],key);
    if(index != -1)
        myLinkedListDeleteAtIndex(obj->arr[myHashSetFun(key)], index);
}

void myHashSetFree(MyHashSet* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

bool containsDuplicate(int* nums, int numsSize)
{
    MyHashSet* obj = NULL;
    int i;

    obj = myHashSetCreate();
    for(i = 0; i < numsSize; i++)
    {
        if(myHashSetContains(obj, nums[i]))
        {
            myHashSetFree(obj);
            return true;
        }
        else
            myHashSetAdd(obj, nums[i]);
    }

    myHashSetFree(obj);
    return false;
} 

/* 16-732(<42%)-180.8, on Jun 3rd, 2021 */
