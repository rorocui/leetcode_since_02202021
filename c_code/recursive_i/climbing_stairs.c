

int climbStairs(int n){
    int stair[n + 1];
    int i;
    
    if(n <= 2) return n;
    for(i = 0; i <= n; i++)
    {
        if(i <=2) stair[i] = i;
        else
            stair[i] = stair[i - 1] + stair[i - 2];
    }
    
    return stair[n];
    
}
/ 45 - 0(<100%) - 5.4MB, on July 29th, 2021 */
