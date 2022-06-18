struct CTreeNode {
    int val;
    int count;
    struct CTreeNode* left;
    struct CTreeNode* right;
};


typedef struct {
    struct CTreeNode* root;
    int k;
} KthLargest;

struct CTreeNode* NewNode(int val)
{
    struct CTreeNode* ret = (struct CTreeNode*)malloc(sizeof(struct CTreeNode));
    ret->val = val;
    ret->count = 0;
    ret->left = ret->right = NULL;

    return ret;
}

/* tree root could be null */
bool InsertInBST(struct CTreeNode* root, int val);
{
    if(root->val == val)    
        return false;
    else if(root->val > val)
        InsertInBST(root->left, val);
    else 
        root->right = InsertInBST(root->right, val);
    (root->count)++;

    return root;
}


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) 
{
    int i;
    KthLargest* ret = (KthLargest*)malloc(sizeof(KthLargest));
    ret->root = NewNode(nums[0]);
    ret->k = k;
    
    for(i = 1; i < numsSize; i++)
    {
        InsertInBST(ret->root, nums[i]);
        printf("create node %d(vs %d), count is %d\n", ret->root->val, nums[i], ret->root->count);
    }

}

int KthLargestinBST(struct CTreeNode* root, int k)
{
    printf("root(%d)/count(%d)-k(%d)\n", root->val, root->count, k);
    if(root->count == k)
        return root->val;
    else if(root->count > k)
    {
        if(root->right && root->right->count >= k)
            return KthLargestinBST(root->right, k);
        else if(root->right && k == root->right->count + 1)
            return root->val;
        else if(root->right && root->right->count < k)
            return KthLargestinBST(root->left, k - 1 - root->right->count);
        else if(k == 1)
            return root->val;
        else
            return KthLargestinBST(root->left, k - 1);
    }
    printf("That is error, the tree doesn't contain more than k=%d(root->count=%d) nodes\n", k, root->count);
    return -10001;
}

int kthLargestAdd(KthLargest* obj, int val) 
{
    obj->root = InsertInBST(obj->root, val);
    printf("create node %d(vs %d), count is %d\n", obj->root->val, val, obj->root->count);
    return KthLargestinBST(obj->root, obj->k);
}

void FreeBST(struct CTreeNode* root)
{
    if(root->right)
        FreeBST(root->right);
    if(root->left)
        FreeBST(root->left);
    free(root);
}

void kthLargestFree(KthLargest* obj) 
{
    if(obj->root) FreeBST(obj->root);
    if(obj) free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/
