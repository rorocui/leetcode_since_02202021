int max(int a, int b)
{
    return (a > b) ? a : b;
}
int min(int a, int b)
{
    return (a > b) ? b : a;
}
bool right_partition(int* nums1, int* nums2, int nums1Size, int nums2Size, int mid1, int mid2)
{
    //printf("m1-%d, m2-%d\n", mid1, mid2);
    if(mid1 == 0 || mid2 == 0)
        return true;
    if(mid1 < nums1Size && mid2 < nums2Size)
        return max(nums1[mid1 - 1], nums2[mid2 - 1]) <= min(nums1[mid1], nums2[mid2]); 
    else if(mid1 >= nums1Size && mid2 < nums2Size)
        return max(nums1[mid1 - 1], nums2[mid2 - 1]) <= nums2[mid2]; 
    else if(mid1 < nums1Size && mid2 >= nums2Size)
        return max(nums1[mid1 - 1], nums2[mid2 - 1]) <= nums1[mid1]; 
    else
        return true;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{

	int start1, end1, mid1;
	int start2, end2, mid2;
	double ret;
	int target_idx;
	
	/* All index pointer would point to 1-indexed array, instead of 0-indexed one */
	if(nums1Size == 0)
	{
	    if(nums2Size % 2 == 0)
	        return (double)(nums2[nums2Size / 2 - 1] + nums2[nums2Size / 2]) / 2;
	    else
	        return (double)nums2[nums2Size / 2];
	}
	if(nums2Size == 0)
	{
	    if(nums1Size % 2 == 0)
	        return (double)(nums1[nums1Size / 2 - 1] + nums1[nums1Size / 2]) / 2;
	    else
	        return (double)nums1[nums1Size / 2];
	}
	start1 = start2 = 1;
	end1 = nums1Size;
	end2 = nums2Size;
	ret = 0.0;
	target_idx = (nums1Size + nums2Size) / 2;
	mid1 = start1 + (end1 - start1) / 2;
	mid2 = start2 + (end2 - start2) / 2;
	
	while(start1 <= end1 && start2 <= end2)
	{
	    //printf("s1-%d, e1-%d, m1-%d, t-%d\n", start1, end1, mid1, target_idx);
	    //printf("s2-%d, e2-%d, m2-%d, t-%d\n\n", start2, end2, mid2, target_idx);
	    while(! right_partition(nums1, nums2, nums1Size, nums2Size, mid1, mid2))
	    {
	        /* We don't handle both mid1 and mid2 reach to the end of two arrays */ 
	        if(mid1 < nums1Size && mid2 < nums2Size)
	        {
	            if(nums1[mid1 - 1] > nums2[mid2 - 1])
	                mid2++;
	            else
	                mid1++;
	        }
	        else if(mid1 >= nums1Size && mid2 < nums2Size)
	            mid2++;
	        else
	            mid1++;
	    }
	    /* right partition */
	    if(mid1 + mid2 == target_idx + 1)
	    {
	        /* possible mid1 == 0 or mid2 == 0 */
	        if((nums1Size + nums2Size) % 2 == 0)
	        {
	            /* to handle the case, which top 2 biggest elements exist in same array */
	            if(mid1 == 0)
	                ret = (double)(nums2[mid2 - 1] + nums2[mid2 - 2]) / 2;
	            else if(mid2 == 0)
	                ret = (double)(nums1[mid1 - 1] + nums1[mid1 - 2]) / 2;
	            else if(nums1[mid1 - 1] > nums2[mid2 - 1])
	                ret = (double)(nums1[mid1 - 1] + max(nums2[mid2 - 1], ((mid1 - 1 > 0) ? nums1[mid1 - 2] : 0))) / 2;
	            else
	                ret = (double)(nums2[mid2 - 1] + max(nums1[mid1 - 1], ((mid2 - 1 > 0) ? nums2[mid2 - 2] : 0))) / 2;
	        }
	        else /* odd number */
	        {
	            //printf("m1-%d|m2-%d\n", mid1, mid2);
	            if(mid1 == 0)
	                ret = nums2[mid2 - 1];
	            else if(mid2 == 0)
	                ret = nums1[mid1 - 1];    
	            else
	                ret = nums1[mid1 - 1] > nums2[mid2 - 1] ? (double)nums1[mid1 - 1] : (double)nums2[mid2 - 1];
	        }
	        return ret;
	    }
	    else if((mid1 + mid2) < target_idx + 1)
	    {
	        if(mid2 < nums2Size && \
	            (mid1 == nums1Size || \
	            (nums1[mid1] >= nums2[mid2] && mid2 < nums2Size) || \ 
	            (nums1[mid1] <= nums2[mid2] && mid1 == nums1Size))) 
	        {
	            start2 = mid2 + 1;
	            mid2 = start2 + (end2 - start2) / 2;
	        }
	        else if(mid1 < nums1Size && \
	            ((mid2 == nums2Size && mid1 < nums1Size) || \
	            (nums1[mid1] <= nums2[mid2] && mid1 < nums1Size) || \ 
	            (nums1[mid1] >= nums2[mid2] && mid2 == nums2Size)))
	        {
	            start1 = mid1 + 1;
	            mid1 = start1 + (end1 - start1) / 2;
	        }
	        else
	            printf("Err: should not be here\n");
	    }
	    else /* (mid1 + mid2) > target_idx + 1 */
	        {
	            if(mid1 == 0)
	            {
	                if((nums1Size + nums2Size) % 2 == 0)
	                    ret = (double)(nums2[target_idx] + nums2[target_idx - 1]) / 2;
	                else
	                    ret = (double)nums2[target_idx];
	                return ret;
	            }
	            if(mid2 == 0)
	            {
	                if((nums1Size + nums2Size) % 2 == 0)
	                    ret = (double)(nums1[target_idx] + nums1[target_idx - 1]) / 2;
	                else
	                    ret = (double)nums1[target_idx];
	                return ret;
	            }
	            
	            if(nums1[mid1 - 1] > nums2[mid2 - 1])
	            {
	                end1 = mid1 - 1;
	                if(end1 == 0)
	                    /* set array 1 to all index to 0 for clean up */
	                    start1 = end1 = mid1 = 0;
	                else
	                    mid1 = start1 + (end1 - start1) / 2;
	            }
	            else
	            {
	                end2 = mid2 - 1;
	                if(end2 == 0)
	                    start2 = end2 = mid2 = 0;
	                else
	                    mid2 = start2 + (end2 - start2) / 2;
	            }
	        }
	    }
	    /* should not reach here */
	    return 0.0;
}
/* 2094 - 10ms(<92%) - 6.4MB, on Feb 17th, 2022 */
