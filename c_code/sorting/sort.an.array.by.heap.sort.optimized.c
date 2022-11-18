
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp
}


/* Recursive maxify a tree function */
void maxifyTree(int* nums, int numsSize, int idx){
    int left = 2 * idx + 1;
    int right = left + 1;
    int largest = idx;

    if(left < numsSize && nums[left] > nums[largest])
        largest = left;
    if(right < numsSize && nums[right] > nums[largest])
        largest = right;
    if(largest != idx)
        swap(&nums[largest], &nums[idx]);
    maxifyTree(nums, numsSize, largest);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize){
    int i;

    *returnSize = numsSize;
    /* Maxify the tree */
    for(i = (numsSize / 2 - 1); i >= 0; i--){
        maxifyTree(nums, numsSize, i);
    }

    /* Sort array by heap sort */
    for(i = (numsSize - 1); i > 0; i--){
        maxifyTree(nums, numsSize, i);
        swap(&nums[i], &nums[0]);
    }


    return nums;

}
