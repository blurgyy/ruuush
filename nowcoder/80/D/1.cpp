#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, cnt;
double T, w[maxn], mn;
priority_queue<pair<double, int> > que;

int main(){
    while(~scanf("%lf%d", &T, &n)){
        while(que.size())que.pop();
        mn = 1e10;
        cnt = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%lf", w + i);
            que.push(make_pair(w[i], 1));
            mn = min(mn, w[i]);
        }
        while(mn / que.top().first < T){
            pair<double, int> now = que.top();
            que.pop();
            now.first = now.first * now.second / (++ now.second);
            mn = min(now.first, mn);
            //printf("mn = %f\n", mn);
            que.push(now);
            cnt ++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}