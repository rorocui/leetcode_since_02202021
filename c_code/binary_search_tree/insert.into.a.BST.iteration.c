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
    struct TreeNode* temp = root;

    if(!root) return createNewNode(val);

    while((temp->right && temp->val < val) || (temp->left && temp->val > val))
    {
        if(temp->right && temp->val < val)
            temp = temp->right;
        if(temp->left && temp->val > val)
            temp = temp->left;
    }
    if(temp->val > val)
        temp->left = createNewNode(val);
    else
        temp->right = createNewNode(val);

    return root;
}
/* beat 35% on Jun 4th, 2022 */
