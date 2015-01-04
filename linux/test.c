#include <stdio.h>

int add(int a, int b)
{
    int sum = a + b;
   
    return sum;
}


int fibonacci(int n)
{
    if (n == 1 || n == 2) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n-2);
    }
}


int main(int argc, char *argv[])
{
    int a = 1, b = 2, sum, fib;
    
    sum = add(a, b);
    fib = fibonacci(3);
    printf("%d + %d = %d, fibonacci(%d) = %d\n", a, b, sum, 3, fib);

    return 0;
}
