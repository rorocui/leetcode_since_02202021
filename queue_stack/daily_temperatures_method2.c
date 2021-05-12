int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
    int* new = NULL;
    int i, j;

    new = (int*)calloc(1, sizeof(int));
    *returnSize = TSize;

    for(i = TSize - 1; i >=0; i--)
    {
        for(j = i - 1; j >=0; j--)
        {
            if(T[i] > T[j]) 
                new[j]++;
            else if(new[j] ! = 0 && T[i] < T[j])
                new[j]++;
            else
                /* do nothing */
                ;
        }
        if(i > 0 && T[i] > T[i - 1])
            T[i - 1] = 1;
    }

    return new;

}

failed "Time Limit Exceeded" at 31/38
