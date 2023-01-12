void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* nums, int r, int l, int pivot){
    int idx = r;
    int i;
    int p_idx;

    for(i = r; i <= l; i++){
        if(nums[i] == pivot){
            p_idx = i;
            break;
        }
    }

    swap(&nums[p_idx], &nums[l]);
    for(i = r; i < l; i++){
        if(nums[i] > nums[l]){
            swap(&nums[idx], &nums[i]);
            idx++;
        }
    }
    swap(&nums[idx], &nums[l]);

    return idx;
}

int findKthLargest(int* nums, int numsSize, int k){
    int ret;
    int random_i;

    random_i = rand() % numsSize;

    ret = partition(nums, 0, numsSize - 1, nums[random_i]);

    if(ret == (numsSize - k))
        return ret;
    else if(ret > (numsSize - k)){
        return findKthLargest(nums, ret + 1, numsSize - k);
    }
    else {
        return findKthLargest(nums + ret, numsSize - ret, k);
    }

}

