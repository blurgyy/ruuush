#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;

struct Edge{
    int s, d, c;
}E[maxn<<2];
int n, pos, pg, pr, pb, pe;
int gp[maxn], rp[maxn], bp[maxn];
char cl[5];

bool cmp(Edge a, Edge b){
    return a.c < b.c;
}

void add_edge(int s, int d, int c){
    E[pe].s = s;
    E[pe].d = d;
    E[pe++].c = c;
    E[pe].s = d;
    E[pe].d = s;
    E[pe++].c = c;
}

int bs(int e, int arr[], int left, int right){
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int main(){
    while(~scanf("%d", &n)){
        pg = pr = pb = pe = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d%s", &pos, cl);
            if(!strcmp(cl, "G")){
                gp[pg++] = pos;
            }
            else if(!strcmp(cl, "R")){
                rp[pr++] = pos;
            }
            else {
                bp[pb++] = pos;
            }
        }
        int ans = 0;
        for(int i = 1; i < pg; ++ i)
            ans += gp[i] - gp[i-1];
        for(int i = 0; i < pr; ++ i){
            int npos = bs(rp[i], gp, 0, gp - 1);
            if(gp[npos] == rp[i])continue;
            add_edge(rp[i], gp[npos]);
            add_edge(rp[i], gp[npos+1]);
        }
    }
    return 0;
}