
int power(int x, int y)
{
   return (int)pow((float)x, y); 
}

int kthGrammar(int n, int k)
{
    int mid = 0;
    
    //printf("n=%d,k=%d\n", n, k);
    if(n == 1 && k == 1) return 0;
    mid = power(2, n - 1) / 2; 
    if(mid < k)
        return !kthGrammar(n - 1, k - mid);
    else
        return kthGrammar(n - 1, k);

}

/* 55 - 0(n/a) - 5.7, Aug 7th, 2021 */
