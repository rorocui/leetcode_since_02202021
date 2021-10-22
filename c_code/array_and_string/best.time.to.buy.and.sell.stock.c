int maxProfit(int* prices, int pricesSize)
{
    int max_profit = 0,
        min_index = 0,
        max_index,
        i;

    if(pricesSize == 1) return 0;
    while(min_index < (pricesSize - 1) && prices[min_index] >= prices[min_index + 1])
        min_index++;
    if(min_index == pricesSize - 1) return 0;
	    
    while(min_index < pricesSize)
    {
	    max_index = min_index + 1;
	    for(i = max_index; i < pricesSize; i++)
	        if(prices[i] > prices[max_index])
	            max_index = i;
	
	    max_profit = (prices[max_index] - prices[min_index] > max_profit) ? prices[max_index] - prices[min_index] : max_profit;
	    for(i = min_index + 1; i < pricesSize; i++)
	        if(prices[i] < prices[min_index])
            {
	            min_index = i;
                break;
            }
        
        if(i == pricesSize || min_index >= pricesSize - 1) break;
    }


    return max_profit;

}

/* 211 - 258(<10%) - 13.1MB, on Oct 22nd, 2021 */
