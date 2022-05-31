/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int height_of_tree(struct TreeNode* root)
{
    int left = 0, right = 0;

    if(! root) return 0;
    if(root->left)
        left = height_of_tree(root->left);
    if(root->right)
        right = height_of_tree(root->right);

    if(right > left)
        return right + 1;
    else
        return left + 1;
}

/*
typedef struct {
    struct TreeNode** tree_array;
    int current;
} TreeStack;
*/

typedef struct 
{
    //struct TreeStack tree_stack;
    struct TreeNode** tree_array;
    int current;
} BSTIterator;


BSTIterator* bSTIteratorCreate(struct TreeNode* root) 
{
    int height = height_of_tree(root);
    BSTIterator* iterator;
    struct TreeNode* temp;

    iterator = (BSTIterator*)malloc(sizeof(BSTIterator));
    iterator->tree_array = (struct TreeNode**)malloc(height * sizeof(struct TreeNode*));
    iterator->current = 0;
    /* push the tree root down to stack */
    *(iterator->tree_array) = root;
    temp = root;
    
    /* push the left side to leaf node  to stack */
    while(temp->left)
    {
        /* push the left node to stack */
        *(iterator->tree_array + iterator->current + 1) = temp->left;
        //printf("push %d\n", temp->left->val);
        iterator->current++;
        temp = temp->left;
    }

    return iterator;
}

int bSTIteratorNext(BSTIterator* obj) 
{
    struct TreeNode* temp;
    int ret = 0;

    if(obj->current < 0)
        return -1;
    temp = *(obj->tree_array + obj->current);
    ret = temp->val;
    if(temp->right)
    {
        /* push the right child node and overwrite its parent node in stack*/
        *(obj->tree_array + obj->current) = temp->right;
        temp = temp->right;
        while(temp->left)
        {
            /* push the left node to stack */
            *(obj->tree_array + obj->current + 1) = temp->left;
            //printf("push %d\n", temp->left->val);
            obj->current++;
            temp = temp->left;
        }
    }
    else
        /* pop temp from stack */
        obj->current--;

    //printf("pop  %d\n", ret);
    return ret;
}

bool bSTIteratorHasNext(BSTIterator* obj) 
{
    if(obj->current >= 0)
        return true;
    else
        return false;
}

void bSTIteratorFree(BSTIterator* obj) 
{
    if(obj->tree_array)
        free(obj->tree_array);
    if(obj)
        free(obj);
    
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 
 * bool param_2 = bSTIteratorHasNext(obj);
 
 * bSTIteratorFree(obj);
*/
/* beat 73% on May 26th, 2022 */

