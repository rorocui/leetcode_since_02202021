/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* createNewNode(int val)
{
    struct TreeNode* new = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    new->val = val;
    new->left = new->right = NULL;

    return new;
}

struct TreeNode* insertIntoBST(struct TreeNode* root, int val)
{
    if(!root) return createNewNode(val);
    if(root->val > val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);

    return root;
}
/* beat 73% on Jun 4th, 2022 */
