int largestRectangleArea(int* heights, int heightsSize)
{
    int p_left  = 0,
        p_right = 0,
        max_rectangle = 0,
        min_height,
        current_rectangle;


    if(heightsSize == 0) return 0;
    if(heightsSize == 1) return heights[0];
    for(p_right = 0; p_right < heightsSize; p_right++)
    {
        if(p_right + 1 < heightsSize && heights[p_right] <= heights[p_right + 1])
            continue;
        min_height = heights[p_right];
        for(p_left = p_right; p_left >=0; p_left--)
        {
            max_rectangle = max_rectangle > heights[p_left] ? max_rectangle : heights[p_left];
            min_height = min_height > heights[p_left] ? heights[p_left] : min_height;
            current_rectangle = min_height * (p_right - p_left + 1);
            max_rectangle = max_rectangle > current_rectangle ? max_rectangle : current_rectangle;
        }
    }

    return max_rectangle;

}
/* 92/96 Time limit Exceeded */
