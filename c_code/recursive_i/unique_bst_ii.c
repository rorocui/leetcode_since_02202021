/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define SIZE 1500

struct TreeNode* treeNodeCreate()
{
    struct TreeNode* new = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    new->val = 0;
    new->left = new->right = NULL;

    return new;
}

int generateBSTRecursion(struct TreeNode** tree, int min, int max)
{
    //printf("%s:%#x[%d-%d]\n", __func__, tree, min, max);
    int i, m, n;
    int idx;
    int l_ret, r_ret;
    struct TreeNode** left  = NULL;
    struct TreeNode** right = NULL;

    idx = 0;
    l_ret = r_ret = 1;
    if(max == min)
    {
        tree[0] = treeNodeCreate();
        //printf("tree[%#x]**[%d]=%#x\n", tree, idx, tree[idx]);
        tree[0]->val = min;
        return 1;
    }
    for(i = min; i <= max; i++)
    {
        left = right = NULL;
        if( i > min)
        {
            left = (struct TreeNode**)malloc(SIZE * sizeof(struct TreeNode*));
            l_ret = generateBSTRecursion(left, min, i - 1);
            //printf("left (%d) returned.[%d-%d]\n", l_ret, min, i - 1);
        }
        if(i < max)
        {
            right = (struct TreeNode**)malloc(SIZE * sizeof(struct TreeNode*));
            r_ret = generateBSTRecursion(right, i + 1, max);
            //printf("right (%d)returned.[%d-%d]\n", r_ret, i + 1, max);
        }
        for(m = 1; m <= l_ret; m++)
        {
            for(n = 1; n <= r_ret; n++)
            {
                //printf("idx=%d[m/n=%d/%d]\n", idx, m, n);
                tree[idx] = treeNodeCreate();
                //printf("tree[%#x]**[%d]=%#x\n", tree, idx, tree[idx]);
                tree[idx]->val = i;
                if(left) tree[idx]->left = left[m - 1];
                if(right) tree[idx]->right = right[n - 1];
                idx++;
            }
        }
        //if(left) free(left);
        //if(right) free(right);
    }

    return idx;

}


void print_tree(struct TreeNode* root)
{
    printf("%s:%#x\n", root);
    if(root)
    {
        printf("[ %d ", root->val);
        if(root->left)
            printf("%d ", root->left->val);
        else
            printf("null ");
        if(root->right)
            printf("%d ", root->right->val);
        else
            printf("null ");
        if(root->left) print_tree(root->left);
        if(root->right) print_tree(root->right);
        printf(" ]\n");
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** generateTrees(int n, int* returnSize)
{
    struct TreeNode** new = NULL;

    new = (struct TreeNode**)malloc(SIZE * sizeof(struct TreeNode*));
    //printf("%s:%#x\n", __func__, new);
    *returnSize = generateBSTRecursion(new, 1, n);

    //printf("%#x,ret=%d\n", new, *returnSize);
    
    /*
    for(int i = 0; i < *returnSize; i++)
    {
        printf("new tree[%#x]**[%d]=%#x\n",new, i, new[i]);
        print_tree(new[i]); 
    }
    */

    return new;
}
/* 8 - 8ms(<100%) - 42.9, on Aug 9th 2021 */

