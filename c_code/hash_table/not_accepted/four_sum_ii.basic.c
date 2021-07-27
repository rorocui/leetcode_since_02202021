int fourSumCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size)
{
    int i,j,l,k;
    int ret = 0;
    int count = 0;

    printf("%d,%d,%d,%d\n", nums1Size, nums2Size, nums3Size, nums4Size);
    for(i = 0; i < nums1Size; i++)
        for(j = 0; j < nums2Size; j++)
            for(l = 0; l < nums3Size; l++)
                for(k = 0; k < nums4Size; k++)
                {
                    if(nums1[i] + nums2[j] + nums3[l] + nums4[k] == 0) ret++;
                }

    return ret;
}

/* 27/132-Time Limit Exceeded(n/a) , on July 18th, 2021 */
/* 27 test case 100x100x100x100 */

