int factorial(int n)
{
	int ret = 1;
	int i;

	for(i = 1; i <= n; i++)
		ret *= i;

	return ret;
}

void perm(int* nums, int numsSize, int** ret, int* idx, int* tmp_buff, int tmp_size)
{
	int i, j;

	if(tmp_size == numsSize)
	{
        /*
        printf("temp_buff ");
        for(int m = 0; m < numsSize; m++)
            printf("%d ", tmp_buff[m]);
        printf("\n");
        printf("ret[%d] ", *idx);
        for(int m = 0; m < numsSize; m++)
            printf("%d ", ret[*idx][m]);
        printf("\n");
        */
		memcpy(ret[(*idx)++], tmp_buff, numsSize * sizeof(int));
        /*
        printf(".ret[%d] ", *idx - 1);
        for(int m = 0; m < numsSize; m++)
            printf("%d ", ret[*idx - 1][m]);
        printf("\n");
        */
	}
	else
	{
		for(i = 0; i < numsSize; i++)
		{
			for(j = 0; j < tmp_size; j++)
				if(tmp_buff[j] == nums[i])
					break;
			if(j < tmp_size)
				continue;
			tmp_buff[tmp_size] = nums[i];
			perm(nums, numsSize, ret, idx, tmp_buff, tmp_size + 1);
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
	int i;
	int** ret = NULL;
	int* tmp_buff = NULL;
	int  idx = 0;


	*returnSize = factorial(numsSize);
	(*returnColumnSizes) = (int*)malloc(*returnSize * sizeof(int));
	ret = (int**)malloc(*returnSize * sizeof(int*));

	for(i = 0; i < *returnSize; i++)
	{
		(*returnColumnSizes)[i] = numsSize;
		ret[i] = (int*)calloc(numsSize, sizeof(int));
	}

	tmp_buff = (int*)calloc(numsSize, sizeof(int));

	perm(nums, numsSize, ret, &idx, tmp_buff, 0);

	if(tmp_buff) free(tmp_buff);

	return ret;

}

/* 26 - 8 (<96%) - 7.3, on Dec 13th, 2021 */
