void swap(int* a, int* b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void moveZeroes(int* nums, int numsSize)
{
    int left, right;

    /*
    left = 0;
    while(left < numsSize && nums[left] != 0)
        left--;
    if(left == numsSize) return;
    */
    while(right < numsSize)
    {
        while(right < numsSize && nums[right] != 0)
            right++;
        left = right;
        while(right < numsSize && nums[right] == 0)
            right++;
        if(right < numsSize && nums[left] == 0 && nums[right] != 0)
        {
            swap(&nums[left], &nums[right]);
            right = left + 1;
        }
    }
}
/* 21 - 26(<13%) - 7.6MB, on Aug 26th, 2021 */

/*
void moveZeroes(int* nums, int numsSize){
    int write_ptr, i;
    
    write_ptr = 0;
    for(i = 0; i < numsSize; i++)
    {
        if(nums[i] != 0)
            nums[write_ptr++] = nums[i];
    }
    for(i = write_ptr; i < numsSize; i++)
        nums[i] = 0;

}
21 - 17(<24%) - 7.8MB, on Aug 26th, 2021 */
