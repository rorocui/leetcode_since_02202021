typedef struct 
{
    struct TreeNode* node;
    struct MyLinkedList* next;
} MyLinkedList;

typedef struct 
{
    MyLinkedList* que;
    int  currentSize;
} MyCQue;


/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() 
{
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->node = NULL;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, struct TreeNode* node) 
{
    MyLinkedList* end = NULL;
    MyLinkedList* ptr = NULL;

    //printf("%s:0x%x:%d\n", __func__, obj, val);
    if(obj)
    {
        end = myLinkedListCreate();
        ptr = obj;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->node = node;
        ptr->next = end;
    }
    else
    {
        obj->node = node;

    }
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* ptr = NULL;

    //while(!EmptyList(obj->next))
    while(obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);

}

/** Remove top of linked list and return it **/
struct TreeNode* myLinkedListGetTop(MyLinkedList* obj) 
{
    MyLinkedList* ptr = NULL;
    struct TreeNode* ret = NULL;

    if(! obj) return NULL;
    ptr = obj->next;
    obj->next = ptr->next;
    ret = obj->node;
    obj->node = ptr->node;

    if(ptr) free(ptr);
    return ret;
}


MyCQue* myCQueCreate() 
{
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->que = myLinkedListCreate();
    obj->currentSize = 0;
    
    return obj;
}

bool myCQueEnQue(MyCQue* obj, struct TreeNode* node) 
{
    //printf("EnQue-%#x\n", node);
    myLinkedListAddAtTail(obj->que, node);
    obj->currentSize++;
    return true;
}

struct TreeNode* myCQueDeQue(MyCQue* obj) 
{
    struct TreeNode*  ret = NULL;

    if(obj->currentSize > 0)
    {
        obj->currentSize--;
        ret = myLinkedListGetTop(obj->que);
        //printf("DeQue-%d\n", ret);
        return ret;
    }
    else
    {
        //printf(" Empty queue, can't Deque\n");
        return NULL;
    }

}

bool myCQueIsEmpty(MyCQue* obj) {
    if(obj->currentSize)
        return false;
    else
        return true;
}

void myCQueFree(MyCQue* obj) {
    if(obj->que) myLinkedListFree(obj->que);
    if(obj) free(obj);
}

int count_depth(struct TreeNode *root)
{
    int ldepth = 0,
        rdepth = 0;

    if(! root)
        return 0;

    if(root->left) 
        ldepth = count_depth(root->left);
    if(root->right) 
        rdepth = count_depth(root->right);

    return (ldepth > rdepth) ? ldepth + 1 : rdepth + 1;

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int** array = NULL;
    int depth = 0,
        idx = 0,
        length = 1,
        i = 0;
    struct TreeNode* tree_ptr = NULL;
    MyCQue* tree_que = NULL;
    MyCQue* swap_que = NULL;


    tree_que = myCQueCreate();
    swap_que = myCQueCreate();
    *returnSize = depth = count_depth(root);
    //printf("%#x, %#x\n", returnColumnSizes, *returnColumnSizes);
    *returnColumnSizes = (int*)calloc(depth, sizeof(int));
    //printf("%#x, %#x\n", returnColumnSizes, *returnColumnSizes);
    array = (int**)calloc(depth, sizeof(int*));
    myCQueEnQue(tree_que, root);
    for(i; i < depth; i++)
    {
        (*returnColumnSizes)[i] = length;
        idx = 0;
        array[i] = (int*)calloc(length, sizeof(int));
        while(!myCQueIsEmpty(tree_que))
        {
            tree_ptr = myCQueDeQue(tree_que);
            array[i][idx++] = tree_ptr->val;
            if(tree_ptr->left)
                myCQueEnQue(swap_que, tree_ptr->left);
            if(tree_ptr->right)
                myCQueEnQue(swap_que, tree_ptr->right);
        }
        length = 0;
        while(! myCQueIsEmpty(swap_que))
        {
            length++;
            myCQueEnQue(tree_que, myCQueDeQue(swap_que));
        }
    }
        
    if(tree_que) myCQueFree(tree_que);
    if(swap_que) myCQueFree(swap_que);

    return array;

}
/* 34 - 0(<100%) - 7.1 MB, Nov 11th, 2021 */
