/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* searchParentBST(struct TreeNode* root, struct TreeNode** parent, int val)
{
    struct TreeNode* target = root;

    if(!root)
    {
        *parent = NULL;
        return NULL;
    }
    *parent = target;
    while(target)
    {
        if(target->val == val)
            return target;
        else if(target->val > val)
        {
            *parent = target;
            target = target->left;
        }
        else
        {
            *parent = target;
            target = target->right;
        }
    }
    
    *parent = NULL;
    return NULL;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key)
{
    struct TreeNode* target = NULL;
    struct TreeNode** parent = NULL;
    struct TreeNode* temp = NULL;
    struct TreeNode* temp_parent = NULL;

    parent = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    target = searchParentBST(root, parent, key);
    
    //printf("%#x, %#x\n", target, *parent);
    if(!target) return root;
    if(target->right && target->left)
    {
        /* Search leftmost's parent in its right subtree */
        temp = target->right;
        temp_parent = target;
        while(temp->left)
        {
            temp_parent = temp;
            temp = temp->left;
        }
        /* temp is the leftmost node of target's right subtree */
        temp->left = target->left;
        if(temp_parent->left == temp)
            temp_parent->left = NULL;
        else
            temp_parent->right = NULL;
        /* Since temp_parent is not needed after set its child 
            use it here for searching temp's rightmost leaf node */
        temp_parent = temp;
        if(target->right != temp)
        {
            while(temp_parent->right)
                temp_parent = temp_parent->right;
            temp_parent->right = target->right;
        }
        if(target == *parent)
        {
            free(target);
            return temp;
        }
        else
        {
            if((*parent)->left == target)
                (*parent)->left = temp;
            else
                (*parent)->right = temp;
            free(target);
            return root;
        }
    }
    else if(target->right)
    {
        if(target == *parent)
        {
            temp = target->right;
            free(target);
            return temp;
        }
        else
        {
            if((*parent)->left == target)
                (*parent)->left = target->right;
            else
                (*parent)->right = target->right;
            free(target);
            return root;
        }
    }
    else if(target->left)
    {
        if(target == *parent)
        {
            temp = target->left;
            free(target);
            return temp;
        }
        else
        {
            if((*parent)->left == target)
                (*parent)->left = target->left;
            else
                (*parent)->right = target->left;
            free(target);
            return root;
        }
    }
    else
    {
        if(target == *parent)
        {
            free(target);
            return NULL;
        }
        else
        {
            if((*parent)->left == target)
                (*parent)->left = NULL;
            else
                (*parent)->right = NULL;
            free(target);
            return root;
        }
    }

}
/* beat 38% on Jun 7th, 2022 */
