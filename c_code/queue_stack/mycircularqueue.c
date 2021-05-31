


typedef struct {
    int* queue;
    int  maxSize;
    int  front;
    int  rear;
    int  currentSize;
} MyCQue;


MyCQue* myCQueCreate(int k) {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->queue = (int*)malloc(sizeof(int) * k);
    obj->maxSize = k;
    obj->front = obj->rear = -1;
    obj->currentSize = 0;
    
    //printf("%s:%lx-%d\n", __func__, &obj, k);
    return obj;
}

bool myCQueEnQueue(MyCQue* obj, int value) {
    //printf("%s:%lx-%d\n", __func__, &obj, value);
    if(obj->currentSize == obj->maxSize) return false;
    /* if empty, need front++ */
    if(obj->currentSize == 0) obj->front++;

    if((++obj->rear) > (obj->maxSize - 1)) obj->rear = 0;
    //printf("%d-%d\n", obj->front, obj->rear);
    *(obj->queue + obj->rear) = value;
    obj->currentSize++;
    
    return true;
}

bool myCQueDeQueue(MyCQue* obj) {
    //printf("%s:%lx-%d\n", __func__, &obj, obj->currentSize);
    if(!obj->currentSize) return false;

    if((++obj->front) > (obj->maxSize - 1)) obj->front = 0;
    obj->currentSize--;
    
    if(obj->currentSize == 0) obj->front = obj->rear = 0;
    //printf("%d-%d\n", obj->front, obj->rear);
    
    return true; 
}

int myCQueFront(MyCQue* obj) {
    //printf("%s:%lx-%d\n", __func__, &obj, obj->currentSize);
    if(!obj->currentSize) return -1;
    
    //printf("%s:%lx-%d\n", __func__, &obj, *(obj->queue + obj->front));
    
    return *(obj->queue + obj->front);
}

int myCQueRear(MyCQue* obj) {
    if(!obj->currentSize) return -1;
    
    //printf("%s:%lx-%d\n", __func__, &obj, *(obj->queue + obj->rear));
    
    return *(obj->queue + obj->rear);
  
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
    if(obj->queue) free(obj->queue);
    if(obj) free(obj);
}

/**
 * Your MyCQue struct will be instantiated and called as such:
 * MyCQue* obj = myCQueCreate(k);
 * bool param_1 = myCQueEnQueue(obj, value);
 
 * bool param_2 = myCQueDeQueue(obj);
 
 * int param_3 = myCQueFront(obj);
 
 * int param_4 = myCQueRear(obj);
 
 * bool param_5 = myCQueIsEmpty(obj);
 
 * bool param_6 = myCQueIsFull(obj);
 
 * myCQueFree(obj);
*/

/* 57 cases in 28ms with 12.9MB, beats 80% on April 16th, 2021 */
