
typedef struct {
    int* que;
    int  maxSize;
    int  front;
    int  rear;
    int  currentSize;
} MyCQue;



MyCQue* circular_queue_create(int k) {
    MyCQue* obj = (MyCQue*)malloc(sizeof(MyCQue));
    obj->que = (int*)malloc(sizeof(int) * k);
    obj->maxSize = k;
    obj->front = obj->rear = -1;
    obj->currentSize = 0;
    
    //printf("%s:%lx-%d\n", __func__, &obj, k);
    return obj;
}

bool circular_queue_is_full(MyCQue* obj) {
    if(obj->currentSize == obj->maxSize)
        return true;
    else
        return false;
}

bool circular_queue_is_empty(MyCQue* obj) {
    //printf("%s:%d\n", __func__, obj->currentSize);
    //printf("%d\n", obj->currentSize); 
    if(obj->currentSize)
        return false;
    else
        return true;
}

bool circular_queue_enque(MyCQue* obj, int value) {
    //if(value == 202) printf("%s:%lx-%d\n", __func__, &obj, value);
    if(circular_queue_is_full(obj))
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

int circular_queue_deque(MyCQue* obj) {
    //printf("%s:%lx-%d\n", __func__, obj, obj->currentSize);
    int ret = -1;

    if(circular_queue_is_empty(obj)) return -1;

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

void circular_queue_free(MyCQue* obj) {
    if(obj->que) free(obj->que);
    if(obj) free(obj);
}

#define SQUARE_MAX 100

/* search in square array to get max number, which less than target */
int search_square_index(int* squareArray, int target, unsigned int range)
{
    if(*(squareArray + range/2) <= target)
    {
        if(*(squareArray + range/2 + 1) > target)
            return range/2;
        else
            return search_square_index((squareArray + range/2 + 1), target, (range/2 + 1));
    }
    else
    {
        if(*(squareArray + range/2 - 1) <= target)
            return (range/2 - 1);
        else
            return search_square_index(squareArray, target, (range/2 + 1));
    }

}


int numSquares(int n)
{
    int* squareArray = NULL;
    int stepCount = 0;
    int squareIndex = SQUARE_MAX;
    int i = 0;
    int nodesInOneLevel = 0;
    int queueVal = -1;

    MyCQue* quePtr = NULL;

    squareArray = (int*)malloc(sizeof(int) * 100);
    for(squareIndex = 0; squareIndex < SQUARE_MAX; squareIndex++)
        squareArray[squareIndex] = (int)pow((float)(squareIndex + 1), 2);

    quePtr = circular_queue_create(1000);
    circular_queue_enque(quePtr, n);
    while(!circular_queue_is_empty(quePtr))
    {
        nodesInOneLevel = quePtr->currentSize;
        while(nodesInOneLevel > 0)
        {
            queueVal = circular_queue_deque(quePtr);
            squareIndex = search_square_index(squareArray, queueVal, squareIndex);
            for(i = 0; i < squareIndex; i++)
            {
                if((queueVal - squareArray[i]) > 0)
                    circular_queue_enque(quePtr, queueVal - squareArray[i]);
                else
                {
                    circular_queue_free(quePtr);
                    free(squareArray);
                    return stepCount + 1;
                }
            }    
            nodesInOneLevel--;
        }/*while nodesInOneLevel */
		stepCount++;
    }/*while queue empty */

    return stepCount;
}
