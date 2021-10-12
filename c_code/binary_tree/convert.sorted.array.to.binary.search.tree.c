/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
    struct TreeNode* root = NULL;

    if(numsSize < 0) return root;
    root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[numsSize / 2];
    if(numsSize > 1) root->left = sortedArrayToBST(nums, numsSize / 2);
    else root->left = NULL;
    if(numsSize / 2 + 1 < numsSize) root->right = sortedArrayToBST(&nums[numsSize / 2 + 1], numsSize - numsSize / 2 - 1 );
    else root->right = NULL;


    return root;
}
/* 31 - 8ms(<72%) - 16.3MB, on Oct 11th, 2021*/
