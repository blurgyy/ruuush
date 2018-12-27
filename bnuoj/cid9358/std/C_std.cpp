#include<bits/stdc++.h>
using namespace std;
int main() {
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        printf("%.12f\n", (n*n-1)/3.0);
    }
    return 0;
}
