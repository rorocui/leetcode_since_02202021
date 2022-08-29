/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* sortedArrayToBST(int* nums, int numsSize){

    struct TreeNode* node_ptr = NULL;

    node_ptr = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node_ptr->val = nums[numsSize / 2];

    if(numsSize > 1)
        node_ptr->left = sortedArrayToBST(nums, numsSize / 2);
    else
        node_ptr->left = NULL;

    if(numsSize - numsSize/2 - 1 > 0)
        node_ptr->right = sortedArrayToBST(&nums[numsSize / 2 + 1], numsSize - numsSize/2 - 1);
    else
        node_ptr->right = NULL;

    return node_ptr;

}
/* beats 75%, on Aug 28th, 2022 */
