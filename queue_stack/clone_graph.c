/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */
typedef struct MyLinkedList{
    struct Node*  val;
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

void minStackPush(MinStack* obj, struct Node* val) {
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

struct Node* minStackPop(MinStack* obj) {
    //printf("%s-obj:0x%lx\n", __func__, obj);
    MyLinkedList* new = NULL;
    struct Node* ret = 0;

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

struct Node* minStackTop(MinStack* obj) {
    //printf("%s-%d\n", __func__, obj->current->val);

    if(obj->current)
        return obj->current->val;
    else
    {
        printf("Empty Stack\n");
        return NULL;
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

struct Node* newNode()
{
    struct Node *new = NULL;
    new = (struct Node*)malloc(sizeof(struct Node));
    new->val = -1;
    new->numNeighbors = 0;
    new->neighbors = NULL;

    return new;
}

struct Node *cloneGraph(struct Node *s) {
    struct Node** visit = NULL;
    struct Node *new = NULL;
    struct Node *node_ptr = NULL;
    MinStack *node_stack = NULL;
    int i;

    if(!s) return NULL;
    visit = (struct Node**)malloc(101 * sizeof(struct Node*));
    for(i = 0; i < 101; i++)
        visit[i] = NULL;

    node_stack = minStackCreate();
    visit[s->val] = new = newNode();
    minStackPush(node_stack, s);

    while(!minStackIsEmpty(node_stack))
    {
        node_ptr = minStackPop(node_stack);
        //printf("handle node %d, its address 0x%x\n", node_ptr->val, node_ptr);
        visit[node_ptr->val]->val = node_ptr->val;
        visit[node_ptr->val]->numNeighbors = node_ptr->numNeighbors;
        visit[node_ptr->val]->neighbors = (struct Node**)malloc(node_ptr->numNeighbors * sizeof(struct Node*));
        //printf("node_ptr=0x%x, visit[%d]=0x%x\n", node_ptr, node_ptr->val, visit[node_ptr->val]);
	    for(i = 0; i < node_ptr->numNeighbors; i++)
	    {
            if(visit[node_ptr->neighbors[i]->val] == NULL)
            {
                //printf("%d\n", node_ptr->neighbors[i]->val);
	            visit[node_ptr->neighbors[i]->val] = newNode();
                //printf("node_ptr=0x%x, node_ptr->neighbors[%d]=0x%x\n", node_ptr, i, node_ptr->neighbors[i]);
	            minStackPush(node_stack, node_ptr->neighbors[i]);
            }
	        visit[node_ptr->val]->neighbors[i] = visit[node_ptr->neighbors[i]->val];
            //printf("visit[%d]=0x%x\n", node_ptr->neighbors[i]->val, visit[node_ptr->neighbors[i]->val]);
	    }
        //printf("cloned node %d, its address 0x%x\n", visit[node_ptr->val]->val, visit[node_ptr->val]);
        
    } /* end of while */

    if(visit) free(visit);
    if(node_stack) minStackFree(node_stack);
        
    return new;
}
/* 22 test cases in 4ms, in 6.6MB, on May 11th, 2021 */
