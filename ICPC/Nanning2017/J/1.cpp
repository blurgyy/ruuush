#include<bits/stdc++.h>
using namespace std;

int n;
char n1[10], n2[10];
int ans;

int main(){
    scanf("%d", &n);
    for(int ii = 0; ii < 5; ++ ii){
        ans = 0;
        scanf("%s%s", n1, n2);
        if(n1[0] == n2[0])
            for(int i = 0; i < n; ++ i)
                if(n1[i] != n2[i]){
                    swap(n1[0], n1[i]);
                    break;
                }
        int tmp = n;
        while(tmp--){
            for(int i = n-1; i > 0; -- i){
                if(n1[i] == n2[i])continue;
                if(n1[0] == n2[i]){
                    ++ ans;
                    swap(n1[0], n1[i]);
                }
            }
            if(n1[0] == n2[0] && tmp)
                for(int i = 0; i < n; ++ i)
                if(n1[i] != n2[i]){
                    swap(n1[0], n1[i]);
                    break;
                }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/**

4
1234 4231
1234 3124
2341 1324
3214 4213
3214 2143

9
356879421
546978321

5
15432
54321

*/