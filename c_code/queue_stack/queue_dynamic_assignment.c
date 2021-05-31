typedef struct {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() {
    //printf("%s\n", __FUNCTION__);
    MyLinkedList* new = NULL;
    new = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    new->val = -1;
    new->next = NULL;
    return new;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
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
        ptr->val = val;
        ptr->next = end;
    }
    else
    {
        obj->val = val;

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
            obj->val = ptr->val;
        }
    }

}

/** Get the value of the index-th node in the linked list.
 * If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
    MyLinkedList* ptr = NULL;
    int i;

    //printf("%s:0x%x\n", __func__, obj);
    if(obj)
        ptr = obj;
    else
        return -1;
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
        return ptr->val;
    }
    else
    {
        return -1;
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

bool myCQueEnQue(MyCQue* obj, int value) {
    //printf("EnQue-%d\n", value);
    myLinkedListAddAtTail(obj->que, value);
    obj->currentSize++;
    return true;
}

int myCQueDeQue(MyCQue* obj) {
    int ret = 0;

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
        return -1;
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

