#include<cstdio>
#include<cstring>
#include<queue>
const char out[2][5] = {"No.", "Yes."};

char in[20];
std::vector<int> E[26];
bool vis[26], ans;

void bfs(){
    std::queue<int> Q;
    Q.push('b'-'a');
    while(Q.size()){
        int now = Q.front();
        vis[now] = true;
        Q.pop();
        for(int i = 0; i < E[now].size(); ++ i){
            if(E[now][i] == 'm' - 'a'){
                ans = true;
                return;
            }
            if(!vis[E[now][i]])Q.push(E[now][i]);
        }
    }
}

int main(){
    while(~scanf("%s", in)){
        if(strcmp(in, "0")){
            E[in[0]-'a'].push_back(in[strlen(in)-1]-'a');
            continue;
        }
        memset(vis, false, sizeof(vis));
        ans = false;
        bfs();
        printf("%s\n", out[ans]);
        for(int i = 0; i < 26; ++ i)
            E[i].clear();
    }
    return 0;
}
