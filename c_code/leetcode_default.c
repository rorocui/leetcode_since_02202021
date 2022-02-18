## Variable
INT_MAX


int compare(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

# functions
    qsort( nums1, nums1Size, sizeof(int), compare);

