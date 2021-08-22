
int removeElement(int* nums, int numsSize, int val)
{
    int i,j;
    
    j = 0;
    for(i = 0; i < numsSize; i++)
    {
        if(nums[i] != val)
        {
            nums[j++] = nums[i];
        }
    }
    return j;
}
/* 113 - 3ms(<63%) - 6.2MB, on Aug 21, 2021 */
/*
int removeElement(int* nums, int numsSize, int val){
    int length = numsSize;
    
    //printf("%d,%d\n", numsSize, val);
    for(int i = 0; i < length && length > 0; i++)
    {
        if(nums[i] == val)
        {
            while(nums[length - 1] == val && (length -1) != i) length--;
            
            nums[i] = nums[length - 1];
            length--;

        }        
    }
    return length;
  
}
*/
/*113 cases in 4ms On Feb 25th, 2021*/
