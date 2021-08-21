/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/* method 1 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int* ret = NULL;
    int* temp = NULL;
    int i;

    *returnSize = 2;

    ret = (int*)calloc(*returnSize, sizeof(int));
    ret[0] = 1; 
    ret[1] = numbersSize;
    while(ret[0] < ret[1])
    {
        if(numbers[ret[0] - 1] + numbers[ret[1] - 1] > target)
            (ret[1])--;
        else if(numbers[ret[0] - 1] + numbers[ret[1] - 1] < target)
            (ret[0])++;
        else 
            break;
    }

    return ret;
}
/*
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int *ret = NULL;
    bool find = false;
    
    *returnSize = 2;
    ret = (int*)calloc(*returnSize, sizeof(int));

    for(ret[0] = 1; ret[0] <= numbersSize; (ret[0])++)
    {
        for(ret[1] = ret[0] + 1; ret[1] <= numbersSize; (ret[1])++)
            if(numbers[ret[0] - 1] + numbers[ret[1] - 1] == target)
            {
                find = true;
                break;
            }
            else if(numbers[ret[0] - 1] + numbers[ret[1] - 1] > target)
                break;
       if(find) break; 
    }

    return ret;

}
*/
/* O(n^2) 19 - 384(<26%) - 7MB, on Aug 20th, 2021 */
/* >target, break; 19 - 228(<36%) - 6.6MB, on Aug 20th, 2021 */
/* method 1: 19 - 4(<96%), on Aug 20th, 2021 */
