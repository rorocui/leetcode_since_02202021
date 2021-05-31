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

int convert_4chars_int(char *source)
{
    return (int)(*source - 0x30) * 1000 \
        + (int)(*(source + 1) - 0x30) * 100 \
        + (int)(*(source + 2) - 0x30) * 10 \
        + (int)(*(source + 3) - 0x30);
}

/* input digit (3/2/1/0) presents thousands/hundreds/tens/onces, 
 * signed char updown means 1=move up by one, -1=move down by one */
int single_digit_rotate(int digit, int input, signed char updown)
{
    //if(input == 1202) printf("%s:digit=%d, input=%d, updown=%d\n", __func__, digit, input, updown);
    int target_digit = 0;
    int origin_value = 0;
    int ret = -1;

    origin_value = target_digit = input % (int)pow((float)10, digit + 1);
    //if(input == 1202) printf("target_digit=%d\n",target_digit);
    if(digit > 0) origin_value = target_digit /= (int)pow((float)10, digit);
    //if(input == 1202) printf("target_digit=%d\n",target_digit);
    target_digit = ((target_digit + updown) >= 0) ? (target_digit + updown) % 10 : 9;
    //if(input == 1202) printf("target_digit=%d\n",target_digit);


    ret = input - (origin_value - target_digit) * (int)pow((float)10, digit);
    //if(input == 1202) printf(" | %04d->%04d \n", input, ret);

    return ret;
}

#define UP 1
#define DOWN -1


int openLock(char ** deadends, int deadendsSize, char * target)
{
   unsigned char* visit_ptr = NULL;
   int i = 0;
   int index = -1;
   int targetNum = -1;
   int step = 0;
   MyCQue* quePtr = NULL;
   int nodeInStep = 0; 
    
   /* status of all 10000 nodes 
    * not visited as "0",
    * visited     as "1",
    * deadends    as "2",
    * target      as "3" */
   visit_ptr = (unsigned char*)calloc(10000, sizeof(unsigned char));
   
   for(i = 0; i < deadendsSize; i++)
   {
        index = convert_4chars_int(deadends[i]);
        //printf("index=%d\n", index);
        *(visit_ptr + index) = 2;
   }
   if(*(visit_ptr) == 2) 
   {
       free(visit_ptr);
       return -1;
   } 

   /* mark 0000 node as visited */ 
   *visit_ptr = 1;
   /* mark target as number 3 */
   index = convert_4chars_int(target);
   *(visit_ptr + index) = 3;
   //printf("target=%d, flag=%d", index, *(visit_ptr + index)); 
    
   /* after run a few test case, I finalize this number, 1350 for queue size */ 
   quePtr = myCQueCreate(1350);
    
   /* initialize the que with 0000 */
   myCQueEnQue(quePtr, 0);
   //printf("\nstep=%d\n", step);
   while(!myCQueIsEmpty(quePtr))
   {
       nodeInStep = quePtr->currentSize;        
       //printf("QueSize=%d,Step=%d\n", nodeInStep, step);
       while(nodeInStep > 0)
       {
           index = myCQueDeQue(quePtr);
           nodeInStep--;
           /*check if index is target number */
           if(*(visit_ptr + index) == 3)
           {
               free(visit_ptr);
               myCQueFree(quePtr);
               return step;
           }
           /* check 4 digits differ by 1/-1 */
           for(i = 0; i < 4; i++)
           {
              /* digit + 1 */ 
              targetNum = single_digit_rotate(i, index, UP);
              if(*(visit_ptr + targetNum) == 3)
              {
                  free(visit_ptr);
                  myCQueFree(quePtr);
                  return ++step;
              }
              if(*(visit_ptr + targetNum) == 0)
              {
                  if(!myCQueEnQue(quePtr, targetNum)) break;
                  *(visit_ptr + targetNum) = 1;
              }
               
              /* digit - 1 */ 
              targetNum = single_digit_rotate(i, index, DOWN);
              if(*(visit_ptr + targetNum) == 3)
              {
                  free(visit_ptr);
                  myCQueFree(quePtr);
                  return ++step;
              }
              if(*(visit_ptr + targetNum) == 0)
              {
                  if(!myCQueEnQue(quePtr, targetNum)) break;
                  *(visit_ptr + targetNum) = 1;
              }
           } /* end for */
       }/* end of while nodeInStep */
       step++;
   } /* end of while emptyQueue */
   free(visit_ptr);
   myCQueFree(quePtr);

   return -1; 
}

/* 47 cases in 56ms in 7.4 MB, on April 22nd, 2021 */

