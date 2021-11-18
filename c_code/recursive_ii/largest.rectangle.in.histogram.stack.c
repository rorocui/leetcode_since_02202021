int largestRectangleArea(int* heights, int heightsSize)
{
    int idx      = 0,
        max_rect = 0,
        cur_rect = 0,
        pop_idx  = 0,
        i;

    int* stack = (int*)calloc(heightsSize, sizeof(int));

    for(i = 0; i <= heightsSize; i++)
    {
        //printf("[%d]idx=%d\n", i, idx);
        if(idx == 0 || (i != heightsSize && heights[stack[idx - 1]] <= heights[i]))
            stack[idx++] = i;
        else
        {
            pop_idx = stack[--idx];
            cur_rect = heights[pop_idx] * ((idx == 0) ? i : (i - stack[idx - 1] - 1));
            //printf("[%d],[%d], cur=%d\n", i, pop_idx, cur_rect);
            max_rect = max_rect > cur_rect ? max_rect : cur_rect;
            i--;
            //printf("[%d],[%d], cur=%d\n", i, pop_idx, cur_rect);
        }
    }
    if(stack) free(stack);

    return max_rect;

}
/* 96 - 84(<66%) - 13.4MB, on Nov 17th, 2021 */
