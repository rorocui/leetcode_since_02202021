/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int tree_height(struct TreeNode* root)
{
    int lheight = 0, rheight = 0;
    if(!root) return 0;
    if(!root->left && !root->right)
        return 1;
    lheight = tree_height(root->left);
    rheight = tree_height(root->right);
    if(lheight > rheight)
        return lheight + 1;
    else
        return rheight + 1;
}

void count_Tree_Node(struct TreeNode* root, int* length)
{
    //printf("1.%lx-%d\n", root, *length);
    if(root != NULL)
    {
        //printf("1.%d\n", *length);
        (*length)++;
        if(root->left) count_Tree_Node(root->left, length);
        if(root->right) count_Tree_Node(root->right, length);
    }
}

/* return child number in total in level 'height' */
int count_child_in_level(struct TreeNode* root, int offset, int height)
{
    printf("root=%lx\n", root);
    if(!root) return offset;
    if(height == 1)
        return ++offset;
    else if(height > 1)
    {
        offset = count_child_in_level(root->left, offset, height -1);
        offset = count_child_in_level(root->right, offset, height -1);
        return offset;
    }
    else
    {
        /* error */
        return -1;
    } 
}
/* return array offset */ 
int level_order_traversal(struct TreeNode* root, int array_offset, int* array, int height)
{
    if(!root) return array_offset;
    //printf("offset=%d,height=%d,array=%lx\n", array_offset, height, array);
    if(height == 1)
    {
        *(array + array_offset) = root->val;
        array_offset++;
        //printf("0.return = %d\n", array_offset);
        return array_offset;
    }
    else if(height > 1)
    {
        array_offset = level_order_traversal(root->left, array_offset, array, height -1);
        array_offset = level_order_traversal(root->right, array_offset, array, height -1);
        //printf("1.return = %d\n", array_offset);
        return array_offset;
    }
    else
    {
        /* error */
        return -1;
    }
} 

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    printf("root=%lx\n", root);
    int height = 0, i = 0, temp = 0; 
    int child_count = 0;
    int** newarray = NULL;
    printf("newarray = %lx,%d\n", &newarray, newarray);
    
    *returnSize = 0;
    if(!root) return NULL;
    height = tree_height(root); 
    count_Tree_Node(root, returnSize);
    printf("tree height is %d, size=%d\n", height, *returnSize);
    
    int* array[height]; 
    int* ColumnSizes[height];
    newarray = &array;
    returnColumnSizes = &ColumnSizes;
    printf("array = %lx,%lx,%lx\n", array, &array, array[0]);
    printf("newarray = %lx,%lx,%lx\n", &newarray, newarray, *newarray);
    
    for( i = 0; i < height; i++)
    {
        child_count = count_child_in_level(root, 0, i + 1); 
        //printf("child is %d\n", child_count);
        array[i] = (int*)malloc(sizeof(int) * child_count);
        *array[i] = 0;
        //printf("array[%d]=%lx,%d\n", i, array[i], *array[i]);
        //printf("newarray = %lx,%lx,%lx,%lx\n", &newarray, newarray, *newarray, **newarray);
        ColumnSizes[i] = (int*)malloc(sizeof(int));
        *(ColumnSizes[i]) = level_order_traversal(root, 0, array[i], i + 1);
        /*
        temp = levelordertraversal(root, 0, array[i], i + 1);
        printf("temp=%d\n", temp);
        *(ColumnSizes[i]) = temp;
        printf("ColumnSize[%d]=%d,%lx\n", i, *(ColumnSizes[i]), ColumnSizes[i]);
        */
    }
    printf("%d,%d,%d\n", **returnColumnSizes, **(returnColumnSizes + 1), **(returnColumnSizes + 2));
    printf("newarray = %lx,%lx,%lx\n", &newarray, newarray, *newarray);
    for(i = 0; i < height; i++)
    {
        printf("[");
        for(int j = 0; j < **(returnColumnSizes + i); j++)
            printf("%d,", *(*(newarray + i) + j));
        printf("]\n");  
        
    }
    
    printf("newarray = %lx,%lx,%lx\n", &newarray, newarray, *newarray);
    return newarray;
    //return NULL;

}
/* 34 cases in 8ms, used 8MB, beats 28% on April 14th, 2021 */
