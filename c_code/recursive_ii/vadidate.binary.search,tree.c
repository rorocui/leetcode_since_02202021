/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MIN_INT_32 0xFFFFFFFF
#define MAX_INT_32 0x7FFFFFFF

int find_BST_max_node(struct TreeNode* root)
{
    struct TreeNode* ptr = root;
    while(ptr->right)
        ptr = ptr->right;

    return ptr->val;
}

int find_BST_min_node(struct TreeNode* root)
{
    struct TreeNode* ptr = root;
    while(ptr->left)
        ptr = ptr->left;

    return ptr->val;
}

bool isValidBST(struct TreeNode* root)
{
    int min, max;
    //printf("%#x,root=%d\n", root, root->val);

    min = MAX_INT_32;
    max = MIN_INT_32;
    if(!root) return true;
    if(root->left)
    {   
        if(! isValidBST(root->left))
        {
            //printf("left is NOT BST\n");
            return false;
        }
        max = find_BST_max_node(root->left);
        //printf(">max=%d\n", max);
        if(root->val <= max)
        {
            //printf("in:>max=%d\n", max);
            return false;
        }
    }
    if(root->right)
    {   
        if(! isValidBST(root->right))
        {
            //printf("right is NOT BST\n");
            return false;
        }
        min = find_BST_min_node(root->right);
        //printf("<min=%d\n", min);
        if(root->val >= min)
        {
            //printf("in:<min=%d\n", min);
            return false;
        }
    }
    //printf("true\n");
    return true;
}
/* 80 - 0ms(<100%) - 8.9MB, on Aug 29th, 2021 */
