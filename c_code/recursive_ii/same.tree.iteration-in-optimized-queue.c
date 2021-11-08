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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool check(struct TreeNode* p, struct TreeNode* q)
{
    //printf("%#x vs %#x\n", p, q);
    //printf("%d vs %d\n", p->val, q->val);
    if( ! p && ! q )
        return true;
    if(( p && ! q ) || (! p && q ))
        return false;
    if( p->val != q->val )
        return false;
    return true;
}

bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    MyCQue *que = NULL;

    que = myCQueCreate();

    myCQueEnQue(que, p);
    myCQueEnQue(que, q);
    
    while(!myCQueIsEmpty(que))
    {
        p = myCQueDeQue(que);
        q = myCQueDeQue(que);
        if(!check(p, q))
            return false;
        if(! p && !q)
            continue;
        myCQueEnQue(que, p->left);
        myCQueEnQue(que, q->left);
        myCQueEnQue(que, p->right);
        myCQueEnQue(que, q->right);
    }

    myCQueFree(que);

    return true;
}
/* 60 - 0 (<100%) - 5.8MB, on Nov 4th, 2021 */

