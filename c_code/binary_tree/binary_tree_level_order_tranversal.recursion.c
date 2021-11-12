int count_depth(struct TreeNode *root)
{
    int ldepth = 0,
        rdepth = 0;

    if(! root)
        return 0;

    ldepth = count_depth(root->left);
    rdepth = count_depth(root->right);

    return (ldepth > rdepth) ? ldepth + 1 : rdepth + 1;

}

void addnum(int size, int** array, int val, int level)
{
    array[level] = (int*)realloc(array[level], size * sizeof(int));
    array[level][size - 1] = val;
}

void level_order_traversal(struct TreeNode* root, int* returnColumnSizes, int** array, int level)
{
    if(! root) return;
    returnColumnSizes[level] += 1;
    addnum(returnColumnSizes[level], array, root->val, level);
    level_order_traversal(root->left, returnColumnSizes, array, level + 1);
    level_order_traversal(root->right, returnColumnSizes, array, level + 1);

}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int** array = NULL;
    int depth = 0;

    *returnSize = depth = count_depth(root);
    //printf("%#x, %#x\n", returnColumnSizes, *returnColumnSizes);
    *returnColumnSizes = (int*)calloc(depth, sizeof(int));
    //printf("%#x, %#x\n", returnColumnSizes, *returnColumnSizes);
    array = (int**)calloc(depth, sizeof(int*));
    level_order_traversal(root, *returnColumnSizes, array, 0);

    return array;

}
/* 34 - 4(<88%) - 7.5MB, Nov 11th, 2021 */
/* 34 - 0(<100%) - 7.5MB, Nov 11th, 2021 */
