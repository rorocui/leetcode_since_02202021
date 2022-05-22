/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int find_max_child(struct TreeNode* root)
{
    struct TreeNode* temp = root;

    while(temp->right)
        temp = temp->right;

    return temp->val;
}

int find_min_child(struct TreeNode* root)
{
    struct TreeNode* temp = root;

    while(temp->left)
        temp = temp->left;

    return temp->val;
}

bool isValidBST(struct TreeNode* root)
{
    int min = INT_MIN, max = INT_MAX;

    if(! root) return false;

    //printf("root=%d\n", root->val);
    if(root->right)
    {
        if(!isValidBST(root->right))
            return false;
        min = find_min_child(root->right);
        //printf("min=%d\n", min);
        if(root->val >= min )
            return false;
    }

    if(root->left)
    {
        if(!isValidBST(root->left))
            return false;
        max = find_max_child(root->left);
        //printf("max=%d\n", max);
        if(root->val <= max)
            return false;
    }

    return true;
}

/* Beat 75% */

