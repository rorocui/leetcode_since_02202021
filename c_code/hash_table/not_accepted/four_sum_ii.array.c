int fourSumCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size)
{
    int i, j;
    int ret = 0;
    int size = 0;
    int* sum = NULL;

    size = nums1Size * nums2Size * nums3Size * nums4Size;
    sum = calloc(size, sizeof(int));
    
    if(memcmp(nums1, sum, sizeof(int) * nums1Size) == 0 && \
        !memcpy(nums2, sum, sizeof(int) * nums2Size) == 0 && \
        !memcpy(nums3, sum, sizeof(int) * nums3Size) == 0 && \
        !memcpy(nums4, sum, sizeof(int) * nums4Size) == 0)
    {
        printf("all zero, return \n");
        return nums1Size * nums2Size * nums3Size * nums4Size;
    }
    
    for(i = 0, j = 0; i < size; i++, j++)
    {
        j = j % nums1Size;
        sum[i] += nums1[j];
        //printf("%d,", sum[i]);
    }
    //printf("\n");
    for(i = 0, j = 0; i < size; i++, j++)
    {
        
        //j = j / nums1Size % nums2Size;
        sum[i] += nums2[j / nums1Size % nums2Size];
        //printf("%d\n", nums2[j / nums1Size % nums2Size]);
    }
    //printf("\n");
    for(i = 0, j = 0; i < size; i++, j++)
    {
        //j = j / nums1Size / nums2Size;
        sum[i] += nums3[j / nums1Size / nums2Size % nums3Size];
    }
    for(i = 0, j = 0; i < size; i++, j++)
    {
        //j = j / nums1Size / nums2Size / nums3Size;
        sum[i] += nums4[j / nums1Size / nums2Size / nums3Size % nums4Size];
    }
    for(i = 0, j = 0; i < size; i++, j++)
    {
        //printf("%d,", sum[i]);
        if(sum[i] == 0) ret++;
    }
    //printf("\n");
            
    free(sum);
    return ret;
}

/* 19/132-Time Limit Exceeded(n/a) , on July 18th, 2021 */
/* 19 test case 100x100x100x100, all arrays contains all Zero */

/* 20/132 - Time Limit Exceeded(n/a), on July 18th, 2021 */
/* 20 test case is 100xnxnxn */
