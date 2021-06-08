#define SIZE            26
#define DELTA           1000000000
#define BUCKET_SIZE     10
#define ERROR_CODE      0x80000000
#define MIN_INT_32    0x80000000
#define MAX_INT_32    0x7FFFFFFF
//#define MIN_INT_32      0
#define MAX             1001
#define NO_DUPLICATED   -1
#define FALSE_CODE    0x80000000
#define STRING_SIZE   31  

typedef struct {
    char* key;
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->key = malloc(sizeof(char) * STRING_SIZE); 
    new->val = MIN_INT_32;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, char* key, int val) {
    //printf("%s:0x%x:%s:%d\n", __func__, obj, key, val);
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
        strcpy(ptr->key, key);
        ptr->next = end;
    }
    else
    {
        obj->val = val;
        strcpy(ptr->key, key);

    }
}

/** check if list contains key
 *  return list node  index **/
int myLinkedListContain(MyLinkedList* obj, char* key)
{
    //printf("%s:0x%x:%s\n", __func__, obj, key);
    MyLinkedList* ptr = obj;
    int index = 0;

    if(!strcmp(ptr->key, key)) return index;
    while(ptr->next)
    {
        ptr = ptr->next;
        index++;
        if(!strcmp(ptr->key, key)) return index;
    }
    return FALSE_CODE;
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
        return FALSE_CODE;
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
/*
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
*/

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

int myHashMapFun(char* key)
{
    /*
    int ret = MIN_INT_32;
    
    ret = (int)key[0] - 0x41;
    printf("%s:%d\n", __func__, ret);
    return ret;
    */
    if((int)key[0] <= 0x5A)
        return (int)key[0] - 0x41;
    else
        return (int)key[0] - 0x61;
}

/* if duplicated, return current index sum(duplicate A + B)
 * if not, add new key to hashmap, and return  NO_DUPLICATED */
int myHashMapPut(MyHashMap* obj, char* key, int val) 
{
    //printf("%s:%d:%d\n", __func__, key, val);
    int ret_val;
    int index = ERROR_CODE;

    index = myLinkedListContain(obj->arr[myHashMapFun(key)], key);
    //printf("%s:index=%d\n", __func__, index);
    if(index == FALSE_CODE)
    {
        myLinkedListAddAtTail(obj->arr[myHashMapFun(key)], key, val);
        return NO_DUPLICATED;
    }
    else
    {
        ret_val = myLinkedListGet(obj->arr[myHashMapFun(key)], index);
        //printf("%s:ret_val=%d\n", __func__, ret_val);
        if(ret_val != ERROR_CODE)
            return val + ret_val;
        else
            return ERROR_CODE;
    }
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char ** findRestaurant(char ** list1, int list1Size, char ** list2, int list2Size, int* returnSize)
{
    MyLinkedList* result_list = NULL;
    MyLinkedList* list_ptr = NULL;
    MyHashMap* hashmap_new = NULL;
    int i;
    int min_index = MAX_INT_32;
    int ret_int = 0;
    char ** ret = NULL;
    bool second_loop = false;

    result_list = myLinkedListCreate();
    hashmap_new = myHashMapCreate();
    *returnSize = 0;

    for(i = 0; i < list1Size; i++)
    {
        //printf("[%d]=%s\n", i, list1[i]);
        myHashMapPut(hashmap_new, list1[i], i);
    }
    for(i = 0; i < list2Size; i++)
    {
        ret_int = myHashMapPut(hashmap_new, list2[i], i);
        //printf("ret_int=%d\n", ret_int);
        if(ret_int == ERROR_CODE)
        {
            printf("Hashmap put failed, stoped. \n");
            myLinkedListFree(result_list);
            myHashMapFree(hashmap_new);
            return NULL;
        }
        if(ret_int != NO_DUPLICATED) 
        {
            if(ret_int == min_index)
            {
                myLinkedListAddAtTail(result_list, list2[i], min_index); 
                (*returnSize)++;
                //printf("returnSize=%d\n", *returnSize);
            }
            else if(ret_int < min_index)
            {
                min_index = ret_int;
                myLinkedListFree(result_list);
                result_list = myLinkedListCreate();
                myLinkedListAddAtTail(result_list, list2[i], ret_int); 
                *returnSize = 1;
            }
            else
                ;
        } /* end if != NO_DUPLICATEd */
    } /* end for list2Size */

    list_ptr = result_list;
    /* malloc ret char** and copy the string list to it */
    ret = malloc(*returnSize * sizeof(char*));
    for(i = 0; i < *returnSize; i++)
    {
        ret[i] = (char*)malloc(STRING_SIZE * sizeof(char));
        //printf("[%d]%s\n", i, list_ptr->key);
        if(list_ptr) 
            strcpy(ret[i], list_ptr->key);
        else 
        {
            printf(" result list is NULL, something wrong.\n");
            break;
        }
        list_ptr = list_ptr->next;
    }

    myLinkedListFree(result_list);
    myHashMapFree(hashmap_new);
    return ret;

}

/* 136-100(<59%)-19.7, on Jun 7th, 2021 */
