
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize)
{
    int temp = 0, idx = 0;
    
    *returnSize = numsSize;
    int* newNums = malloc(sizeof(int) * *returnSize);
   
    for(int i = 0; i < numsSize; i++)
    {
        newNums[i] = nums[i] * nums[i];
        idx = i;
        for(int j = i - 1; j >= 0; j-- )
        {
            if (newNums[idx] < newNums[j])
            {
                temp = newNums[idx];
                newNums[idx] = newNums[j];
                newNums[j] = temp;
                idx = j;
            }
            else
                break;
        }
    }
    return newNums;            
}

