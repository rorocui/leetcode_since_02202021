/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int maxDepth(struct TreeNode* root)
{
    int dLeft, dRight; 

    dLeft = dRight = 0;
    if(! root) return 0;

    if(root->left) dLeft = maxDepth(root->left);
    if(root->right) dRight = maxDepth(root->right);

    if(dLeft > dRight)
        return dLeft + 1;
    else
        return dRight + 1;

}
/* 39 - 6ms(<31%) - 8MB, On Oct 2nd, 2021 */
/* Check child tree is_NULL before call maxDepth,
  39 - 4ms(<89%) - 7.9MB, on Oct 2nd, 2021 */
