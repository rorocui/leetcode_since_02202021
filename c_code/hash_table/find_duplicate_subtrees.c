#define LIST_SIZE       401
#define DELTA           200
#define STRING_SIZE     40000
#define NODE_SIZE       10000
#define INIT_NUM        -1


typedef struct {
    char* val;
    bool checked;
    struct TreeNode* tree_ptr;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate(int size) 
{
    //printf("%s:%d\n", __func__, size);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val  = calloc(size, sizeof(char));
    new->val[0] = INIT_NUM;
    new->tree_ptr = NULL;
    new->next = NULL;
    new->checked = false;
    return new;
}

int printTreeToString(struct TreeNode* root, char* stree)
{
    int count = 0;
    
    //printf("%s-[stree=0x%x]-%d-0x%x\n", __func__, stree, root->val, root);
    sprintf(stree + count, "%04d", root->val);
    count += 4;
    if(root->left)
        count += printTreeToString(root->left, stree + count);
    else
    {
        sprintf(stree + count, "%c", 'n');
        count++;
    }
    if(root->right)
        count += printTreeToString(root->right, stree + count);
    else
    {
        sprintf(stree + count, "%c", 'n');
        count++;
    }
    //printf("[%d]-%s\n", count, stree);

    return count;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, struct TreeNode* root, char* stree) 
{
    //printf("%s:0x%x\n", __func__, obj);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    int len = 0;
    
    if(obj && obj->val[0] != INIT_NUM)
    {
        end = myLinkedListCreate(STRING_SIZE);
        strcpy(end->val, stree);
        //printf("not root:%s\n", end->val); 
        end->tree_ptr = root;
        //printf("save tree node 0x%x\n", end->tree_ptr);
        ptr = obj;
        while(ptr->next)
        {
            ptr = (MyLinkedList*)ptr->next;
        }
        ptr->next = end;
    }
    else
    {
        //printf("copy... %d:%d\n", strlen(obj->val), strlen(val));
        strcpy(obj->val, stree);
        //printf("root:%s\n", obj->val); 
        obj->tree_ptr = root;
        //printf("save tree node 0x%x\n", obj->tree_ptr);
    }
}


/** check if list contains tree root
 *  return stree for string coverted from tree
 *  return null, if not contains or contains but has been checked.
 *  return tree node pointer of duplicated tree node, if contains and not checked yet. **/
struct TreeNode* myLinkedListContain(MyLinkedList* obj, struct TreeNode* root, char* stree, int* checked)
{
    //printf("%s:0x%x:0x%x\n", __func__, root, stree);
    MyLinkedList* ptr = obj;
    int len;
    
    len = printTreeToString(root, stree);
    //printf("target:[%d]-%s\n", len, stree);
    while(ptr)
    {
        if(!strcmp(ptr->val, stree))
	    {
            //printf("found one[checked:%d]:%s:0x%x\n", ptr->checked, ptr->val, ptr->tree_ptr);
            *checked = (int)ptr->checked;
	        if(!ptr->checked)
            {
                ptr->checked = true;
                //printf("return tree ptr\n");
	            return ptr->tree_ptr;
            }
	    }
        ptr = (MyLinkedList*)ptr->next;
    }
    return NULL;
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;

    while(obj)
    {
        ptr = (MyLinkedList*)obj->next;
        if(obj->val) free(obj->val);
        free(obj);
        obj = ptr;
    }
}

typedef struct 
{
    MyLinkedList** arr;
} TreeHashSet;

TreeHashSet* treeHashSetCreate() 
{
    //printf("%s\n", __FUNCTION__);
    TreeHashSet* obj = malloc(sizeof(TreeHashSet));
    int j; 

    obj->arr = malloc(sizeof(MyLinkedList*) * LIST_SIZE);
    for(j = 0; j < LIST_SIZE; j++)    
    {
        obj->arr[j] = myLinkedListCreate(STRING_SIZE);
    }
    return obj;
}

//static MyLinkedList* list_key;
//static list_key_count;

void treeHashSetAdd(TreeHashSet* obj, struct TreeNode* root, char* stree) 
{
    //printf("%s####%s####0x%x:%d\n", __func__, key, key, strlen(key));
    myLinkedListAddAtTail(obj->arr[root->val + DELTA], root, stree);
}

struct TreeNode* treeHashSetContain(TreeHashSet* obj, struct TreeNode* root, char* stree, int* checked)
{
    return myLinkedListContain(obj->arr[root->val + DELTA], root, stree, checked); 
}

void treeHashSetFree(TreeHashSet* obj) 
{
    //printf("%s\n", __func__);
    int i;

    for(i = 0; i < LIST_SIZE; i++)
	    if(obj->arr[i]) myLinkedListFree(obj->arr[i]);

	if(obj->arr) free(obj->arr);
    if(obj) free(obj);
} 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static struct TreeNode** new;    

int searchTree(TreeHashSet* obj, struct TreeNode* root, int pre_count)
{
    //printf("%s:0x%x:%d\n", __func__, root, pre_count);
    char* stree = malloc(STRING_SIZE * sizeof(char));
    //printf("0x%x\n", stree);
    int checked = 0;
    int count = 0; 
    
    /* process root node */
    new[pre_count + count] = treeHashSetContain(obj, root, stree, &checked);
    if(new[pre_count +count ] != NULL) 
        count++; /* find one duplicated subtree, and store in new[count] */
    else if(checked != 1)
        treeHashSetAdd(obj, root, stree);
    else
        ;
    free(stree);

    /* process left sub tree */
    if(root->left) count += searchTree(obj, root->left, pre_count + count);
    /* process right sub tree */
    if(root->right) count += searchTree(obj, root->right, pre_count + count);
    
    //printf("found %d\n", count);
    return count;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize)
{
    TreeHashSet* hash_tree = NULL;
    int i = 0;

    hash_tree = treeHashSetCreate();
    new = malloc(NODE_SIZE * sizeof(struct TreeNode*));
    for(i = 0; i < NODE_SIZE; i++)
    {
        new[i] = NULL;
    }

    *returnSize = searchTree(hash_tree, root, 0);

    treeHashSetFree(hash_tree);

    return new;
    
}

/* Time Limit Exceeded  on Jun 26th, 2021*/

/* 114-1288(n/a)-321.8 , on Jun 19, 2021 */

