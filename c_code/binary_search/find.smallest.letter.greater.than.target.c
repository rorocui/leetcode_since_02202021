
char nextGreatestLetter(char* letters, int lettersSize, char target)
{
    int start, end, mid;

    start = 0;
    end = lettersSize - 1;
    mid = start + (end - start) / 2;

    while(start < end)
    {
        //printf("s-%d,end-%d,m-%d\n", start, end, mid);
        /*
        if(letters[mid] == target)
            return letters[mid + 1];
        /* mid == end;
         * end = start + end/2 - start/2;
         * end/2 = start/2; */
        if(letters[mid] <= target)
        {
            if(letters[mid + 1] > target)
                return letters[mid + 1];
            else if(letters[mid + 1] < target)
                /*
                if(mid + 1 == end)
                    return letters[0];
                else
                    start = mid + 1;
                   */
                start = mid + 1;
            else /* letters[mid + 1] == target */
            {
                if(mid + 1 < end)
                    start = mid;
                else
                    return letters[0];
            }
        }
        else /* letters[mid] > target */ 
            /* mid is possible to be 0 at this point */
        {
            /* mid == start
             * start = start + end/2 - start/2;
             * no possibility mid = start */
            if(mid > 0 && letters[mid - 1] > target)
                /*
                if(mid - 1 == 0)
                    return letters[0];
                else
                    end = mid - 1;
                */    
                end = mid - 1;
            else /* letters[mid - 1] <= target */
                return letters[mid];
        }
        mid = start + (end - start) / 2;
    }
    return letters[0];

}
/* 165 - 0(<100%) - 6.3MB, on Jan 30th, 2022 */
