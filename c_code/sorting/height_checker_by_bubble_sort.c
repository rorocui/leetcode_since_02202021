
void swap(int* a, int* b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int* input, int size){
    bool did_swap = false;

    do
    {
        did_swap = false;
        for(int i = 0; i < size - 1; i++)
        {
            if(input[i] > input[i + 1])
            {
                did_swap = true;
                swap(&input[i], &input[i + 1]);
            }
        }
    }
    while(did_swap);
}



int heightChecker(int* heights, int heightsSize){

    int* expected = (int*)malloc(heightsSize * sizeof(int));
    int ret = 0;

    memcpy(expected, heights, heightsSize * sizeof(int));
    bubble_sort(expected, heightsSize);
    for(int i = 0; i < heightsSize; i++){
        //printf("expected[%d] = %d\n", i, expected[i]);
        if(heights[i] != expected[i])
            ret++;
    }
    
    return ret;
}

/* beat 44% on Sep 14th, 2022 */
