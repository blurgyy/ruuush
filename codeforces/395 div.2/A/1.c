#include<stdio.h>
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
int main()
{
    int n, m, z;
    while(scanf("%d%d%d", &n, &m, &z) != EOF)
    {
        printf("%d\n", z / lcm(n, m));
    }
    return 0;
}
