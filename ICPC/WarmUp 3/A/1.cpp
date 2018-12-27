#include<bits/stdc++.h>
using namespace std;
const int maxn = 5010;

int E, A, B, P;
vector<int> f[maxn], s[maxn];
bool MARK[maxn];
int ans;
int cnt;
int check;
void dfsf(int pt, bool mark[]){
    if(mark[pt])
        return;
    mark[pt] = true;
    cnt++;
    if(check < cnt)
        return;
    for(int i = 0; i < f[pt].size(); i++)
        dfsf(f[pt][i],mark);
}
void dfss(int pt, bool mark[]){
    if(mark[pt])return;
    mark[pt] = true;
    cnt++;
    if(check < cnt)
        return;
    for(int i = 0; i < s[pt].size(); i++)
        dfss(s[pt][i],mark);
}

void DFS(int pt, bool father){
    if(MARK[pt])return;
    MARK[pt] = true;
    bool mark[maxn] = {0};
    cnt = 0;
    if(father){
        dfsf(pt,mark);
        //cout << pt  << ' ' << cnt << endl;
        if(cnt <= check)return;
        ans ++;
        int len = f[pt].size();
        for(int i = 0; i < len; ++ i){
            DFS(f[pt][i], father);
        }
    }
    else{
        dfss(pt,mark);
        //cout << pt  << ' ' << cnt << endl;
        if(cnt <= check)return;
        ans ++;
        int len = s[pt].size();
        for(int i = 0; i < len; ++ i){
            DFS(s[pt][i], father);
        }
    }
}

int main(){
    cin >> A >> B >> E >> P;
    for(int i = 0; i < P; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        f[a].push_back(b);
        s[b].push_back(a);
    }
    ans = 0;
    check = E - A;
    for(int i = 0; i < E; i++) MARK[i] = false;
    for(int i = 0; i < E; i++)
    {
        if(!s[i].size())
            DFS(i,true);
    }
    cout << ans << endl;
    ans = 0;
    check = E - B;
    for(int i = 0; i < E; i++) MARK[i] = false;
    for(int i = 0; i < E; i++)
    {
        if(!s[i].size())
            DFS(i,true);
    }
    cout << ans << endl;
    ans = 0;
    check = B;
    for(int i = 0; i < E; i++) MARK[i] = false;
    for(int i = 0; i < E; i++)
    {
        if(!f[i].size())
            DFS(i,false);
    }
    cout << ans << endl;
    return 0;
}