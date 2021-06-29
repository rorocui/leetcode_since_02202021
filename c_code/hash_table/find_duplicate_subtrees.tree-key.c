/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define SIZE          100000000
#define BUCKET_SIZE   10000
#define DELTA         200  
#define MIN_INT_32    0x80000000
#define MIN_INT_64    0x8000000000000000
#define MAX_INT_32    0x7FFFFFFF
#define MAX_INT_64    0x7FFFFFFFFFFFFFFF
#define NOT_FOUND     -1
#define NODE_SIZE     10000

typedef struct {
    long key;
    int count;
    int id;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* new = NULL;
    
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));

    new->key    = MIN_INT_64;
    new->count  = 0;
    new->id     = MIN_INT_32;
    new->next   = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, long key, int id) 
{
    //printf("%s:0x%x-%d-%d\n", __func__, obj, key, val);
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
        ptr->key = key;
        ptr->count = 1;
        ptr->id = id;
        ptr->next = end;
    }
    else
    {
        obj->key = key;
        obj->count = 1;
        obj->id = id;
    }
}

/** check if list contains key
 *  return count and id in parameter **/
int myLinkedListContain(MyLinkedList* obj, long key, int* id)
{
    MyLinkedList* ptr = obj;
 
    //printf("%#lx vs %#lx\n", ptr->key, key);
    if(ptr->key == key)
    {
        ptr->count++;
        *id = ptr->id;
        return ptr->count;
    }
    while(ptr->next)
    {
        ptr = ptr->next;
        //printf("%#lx vs %#lx\n", ptr->key, key);
        if(ptr->key == key)
	    {
	        ptr->count++;
            *id = ptr->id;
	        return ptr->count;
	    }
    }
    return NOT_FOUND;
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

    obj->arr = malloc(sizeof(MyLinkedList*) * SIZE / BUCKET_SIZE);
    for(j = 0; j < (SIZE / BUCKET_SIZE); j++)    
    {
        obj->arr[j] = myLinkedListCreate();
    }
    return obj;
}

int myHashMapFun(long key)
{
    return key % BUCKET_SIZE;
}

void myHashMapPut(MyHashMap* obj, long key, int id) 
{
    myLinkedListAddAtTail(obj->arr[myHashMapFun(key)], key, id);
}

/* Return key ocurring times */
int myHashMapGet(MyHashMap* obj, long key, int* id)
{
    return myLinkedListContain(obj->arr[myHashMapFun(key)], key, id);
}

void myHashMapFree(MyHashMap* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < (SIZE / BUCKET_SIZE); i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

static int count;
static int id;

int searchTree(MyHashMap* obj, struct TreeNode* root, struct TreeNode** new)
{
    long key = 0;
    int ret = 0;
    int pre_id = -1;

    if(!root) return 0;

    key = (long)(root->val + DELTA) << 32 | (long)searchTree(obj, root->left, new) << 16 | searchTree(obj, root->right, new);
    
    //printf("key=%#llx\n", key);
    //printf("%#lx%lx\n", *(((int*)(&key))+1), key);
    
    ret = myHashMapGet(obj, key, &pre_id);
    if(ret == NOT_FOUND)
    {
        //printf("not found %#lx\n", key);
        id++;
        myHashMapPut(obj, key, id);
        return id;
    }
    if(ret == 2)
    {
        //printf("found %#lx\n", key);
        new[count] = root;
        //printf("new[%d] %#lx vs %#lx \n", count, new[count], root);
        count++;
        return pre_id;
    }
    if(ret > 2)
        return pre_id;
    return MIN_INT_32;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
    struct TreeNode**   new         = NULL;    
    MyHashMap*          hash_tree   = NULL;
    int i;

    hash_tree = myHashMapCreate();
    new = malloc(NODE_SIZE * sizeof(struct TreeNode*));
    //printf("%s:0x%x\n", __func__, new);
    for(i = 0; i < NODE_SIZE; i++)
    {
        new[i] = NULL;
    }
    count = id = 0;

    searchTree(hash_tree, root, new);

    *returnSize = count;
    myHashMapFree(hash_tree);

    //printf("count=%d\n", count);
    return new;
}

/* 175-300(n/a)-160.4 , on July 15th, 2021 */
