///TLE
///First line an inteter c, indecating the number of the test cases. = =

#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 20010;

struct node{
    int l, r;
}itv[maxn];
int T, n, p, disc[maxn];
int ans[maxn];

int bs(int e, int left = 0, int right = p){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(disc[mid] > e)return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    /*printf("1000\n");
    int ti = 1000;
    while(ti--){
        printf("1000\n");
        for(int i = 1; i < 1001; ++ i)
            printf("%d\n", i);
    }
    return 0;*/
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        p = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d%d", &itv[i].l, &itv[i].r);
            disc[p++] = itv[i].l;
            disc[p++] = itv[i].r;
        }
        sort(disc, disc + p);
        p = unique(disc, disc + p) - disc;
        int maxx = p - 1;
        for(int i = 0; i < maxx; ++ i)
            ans[i] = i;
        for(int i = 0; i < n; ++ i){
            int l = bs(itv[i].l), r = bs(itv[i].r);
            ans[l] = l;
            for(int j = l+1; j <= r; ++ j)
                ans[j] = ans[j-1];
        }
        sort(ans + 1, ans + maxx + 1);
        printf("%d\n", unique(ans + 1, ans + maxx + 1) - ans - 1);
    }
    return 0;
}
