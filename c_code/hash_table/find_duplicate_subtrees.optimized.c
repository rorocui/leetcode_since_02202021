#define LIST_SIZE       401
#define DELTA           200
#define STRING_SIZE     40000
#define NODE_SIZE       10000
#define INIT_NUM        -1
#define INIT_TREE_NODE  210
#define NUM_REPLACE_ZERO 201


typedef struct {
    char* val;
    bool checked;
    struct TreeNode* tree_ptr;
    struct MyLinkedList* next;
} MyLinkedList;

struct StringTreeNode {
    int val;
    char *stree;
    struct TreeNode* tree;
    struct StringTreeNode *left;
    struct StringTreeNode *right;
};

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

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, struct StringTreeNode* root) 
{
    //printf("%s:0x%x\n", __func__, obj);
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;
    
    if(obj && obj->val[0] != INIT_NUM)
    {
        end = myLinkedListCreate(STRING_SIZE);
        strcpy(end->val, root->stree);
        //printf("not root:%s\n", end->val); 
        end->tree_ptr = root->tree;
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
        strcpy(obj->val, root->stree);
        //printf("root:%s\n", obj->val); 
        obj->tree_ptr = root->tree;
        //printf("save tree node 0x%x\n", obj->tree_ptr);
    }
}


/** check if list contains tree root
 *  return stree for string coverted from tree
 *  return null, if not contains or contains but has been checked.
 *  return tree node pointer of duplicated tree node, if contains and not checked yet. **/
struct TreeNode* myLinkedListContain(MyLinkedList* obj, struct StringTreeNode* root, int* checked)
{
    //printf("%s:0x%x:0x%x\n", __func__, root, stree);
    MyLinkedList* ptr = obj;

    //printf("target:[%d]-%s\n", len, stree);
    while(ptr)
    {
        if(!strcmp(ptr->val, root->stree))
	    {
            //printf("found one[checked:%d]:%s:0x%x\n", ptr->checked, ptr->val, ptr->tree_ptr);
            //if(ptr->tree_ptr->left) printf("found:0x%x-%d\n", ptr->tree_ptr->left, ptr->tree_ptr->left->val);
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

void treeHashSetAdd(TreeHashSet* obj, struct StringTreeNode* root) 
{
    //printf("%s####0x%x:%d\n", __func__, root, root->val);
    myLinkedListAddAtTail(obj->arr[root->val + DELTA], root);
}

struct TreeNode* treeHashSetContain(TreeHashSet* obj, struct StringTreeNode* root, int* checked)
{
    //printf("%s:%d:0x%x:0x%x\n", __func__, root->val, obj, obj->arr[root->val + DELTA]);
    return myLinkedListContain(obj->arr[root->val + DELTA], root, checked); 
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

struct StringTreeNode* stringTreeNodeCreate()
{
    struct StringTreeNode *new = malloc(sizeof(struct StringTreeNode));

    new->val =  INIT_TREE_NODE;
    new->stree = new->left = new->right = NULL;

    return new;
}

struct StringTreeNode* copyTreeToStringTree(struct TreeNode* root)
{
    //printf("%s:0x%d\n", __func__, root->val);
    struct StringTreeNode *new = malloc(sizeof(struct StringTreeNode));
    int len = 0;

    new->stree = malloc(STRING_SIZE * sizeof(char));
    if(root->left)
    {
        new->left = copyTreeToStringTree(root->left);
        if(new->left->stree)
        {
            strcpy(new->stree, new->left->stree);
            len += strlen(new->left->stree);
        }
        else   
            printf("left stree is NULL, error\n");
    }
    else
    {
        sprintf(new->stree, "%c", 'n');
        new->left = NULL;
        len++;
    }
    //printf("L:Get node string is %s[%d] at 0x%x[%d]\n", new->stree, len, new, root->val);
    if(root->right)
    {
        new->right = copyTreeToStringTree(root->right);
        if(new->right->stree)
        {
            //printf("R:%s[%d?%d]\n", new->right->stree, len, strlen(new->right->stree));
            strcpy(new->stree + len, new->right->stree);
            len += strlen(new->right->stree);
        }
        else   
            printf("right stree is NULL, error\n");
    }
    else
    {
        sprintf(new->stree + len, "%c", 'n');
        new->right = NULL;
        len++;
    }
    //printf("R:Get node string is %s[%d] at 0x%x[%d]\n", new->stree, len, new, root->val);
    /* handle root */
    /* replace value 0 by NUM_REPLACE_ZERO for regular string access */
    if(root->val != 0)
        sprintf(new->stree + len, "%04d", root->val);
    else
        sprintf(new->stree + len, "%04d", NUM_REPLACE_ZERO);
    new->val = root->val;
    new->tree = root;
    len += 4;
    

    //printf("ROOT:Get node string is %s[%d?%d] at 0x%x[%d]\n", new->stree, len, strlen(new->stree), new, new->val);
    //if(new->left) printf("0x%x,%d\n", new->left, new->left->val);

    //printf("new=0x%x\n", new);
    return new;
}

int searchTree(TreeHashSet* obj, struct StringTreeNode* root, int pre_count)
{
    //printf("%s:0x%x:%d\n", __func__, root, pre_count);
    //printf("0x%x\n", stree);
    int checked = 0;
    int count = 0; 
    
    /* process root node */
    new[pre_count + count] = treeHashSetContain(obj, root, &checked);
    if(new[pre_count +count ] != NULL) 
        count++; /* find one duplicated subtree, and store in new[count] */
    else if(checked != 1)
        treeHashSetAdd(obj, root);
    else
        ;

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
    TreeHashSet*    hash_tree      = NULL;
    struct StringTreeNode* new_root    = NULL;
    int i = 0;

    hash_tree = treeHashSetCreate();
    new = malloc(NODE_SIZE * sizeof(struct TreeNode*));
    //printf("%s:0x%x\n", __func__, new);
    for(i = 0; i < NODE_SIZE; i++)
    {
        new[i] = NULL;
    }

    new_root = copyTreeToStringTree(root);
    //printf("new_root = 0x%x\n", new_root);
    *returnSize = searchTree(hash_tree, new_root, 0);

    treeHashSetFree(hash_tree);
    //printf("return 0x%x[%d]\n", new, *returnSize);

    return new;
    
}

/* Time Limit Exceeded  on Jun 26th, 2021*/

/* 114-1288(n/a)-321.8 , on Jun 19, 2021 */

