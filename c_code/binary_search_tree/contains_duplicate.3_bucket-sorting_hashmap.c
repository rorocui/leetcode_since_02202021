#define SIZE            0x10000
#define DELTA           0x80000000
#define BUCKET_SIZE     0x10000
/* unsinged int         0x1_0000_0000 - 1 */
#define ERROR_CODE      -1
#define NULL_EXIST      0x0
#define MAX_UNSIGNED_INT    0xFFFFFFFF


typedef struct {
    unsigned int key;
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->key = new->val = 0;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
MyLinkedList* myLinkedListAddAtTail(MyLinkedList* obj, unsigned int key, int val) 
{
    //printf("%s:0x%x-%d-%d\n", __func__, obj, key, val);
    MyLinkedList* new = NULL;
    if(! obj)
    {
        new = myLinkedListCreate();
        new->key = key;
        new->val = val;
        return new;
    }
    
    MyLinkedList* ptr = NULL;
    MyLinkedList* end = NULL;

    end = myLinkedListCreate();
    end->val = val;
    end->key = key;
    ptr = obj;
    while(ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = end;

    return obj;
}



bool myLinkedListGetVal(MyLinkedList* obj, int key, int* ret)
{
    MyLinkedList* ptr = obj;
    bool find = false;

    if(ptr->key == key) 
    {
        find = true;
        *ret = ptr->val;
    }
    while(! find && ptr->next)
    {
        ptr = ptr->next;
        if(ptr->key == key) 
        {
            find = true;
            *ret = ptr->val;
        }
    }
    return find;
}

/* Check if list contains the val, if yes then delete it */
MyLinkedList* myLinkedListDelete(MyLinkedList* obj, int val)
{
    MyLinkedList* ptr = obj->next;
    MyLinkedList* temp = NULL;
    
    if(obj->val == val) 
    {
        /* ToDo, handle the deletion  of first node in only one node linked list */
        if(obj->next)
        {
            obj->val = ptr->val;
            obj->next = ptr->next;
            ptr->next = NULL;
            free(ptr);
            return obj;
        }
        else
        {
            free(obj);
            return NULL;
        }
    }
    temp = ptr->next;
    while(temp && temp->val != val)
    {
        ptr = ptr->next;
        temp = ptr->next;
    }
    if(ptr->next)
    {
        temp = ptr->next;
        ptr->next = temp->next;
        temp->next = NULL;
        free(temp);
    }
    return obj;
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
    /* ToDo, malloc linkedlist data structure on demand */
    for(j = 0; j < SIZE; j++)    
    {
        obj->arr[j] = NULL;
    }
    return obj;
}

unsigned int myHashMapFun(unsigned int key)
{
    return key % BUCKET_SIZE;
}

void myHashMapPut(MyHashMap* obj, unsigned int key, int val) 
{
    //printf("Put: key=%d, %d\n", key, val);
    obj->arr[myHashMapFun(key)] = myLinkedListAddAtTail(obj->arr[myHashMapFun(key)], key, val);
}

bool myHashMapGet(MyHashMap* obj, unsigned int key, int* ret)
{
    bool find = false; 
   
    /*
    printf("Get: key=%d, bucket-id=%d, obj-#%x\n", 
          key, myHashMapFun(key), obj->arr[myHashMapFun(key)]);
    */      
    if(! obj->arr[myHashMapFun(key)]) return false;

    find = myLinkedListGetVal(obj->arr[myHashMapFun(key)], key, ret);
    /*
    printf("Get: key=%d, find=%d, bucket-id=%d, ret=%d,obj-#%x\n", 
          key, find, myHashMapFun(key), *ret, obj->arr[myHashMapFun(key)]);
    */      
    return find;
}

void myHashMapRemove(MyHashMap* obj, unsigned int key, int val) 
{
    //printf("%s:%d\n", __func__, val);
    obj->arr[myHashMapFun(key)] = myLinkedListDelete(obj->arr[myHashMapFun(key)], val); 
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

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t)
{
    MyHashMap *phashmap = NULL;
    int i, win_size, remove_idx;
    unsigned int key;
    int get_val, get_val_pre, get_val_post;
    int bucket_size;
    bool ret;
    unsigned int* new_array = malloc(numsSize * sizeof(unsigned int));
    
    ret = false;
    key = 0;
    win_size = 0; /*for windows Size k counter */
    remove_idx = 0; /* for remove index */
    get_val = get_val_pre = get_val_post = 0;
    bucket_size = 0;
    phashmap = myHashMapCreate();
    for(i = 0; i < numsSize; i++)
        new_array[i] = nums[i] + DELTA; 
    for(i = 0; i < numsSize; i++)
    {
        if(t < INT_MAX)
            bucket_size = t + 1;
        else
            bucket_size = t;
        key = new_array[i] / bucket_size;
        if(win_size == k + 1)
        {
            //printf("remove:%d\n", new_array[remove_idx]/bucket_size);
            myHashMapRemove(phashmap, new_array[remove_idx] / bucket_size, nums[remove_idx]);
            remove_idx++;
            win_size--;
        }
        ret = myHashMapGet(phashmap, key, &get_val);
        if(ret)
        {
            myHashMapFree(phashmap);
            free(new_array);
            return true;
        }
        else
        {
            if(key > 0)                 
            {
                ret = myHashMapGet(phashmap, key - 1, &get_val_pre);
                if(ret && (labs((long)get_val_pre - nums[i]) <= t))
                {
                    myHashMapFree(phashmap);
                    free(new_array);
                    return true;
                }
            }
            if(key < (MAX_UNSIGNED_INT - 1))
            {
                ret = myHashMapGet(phashmap, key + 1, &get_val_post);
	            if(ret && labs((long)get_val_post - nums[i]) <= t)
	            {
	                myHashMapFree(phashmap);
                    free(new_array);
	                return true;
	            }
            }
            /* Done with adjacent buckets checking */
            win_size++;
            myHashMapPut(phashmap, key, nums[i]);
        }
    }
    myHashMapFree(phashmap);
    free(new_array);
    return false;
}

/* On Aug 17th, 2022, running time 49ms */
