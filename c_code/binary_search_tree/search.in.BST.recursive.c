/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* searchBST(struct TreeNode* root, int val)
{
    if(!root) return NULL;
    //printf("%#x-%d\n", root, root->val);
    if(root->val == val)
        return root;
    else if(root->val > val)
        if(root->left)
            return searchBST(root->left, val);
        else
            return NULL;
    else
        if(root->right)
            return searchBST(root->right, val);
        else    
            return NULL;
}
