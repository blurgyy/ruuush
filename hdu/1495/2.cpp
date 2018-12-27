#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

struct node{
    int s, cnt;
    node(int _s, int _cnt){
        s = _s;
        cnt = _cnt;
    }
};
int s, n, m;

int main(){
    while(~scanf("%d%d%d", &s, &n, &m) && s && n && m){
        if(s & 1){
            printf("NO\n");
            continue;
        }
        queue<node> que;
        que.push(node(s>>1, 1));
        int ans = INF;
        while(que.size()){
            node now = que.front();
            //printf("%d %d\n", now.s, now.cnt);
            if(now.s <= 0){
                ans = now.cnt;
                break;
            }
            que.pop();
            if(now.s >= n)
                que.push(node(now.s - n, now.cnt + 1));
            if(now.s >= m)
                que.push(node(now.s - m, now.cnt + 1));
        }
        if(ans == INF)printf("NO\n");
        else printf("%d\n", ans);
    }
    return 0;
}