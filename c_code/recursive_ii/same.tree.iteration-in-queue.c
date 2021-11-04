typedef struct {
    struct TreeNode* node;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->node = NULL;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, struct TreeNode* node) {
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

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    MyLinkedList* temp = NULL;
    int i;

    //printf("%s:%d\n", __func__, val);
    if(obj)
    {
        if(index > 0)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                if(ptr->next)
                {
                    ptr = ptr->next;
                    i++;
                }
                else
                    break;
            }
            if(i == index - 1)
            {
                if(ptr->next)
                {
                    temp = ptr->next;
                    ptr->next = temp->next;
                }
                free(temp);
            }
        }
        else
        {
            ptr = obj->next;
            obj->next = ptr->next;
            obj->node = ptr->node;
        }
    }

}

/** Get the value of the index-th node in the linked list.
 * If the index is invalid, return -1. */
struct TreeNode* myLinkedListGet(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    int i;

    //printf("%s:0x%x\n", __func__, obj);
    if(obj)
        ptr = obj;
    else
        return NULL;
    for(i = 0; i < index;)
    {
        if(ptr->next)
        {
            ptr = ptr->next;
            i++;
        }
        else
            break;
    }
    //printf("%s:0x%x\n", __func__, obj);
    if(i == index && ptr)
    {
        //printf("%s:%d\n", __func__, ptr->val);
        return ptr->node;
    }
    else
    {
        return NULL;
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

typedef struct {
    MyLinkedList* que;
    int  currentSize;
} MyCQue;


MyCQue* myCQueCreate() {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->que = myLinkedListCreate();
    obj->currentSize = 0;
    
    return obj;
}

bool myCQueEnQue(MyCQue* obj, struct TreeNode* node) {
    //printf("EnQue-%#x\n", node);
    myLinkedListAddAtTail(obj->que, node);
    obj->currentSize++;
    return true;
}

struct TreeNode* myCQueDeQue(MyCQue* obj) {
    struct TreeNode*  ret = NULL;

    if(obj->currentSize > 0)
    {
        obj->currentSize--;
        ret = myLinkedListGet(obj->que, 0);
        myLinkedListDeleteAtIndex(obj->que, 0);
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
/* 60 - 0 (<100%) - 6.1MB, on Nov 3rd, 2021 */
