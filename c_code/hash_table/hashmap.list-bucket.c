#define SIZE            200001
#define DELTA           1000000000
#define BUCKET_SIZE     10000
#define ERROR_CODE      0x80000000
#define MIN_INT_32    0x80000000
#define MAX_INT_32    0x7FFFFFFF
//#define MIN_INT_32      0
//#define MAX             1001
//#define NO_DUPLICATED   -1
#define FALSE_CODE    0x80000000
//#define STRING_SIZE   31  

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
        else /* index > 0 */
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

void myLinkedListUpdate(MyLinkedList* obj, int key, int val)
{
    //printf("%s:0x%x-%d-%d\n", __func__, obj, key, val);
    //printf("obj->val:%d\n", obj->val);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key)
    {
        ptr->val = val;
        return;
    }
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key)
        {
            ptr->val = val;
            return;
        }
    }
    
    /* not existing key, add it to list */
    if(obj->val != MIN_INT_32)
    {
        end = myLinkedListCreate();
        ptr->val = val;
        ptr->key = key;
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        obj->key = key;
    }
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
    MyLinkedList* ptr = obj;
    int index = 0;

    if(ptr->key == key) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(ptr->key == key) return index;
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
    for(j = 0; j < SIZE; j++)    
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
    myLinkedListUpdate(obj->arr[myHashMapFun(key)], key, val);
}

int myHashMapGet(MyHashMap* obj, int key)
{
    
   return myLinkedListGetVal(obj->arr[myHashMapFun(key)], key);
}

void myHashMapRemove(MyHashMap* obj, int key) 
{
    //if(key == 14498) printf("%s:%d\n", __func__, key);
    int index = 0; 

    index = myLinkedListContain(obj->arr[myHashMapFun(key)],key);
    if(index != ERROR_CODE)
        myLinkedListDeleteAtIndex(obj->arr[myHashMapFun(key)], index);
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

