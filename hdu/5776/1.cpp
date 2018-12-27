//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;

int T, x[maxn], n, m;

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        int tmp, SUM = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &tmp);
            x[i] = tmp % m;
            SUM += x[i];
        }
        int front = 0, rear = 1, sum = x[0];
        if(sum == 0 || SUM % m == 0){
            printf("YES\n");
            continue;
        }
        int mod = 0;
        for(int i = 1; i*m < SUM; ++ i){
            mod = i * m;
            while(front < rear && rear <= n && sum != mod){
                //printf("mod = %d\n", mod);
                //printf("front = %d, rear = %d\n", front, rear);
                while(sum < mod)sum += x[rear++];
                while(sum > mod)sum -= x[front++];
            }
            if(sum == mod)break;
        }
        //printf("sum = %d, mod = %d\n", sum, mod);
        if(sum == mod){
            printf("YES\n");
        }
        else printf("NO\n");
    }
    return 0;
}