/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    int* new = NULL;
    int i;
    int nine_counter;
    int delta;
    
    nine_counter = delta = 0;
    for(i = digitsSize - 1; i >=0; i--)
    {
        if(digits[i] == 9) nine_counter++;
        else break;
    }
    if(nine_counter == digitsSize)
    {
        delta = 1; 
        *returnSize = digitsSize + 1;
    }
    else
        *returnSize = digitsSize;

    new = (int*)calloc(*returnSize, sizeof(int));
    i = 0;
    if(nine_counter == digitsSize) new[i++] = 1;
    for(i; i <= (*returnSize - nine_counter - 1); i++)
        new[i] = digits[i - delta];
    //printf("[%d]=%d\n", *returnSize - nine_counter, *returnSize);
    if(delta != 1) new[*returnSize - nine_counter - 1] = digits[digitsSize - nine_counter - 1] + 1; 
    for(i = *returnSize - nine_counter; i < *returnSize; i++)
        new[i] = 0;
        
    return new;

}

/* 111 - 4(<52%) - 6MB, Aug 10th, 2021 */
