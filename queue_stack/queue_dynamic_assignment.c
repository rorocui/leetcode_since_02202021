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

    //if(! EmptyList(obj))
    if(obj)
    {
        end = myLinkedListCreate();
        end->val = val;
        end->next = NULL;
        ptr = obj;
        //while(! EmptyList(ptr->next))
        while(ptr->next)
        {
            ptr = ptr->next;
        }
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

    //if(!EmptyList(obj))
    if(obj)
    {
        if(index > 0)
        {
            ptr = obj;
            for(i = 0; i < index - 1;)
            {
                //if(!EmptyList(ptr->next))
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
                //if(!EmptyList(ptr->next))
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

    //if(! EmptyList(obj))
    if(obj)
        ptr = obj;
    else
        return -1;
    for(i = 0; i < index;)
    {
        //if(! EmptyList(ptr->next))
        if(ptr->next)
        {
            ptr = ptr->next;
            i++;
        }
        else
            break;
    }
    //if(i == index && !EmptyList(ptr))
    if(i == index && ptr)
    {
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
        return ret;
    }
    else
    {
        printf(" Empty queue, can't Deque\n");
        return -1;
    }

}



bool myCQueIsEmpty(MyCQue* obj) {
    if(obj->currentSize)
        return false;
    else
        return true;
}

bool myCQueIsFull(MyCQue* obj) {
    if(obj->currentSize == obj->maxSize)
        return true;
    else
        return false;
}

void myCQueFree(MyCQue* obj) {
    if(obj->que) myLinkedListFree(obj->que);
    if(obj) free(obj);
}
