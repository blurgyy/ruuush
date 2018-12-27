//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 100010;
const char out[2][5] = {"No.", "Yes."};

vector<int> E[26];
bool ans;
char in[30];

int idx(char ch){
    return ch - 'a';
}

bool vis[26];
void dfs(int now = idx('b')){
    int len = E[now].size();
    vis[now] = true;
    for(int i = 0; i < len; ++ i){
        if(E[now][i] + 'a' == 'm'){
            ans = true;
            return;
        }
        if(!vis[E[now][i]])dfs(E[now][i]);
        if(ans)return;
    }
}

int main(){
    while(~scanf("%s", in)){
        ans = false;
        memset(vis, 0, sizeof(vis));
        if(strcmp(in, "0")){
            E[idx(in[0])].push_back(idx(in[strlen(in)-1]));
            continue;
        }
        dfs();
        //bfs();
        printf("%s\n", out[ans]);
        for(int i = 0; i < 26; ++ i)
            E[i].clear();
    }
    return 0;
}
