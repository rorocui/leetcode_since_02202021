/* Time limit exceeded for tail recursion method
double pow_tail_recursion(double x, double base, long n)
{
   if(n == 0) return 1.0; 
   if(n == 1) return x;
   return pow_tail_recursion(x * base, base, n - 1);
}

long pow_tail_recursion_int(long x, int base, long n)
{
   printf("%ld,%ld\n", x, n);
   if(n == 0) return 1; 
   if(n == 1) return x;
   return pow_tail_recursion_int(x * base, base, n - 1);
}

double myPow(double x, long n)
{
    double ret;
    long   x_int;
    
    if(x == 1) return 1.0;
    x_int = (long)x;
    printf("%ld,%f\n", x_int, x);
    if(x_int == x) 
        ret = (double)pow_tail_recursion_int(x_int, (int)x_int, labs(n));
    else
        ret = pow_tail_recursion(x, x, labs(n));
    //ret = pow_tail_recursion(x, x, labs(n));
    if(n < 0)
      return  1 / ret;
    else
      return  ret;
}
*/

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

/* Non tail recursion method */
/* 304 - 0(<100%) - 5.4, on Aug 1st, 2021 */
