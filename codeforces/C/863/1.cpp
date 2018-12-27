#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node
{
    int a, b;
    int add[2];
}node[100];
ll k, a, b, ans[2];
int alice[5][5], bob[5][5], rec[2];
map<pii, int> vis;

int main(){
    while(~scanf("%I64d%d%d", &k, &a, &b)){
        for(int i = 1; i < 4; ++ i)
            for(int j = 1; j < 4; ++ j)
                scanf("%d", alice[i] + j);
        for(int i = 1; i < 4; ++ i)
            for(int j = 1; j < 4; ++ j)
                scanf("%d", bob[i] + j);
        vis.clear();
        ans[0] = ans[1] = 0;
        rec[0] = rec[1] = 0;
        memset(node, 0, sizeof(node));
        if(a - b == 1 || a == 1 && b == 3)++ ans[0];
        else ++ ans[1];
        vis[make_pair(a, b)] = 0;
        int nxta = a, nxtb = b;
        int pos, p = 0, cnt = 0;
        while(true){
            vis[make_pair(nxta, nxtb)] = p;
            printf("nxta = %d, nxtb = %d\n", nxta, nxtb);
            a = nxta, b = nxtb;
            nxta = alice[a][b];
            nxtb = bob[a][b];
            node[++p].a = nxta;
            node[p].b = nxtb;
            if(nxta - nxtb == 1 || nxta == 1 && nxtb == 3)node[p].add[0] = node[p-1].add[0] + 1;
            else node[p].add[1] = node[p-1].add[1] + 1;
            if(vis[make_pair(nxta, nxtb)]){
                for(int i = 0; i <= p; ++ i)
                    if(node[i].a == a && node[i].b == b){
                        pos = i;
                        break;
                    }
                cnt = p - pos;
                break;
             }
        }
        ans[0] += ((k-1) / cnt) * (node[p].add[0] - node[pos].add[0]);
        ans[1] += ((k-1) / cnt) * (node[p].add[1] - node[pos].add[1]);
        ans[0] += (k % cnt) * (node[pos+(k%cnt)].add[0] - node[pos].add[0]);
        ans[1] += (k % cnt) * (node[pos+(k%cnt)].add[1] - node[pos].add[1]);
        printf("%I64d %I64d\n", ans[0], ans[1]);
    }
    return 0;
}