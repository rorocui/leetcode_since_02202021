
int maxProfit(int* prices, int pricesSize)
{
    int profit = 0;
    int i;
    
    for(i = 0; i < pricesSize - 1; i++)
    {
        if(prices[i + 1] > prices[i])
            profit += prices[i + 1] - prices[i];
    }
    
    return profit;
    
}

/* 200 - 3ms(<93%) - 6.8MB, on Oct 11th, 2021 */
    
/*
int maxProfit(int* prices, int pricesSize)
{
    int buy, sell, sell_search;
    int profit = 0;

    buy = sell = 0;
    sell_search = 1;
    while(sell_search < pricesSize)
    {
        while(sell_search < pricesSize && prices[buy] > prices[sell_search])
            buy = sell_search++;
        if(sell_search < pricesSize) sell = sell_search++;
        else    break;
        while(sell_search < pricesSize && prices[sell] < prices[sell_search])
            sell = sell_search++;
        //printf("buy=%d,sell=%d\n", buy, sell);
        if(sell < pricesSize) profit += (prices[sell] - prices[buy]);
        else break;
        buy = sell_search++;
    }

    return profit;

}
*/
/* 200 - 8ms(<22%) - 6.6MB, on Oct 11th, 2021 */

