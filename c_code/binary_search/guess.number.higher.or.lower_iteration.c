/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

int guessNumber(int n)
{
    int start = 1;
    int end = n;
    int mid = start + (end - start) / 2;
    int ret;

    ret = guess(mid);
    while(ret != 0)
    {
        if(ret > 0)
            start = mid + 1;
        else
            end = mid - 1;
        mid = start + (end - start) / 2;
        //printf("mid=%d\n", mid);
        ret = guess(mid);
    }
    return mid;
}
/* 25 - 0(<100%) - 5.3MB, on Jan 9th, 2022 */
