/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static int * newArray; 

void countTreeNode(struct TreeNode* root, int* length)
{
    if(root != NULL)
    {
        //printf("1.%d\n", *length);
        (*length)++;
        countTreeNode(root->left, length);
        countTreeNode(root->right, length);
    }
}

void inorderTree(struct TreeNode* root)
{
   if(root != NULL)
   {
        inorderTree(root->left);
        *newArray = root->val;
        //printf("1.%d-0x%lx\n", *newArray, newArray);
        newArray++;
        //printf("2.0x%lx\n", newArray);
        inorderTree(root->right);  
   } 
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    /* Recursive */

    int *head;
    
    if(!root) 
    {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 0;
    countTreeNode(root, returnSize);
    //printf("%d\n", *returnSize);
    head = newArray = (int*)malloc(sizeof(int)*(*returnSize));
    //printf("%d-0x%lx\n", *returnSize, newArray);
    
    inorderTree(root);

    return head;
    /* 68 cases in 0ms, beats ? on March 20th, 2021 */
}
