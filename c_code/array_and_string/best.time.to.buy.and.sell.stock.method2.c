int maxProfit(int* prices, int pricesSize)
{
    int i,
        min = prices[0],
        profit = 0;

    for(i = 1; i < pricesSize; i++)
    {
        if(prices[i] > min)
            profit = (prices[i] - min > profit) ? prices[i] - min : profit;
        else
            min = prices[i];
    }

    return profit;

}
/* 211 - 108(<96%) - 12.8, on Oct 22nd, 2021 */
