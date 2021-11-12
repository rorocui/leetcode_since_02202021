
#define LEN 101

typedef struct MyLinkedList{
    struct TreeNode*  val;
    struct MyLinkedList *next;   
    struct MyLinkedList *prev;   
} MyLinkedList;

typedef struct {
    MyLinkedList* list;
    MyLinkedList* current;
    unsigned int currentSize;
} MinStack;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __func__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));

    new->val = NULL;
    new->next = new->prev = NULL;
    return new; 
}

void myLinkedListFree(MyLinkedList* obj) {
    //printf("%s\n", __func__);
    MyLinkedList* ptr = NULL;
    
    while(!obj && !obj->next)
    {
        ptr = obj->next;
        free(obj);
        obj = ptr;
    }
    free(obj);
    
}

MinStack* minStackCreate() {
    //printf("%s\n", __func__);
    MinStack* new = NULL;

    new = (MinStack*)malloc(sizeof(MinStack));
    new->current = new->list = NULL;
    new->currentSize = 0;
    
    return new;
}

void minStackPush(MinStack* obj, struct TreeNode* val) {
    //printf("%s-obj:0x%lx,val:%d\n", __func__, obj, val);
    //printf("%s-val:%d\n", __func__, val);
    if(obj->list)
    {
        //printf("%s-list:0x%lx\n", __func__, obj->list);
        //printf("%s-current:0x%lx\n", __func__, obj->current);
        obj->current->next = myLinkedListCreate();
        obj->current->next->prev = obj->current;
        obj->current = obj->current->next;
        //printf("%s-after_current:0x%lx\n", __func__, obj->current);
    }
    else
    {
        obj->list = obj->current = myLinkedListCreate();
        //printf("%s-after_list:0x%lx\n", __func__, obj->list);
        //printf("%s-after_current:0x%lx\n", __func__, obj->current);
    }
    

    obj->current->val = val;
    obj->currentSize++;
    //printf("\n");
    ////printf("%s-%d\n", __func__, obj->currentSize);
}

struct TreeNode* minStackPop(MinStack* obj) {
    //printf("%s-obj:0x%lx\n", __func__, obj);
    MyLinkedList* new = NULL;
    struct TreeNode* ret = 0;

    ret = obj->current->val;
    if(obj->current != obj->list)
    {
        new = obj->current;
        obj->current = obj->current->prev;
        obj->current->next = NULL;
        free(new);
    }
    else
    {
        free(obj->current);
        obj->list = obj->current = NULL;
    }
    obj->currentSize--;
    
    //printf("%s-%d\n", __func__, ret);
    return ret;
    //printf("%s-%d\n", __func__, obj->currentSize);
}

bool minStackIsEmpty(MinStack* obj)
{
    //printf("%s-%d\n", __func__, obj->currentSize);
    if(obj->currentSize) return false;
    else    return true;
}

void minStackFree(MinStack* obj) {
    //printf("%s\n", __func__);

    if(obj->list) myLinkedListFree(obj->list);
    if(obj) free(obj);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    struct TreeNode* tree_ptr = NULL;
    MinStack *tree_stack = NULL;
    int *ret = NULL;

    *returnSize = 0;
    if(! root) return NULL;

    tree_stack = minStackCreate();
    ret = (int*)calloc(LEN, sizeof(int));
    tree_ptr = root;
    while(! minStackIsEmpty(tree_stack) || tree_ptr)
    {
        if(tree_ptr)
        {
            minStackPush(tree_stack, tree_ptr);
            tree_ptr = tree_ptr->left;
        }
        else
        {
            tree_ptr = minStackPop(tree_stack);
            ret[(*returnSize)++] = tree_ptr->val;
            tree_ptr = tree_ptr->right;
        }
    }

    if(tree_stack) minStackFree(tree_stack);

    return ret;

}
/ 68 - 0(<100%) - 5.9. on Nov 11, 2021 */
