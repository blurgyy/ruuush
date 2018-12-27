 #include<bits/stdc++.h>
using namespace std;
const int maxn = 100010; 

int m, a[maxn];

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int bs(int e, int left = 0, int right = m-1){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= a[mid])return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

bool check(int e){
    return a[bs(e)] == e;
}

int main(){
    while(~scanf("%d", &m)){
        for(int i = 0; i < m; ++ i)
            scanf("%d", a + i);
        int rec[maxn];
        bool ans = true;
        memset(rec, 0, sizeof(rec));
        for(int i = 0; i < m; ++ i){
            for(int j = i+1; j < m; ++ j){
                if(a[j] % a[i]){
                    rec[i] = j;
                    break;
                }
            }
            if(rec[i]){
                int g = gcd(a[i], a[i+1]);
                for(int k = i+2; k < rec[i]; ++ k)
                    g = gcd(g, a[k]);
                if(!check(g)){
                    ans = false;
                    break;
                }
                else{
                    printf("%d\n", bs(g));
                }
            }
        }
        if(ans){
            int out[maxn], p = 0;
            for(int i = 0; i < m; ++ i)
                if(rec[i]){
                    for(int j = i; j < m; ++ j)
                        out[p++] = a[j];
                }
            if(p == 0){
                printf("%d\n", m);
                for(int i = 0; i < m; ++ i)
                    printf("%d%c", a[i], " \n"[i == m-1]);
            }
            else{
                printf("%d\n", p);
                for(int i = 0; i < p; ++ i)
                    printf("%d%c", out[i], " \n"[i == p-1]);
            }
        }
        else printf("-1\n");
    }
    return 0;
}