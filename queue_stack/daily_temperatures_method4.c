#define TEMP_LEN 101
#define INDEX_MAX 30001

int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
    int* new = NULL;
    int* temp = NULL;
    int i, j;
    bool find_result = false;
    int compare = INDEX_MAX;

    new = (int*)calloc(TSize, sizeof(int));
    temp = (int*)malloc(sizeof(int) * TEMP_LEN);
    for(i = 0; i < TEMP_LEN; i++) temp[i] = INDEX_MAX;
    *returnSize = TSize;

    for(i = TSize - 1; i >= 0; i--)
    {
        compare = INDEX_MAX;
        for(j = T[i] + 1; j <= 100; j++)
        {
            compare = temp[j] < compare ? temp[j]:compare;
            //if(comprintf("[%d]-compare=%d\n", i, compare);
        }
        if(compare < INDEX_MAX)
            new[i] = compare - i;
        temp[T[i]] = i;
        /*
        if(T[i] == 98)
        {
            printf("[%d]-compare=%d\n", i, compare);
            for(int k = 98; k < 101; k++)
                printf("temp[%d]=%d |", k, temp[k]);
            printf("\n");
        }
        */
    }

    return new;

}

/* 38 test cases in 200ms(<19%) in 26MB(<60%) on May 4th, 2021 */
