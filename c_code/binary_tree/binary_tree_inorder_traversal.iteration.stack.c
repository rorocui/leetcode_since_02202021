typedef struct MyLinkedList{
    struct TreeNode*  val;
    bool visited;
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
    new->visited = false;
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

struct TreeNode* minStackTop(MinStack* obj) {
    //printf("%s-%d\n", __func__, obj->current->val);

    if(obj->current)
        return obj->current->val;
    else
    {
        printf("Empty Stack\n");
        return NULL;
    }
}

bool isTopVisited(MinStack* obj){
    return obj->current->visited;
}

void minStackTopVisited(MinStack* obj){
    if(obj->current)
        obj->current->visited = true;
    else
    {
        printf("Empty Stack\n");
    }

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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    MinStack *tree_stack = NULL;
    int *ret = NULL, *new = NULL;
    int length = 0;
    struct TreeNode* tree_ptr = NULL;

    if(!root)
    {   
        *returnSize = 0;
        return ret;
    }
    countTreeNode(root, &length);
    //printf("tree length = %d\n", length);
    ret = new = (int*)calloc(length, sizeof(int));
    //printf("init ret=0x%lx\n", ret);

    tree_stack = minStackCreate();
    minStackPush(tree_stack, root);
    while(!minStackIsEmpty(tree_stack))
    {
        if(isTopVisited(tree_stack))
        {
            tree_ptr = minStackPop(tree_stack);
            *new = tree_ptr->val;
            //printf("[%d] ret=0x%lx\n", *new, new);
            new++;
        }
        else
        {
            tree_ptr = minStackPop(tree_stack);
            if(tree_ptr->right) minStackPush(tree_stack, tree_ptr->right);
            minStackPush(tree_stack, tree_ptr);
            minStackTopVisited(tree_stack);
            if(tree_ptr->left) minStackPush(tree_stack, tree_ptr->left);
        }

    }
    
    *returnSize = length;
    //printf("return ret=0x%lx\n", ret);
    return ret;

}
/* 68 test cases in 0ms, in 5.9MB on May 13th, 2021*/
/* 68 - 0(<100%) 6.3MB, on Nov 9th, 2021 */
