/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/* return height of a tree */
/* since height would >= 0 for actual height of a tree */
/* I define another value -1 for false binary tree return */
int is_balanced_or_height(struct TreeNode* root){
    int left_height = -2, right_height = -2;

    if(! root) return 0;

    left_height = is_balanced_or_height(root->left);
    //printf("%#x:left=%d\n", root->left, left_height);
    if(left_height == -1) return -1;

    right_height = is_balanced_or_height(root->right);
    //printf("%#x:right=%d\n", root->right, right_height);
    if(right_height == -1) return -1;

    if(abs(right_height - left_height) > 1) return -1;

    return (right_height > left_height) ? right_height + 1 : left_height + 1;
}

bool isBalanced(struct TreeNode* root){
    int ret = -2;

    ret = is_balanced_or_height(root);
    if(ret == -1)
        return false;
    else
        return true;
}

/* beat 58% on Aug 27th, 2022 */
