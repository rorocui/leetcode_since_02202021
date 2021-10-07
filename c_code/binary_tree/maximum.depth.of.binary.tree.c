/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static int depth;

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

void maxDepth_top(struct TreeNode* root, int level)
{
    if(!root) return 0;
    if(!root->right && !root->left)
    {
        //printf("%d,%d\n", depth, level);
        depth = max(depth, level);
    }
    
    if(root->left) maxDepth_top(root->left, level + 1);
    if(root->right) maxDepth_top(root->right, level + 1);
}

int maxDepth(struct TreeNode* root){
    
    /* Top down */
    depth = 0;
    maxDepth_top(root, 1);
    
    return depth;
    /* 39 cases in 4ms, beats 93% on March 25th, 2021 */
    
    /* bottom up */
    /*
    int lheight = 0, rheight = 0;
    if(!root) return 0;
    if(!root->left && !root->right)
        return 1;
    lheight = maxDepth(root->left);
    rheight = maxDepth(root->right);
    if(lheight > rheight)
        return lheight + 1;
    else
        return rheight + 1;
     */    
    /* 39 cases in 4ms, beats 93% on March 25th, 2021 */
}
