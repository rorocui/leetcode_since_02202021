double pow_tail_recursion(double x, long n)
{
   double ret = 0.0; 
    
   if(n == 1) return x;
   if(n % 2 == 0) 
   {
       ret = pow_tail_recursion(x, n / 2);
       return ret * ret; 
   }
    else
    {
       return pow_tail_recursion(x, n / 2) * pow_tail_recursion(x, n - n / 2); 
    }
}

double myPow(double x, long n)
{
    if(n == 0) return 1.0; 
    if(x == 1) return 1.0;
    if(n < 0) x = 1/x; 
    
    return pow_tail_recursion(x, labs(n));
}
/* 304 - 0(<100%) - 5.5, on Aug 4st, 2021 */
/*

double myPow(double x, long n)
{
   double ret;
    

   if(n == 0) return 1; 
   if(n == 1) return x;
   if(n < 0)
   {
      n = labs(n); 
      x = 1 / x; 
   }  
    
    if(n % 2 == 0)
    {
        ret = myPow(x, n / 2);
        return ret * ret;
    }
    else
    {
        return myPow(x, n / 2) * myPow(x, n - n / 2);
    }
}

*/
/* Non tail recursion method */
/* 304 - 0(<100%) - 5.4, on Aug 1st, 2021 */
