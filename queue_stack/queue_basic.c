typedef struct {
    int* que;
    int  maxSize;
    int  front;
    int  rear;
    int  currentSize;
} MyCQue;


MyCQue* myCQueCreate(int k) {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->que = (int*)malloc(sizeof(int) * k);
    obj->maxSize = k;
    obj->front = obj->rear = -1;
    obj->currentSize = 0;
    
    //printf("%s:%lx-%d\n", __func__, &obj, k);
    return obj;
}

bool myCQueEnQue(MyCQue* obj, int value) {
    //if(value == 202) printf("%s:%lx-%d\n", __func__, &obj, value);
    if(obj->currentSize == obj->maxSize)
    {
        printf("no enough space in Queue for insert request, max=%d\n", obj->maxSize);
        return false;
    }
    /* if empty, need front++ */
    if(obj->currentSize == 0) obj->front++;

    if((++obj->rear) > (obj->maxSize - 1)) obj->rear = 0;
    //printf("%d-%d\n", obj->front, obj->rear);
    *(obj->que + obj->rear) = value;
    obj->currentSize++;
    
    //printf("EnQ:%d\n", obj->currentSize); 
    return true;
}

int myCQueDeQue(MyCQue* obj) {
    //printf("%s:%lx-%d\n", __func__, obj, obj->currentSize);
    int ret = 0;

    if(!obj->currentSize) return -1;

    //printf("b:ret=%d\n", ret);
    //printf("b:%d-%d\n", obj->front, obj->rear);
    ret = *(obj->que + obj->front);
    //printf("a:ret=%d\n", ret);
    if((++obj->front) > (obj->maxSize - 1)) obj->front = 0;
    obj->currentSize--;
    
    if(obj->currentSize == 0) obj->front = obj->rear = -1;
    //printf("a:%d-%d\n", obj->front, obj->rear);
    
    //if(ret == 202) printf("done:ret=%d\n", ret);
    //printf("DeQ:%d\n", obj->currentSize); 
    return ret; 
}

bool myCQueIsEmpty(MyCQue* obj) {
    //printf("%s:%d\n", __func__, obj->currentSize);
    //printf("%d\n", obj->currentSize); 
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
    if(obj->que) free(obj->que);
    if(obj) free(obj);
}
