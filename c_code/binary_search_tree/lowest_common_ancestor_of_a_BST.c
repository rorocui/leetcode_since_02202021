/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) 
{
    struct TreeNode* temp = root;
    int max, min;

    if(p->val > q->val)
    {
        max = p->val;
        min = q->val;
    }
    else
    {
        max = q->val;
        min = p->val;
    }

    while(temp->val > max || temp->val < min)
    {
        if(temp->val > max)
            temp = temp->left;
        if(temp->val < min)
            temp = temp->right;
    }

    return temp;
}
