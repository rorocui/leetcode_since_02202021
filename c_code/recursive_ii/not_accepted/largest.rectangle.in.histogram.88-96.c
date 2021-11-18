
int min_height_than_max_rectangle(int p_left, int heightsSize, int max_rectangle)
{
    return max_rectangle / (heightsSize - p_left - 1);
}

int cal_current_rectangle(int p_left, int p_right, int min_height)
{
    //printf("l-%d, r-%d, min_height-%d, ret-%d\n", p_left, p_right, min_height, min_height*(p_right-p_left+1));
    return min_height * (p_right - p_left + 1);
}

int largestRectangleArea(int* heights, int heightsSize)
{
    int p_left  = 0,
        p_right = 1,
        p_min   = 0,
        max_rectangle,
        current_rectangle;


    if(heightsSize == 0) return 0;
    if(heightsSize == 1) return heights[0];
    max_rectangle = current_rectangle = heights[0];
    while(p_left <= heightsSize - 2)
    {
        //printf("start. left-%d, right-%d, min-%d, max-%d\n", p_left, p_right, p_min, max_rectangle);
        if(heights[p_right] <= heights[p_min])
        {
            /* new min_height*/
            current_rectangle = cal_current_rectangle(p_left, p_right, heights[p_right]);
            max_rectangle = max_rectangle > current_rectangle ? max_rectangle : current_rectangle;
            p_min = p_right;
        }
        else if(heights[p_right] > heights[p_min])
        {
            current_rectangle = cal_current_rectangle(p_left, p_right, heights[p_min]);
            max_rectangle = max_rectangle > current_rectangle ? max_rectangle : current_rectangle;
            /* Check rectangle with single bar. */
            max_rectangle = max_rectangle > heights[p_right] ? max_rectangle : heights[p_right];
        }
        else if(heights[p_right] < min_height_than_max_rectangle(p_left, heightsSize, max_rectangle))
        {
            /*new height at p_right is too low, need move p_left*/
            p_left = p_min + 1;
            p_right = p_left + 1;
            p_min++;
            continue;
        }
        p_right++;
        if(p_right >= heightsSize)
        {
            p_left++;
            p_right = p_left + 1;
            p_min = p_left;
        }
        //printf("end. left-%d, right-%d, min-%d, max-%d\n", p_left, p_right, p_min, max_rectangle);
    }

    return max_rectangle;

}

/* 88/96, Time limit Exceeded */
