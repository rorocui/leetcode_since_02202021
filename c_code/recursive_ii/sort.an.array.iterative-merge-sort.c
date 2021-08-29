
void merge_arrays(int* a, int* b, int len_a, int len_b)
{
    //printf("merge_arrays: %#x,%#x,%d,%d\n", a, b, len_a, len_b);
    int i, j;
    int* new = NULL;
    int idx;
    
    new = (int*)calloc(len_a + len_b, sizeof(int));
    idx = i = j = 0;
    while(i < len_a && j < len_b)
    {
        if(a[i] <= b[j])
        {
            new[idx++] = a[i++];
        }
        else
        {
            new[idx++] = b[j++];
        }
    }
    if(i == len_a)
        for(j; j < len_b; j++)
            new[idx++] = b[j];
    if(j == len_b)
        for(i; i < len_a; i++)
            new[idx++] = a[i];
    for(i = 0; i < len_a; i++)
    {
        a[i] = new[i];
        //printf("%d.", a[i]);
    }
    for(i = 0; i < len_b; i++)
    {
        b[i] = new[i + len_a];
        //printf("%d.", b[i]);
    }
    //printf("\n");

    if(new) free(new);
}
int power_two(int a)
{
    return (int)pow((float)2, a);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize)
{
    int* ret = NULL;
    int i, j;
    int len_b;
    int len_a;
    //printf("sortArray:%#x,%d\n", nums, numsSize);

    len_a = len_b = 0;
    ret = (int*)calloc(numsSize, sizeof(int));
    for(i = 0; i < log2(numsSize); i++)
    {
        len_a = power_two(i);
        //printf("i=[%d],len_a=%d\n", i, len_a);
        for(j = 0; j < numsSize; j += len_a * 2)
        {
            len_b = (j + len_a * 2) > numsSize ? (numsSize - j - len_a) : len_a;
            
            if(len_b > 0) merge_arrays(&nums[j], &nums[j + len_a], len_a, len_b);
        }
    }

    *returnSize = numsSize;
    return nums;
}
/* 13 - 243 (<23%) - 44.1MB, on Aug 28th, 2021 */
