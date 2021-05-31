/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* searchBST(struct TreeNode* root, int val){
    struct TreeNode* ret = NULL;
    
    if(root->val == val)
        return root;
    else
    {
        if(root->left) ret = searchBST(root->left, val);
        if(ret) return ret;
        if(root->right) ret = searchBST(root->right, val);
        if(ret) return ret;
    }
    
    return NULL;
}
/* 36 test cases in 28ms(<8%), in 15.2MB, on May 29th, 2021*/
