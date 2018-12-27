#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
const int maxm = 20010;

struct Node{
    vector<int> athand;
    int pos, prep;
}node[maxn];
int T, Case = 0;
int n, m;
int cd[maxm];
int cdtop;
int lastone;
int ontable;
int winner;

int nxt(int x){
    if(x == 2)return -1;
    if(x == 13)return 1;
    return x + 1;
}

bool better(int a, int b){
    //printf("%d comp %d\n", a, b);
    if(ontable == -1){
        if(a >= 3){
            if(b >= 3){
                return a < b;
            }
            else {
                return true;
            }
        }
        if(a < 3){
            if(b >= 3){
                return false;
            }
            else {
                return a < b;
            }
        }
    }
    else {
        int dsgn = nxt(nxt(ontable));
        if(a == dsgn)return false;
        if(b == dsgn)return true;
        return false;
    }
}

void drawcard(int count = 5, int currentplayer = 0){
    int now = currentplayer;
    for(int cnt = 0; cnt < count && cdtop < m; ++ cnt)
        node[now].athand.push_back(cd[cdtop++]);
    now = (now + 1) % n;
    while(now != currentplayer && cdtop < m){
        for(int cnt = 0; cnt < count && cdtop < m; ++ cnt)
            node[now].athand.push_back(cd[cdtop++]);
        now = (now + 1) % n;
    }
}

void test(int x){
    printf("%dth left: ", x);
    for(int i = 0; i < node[x].athand.size(); ++ i){
        printf("%d ", node[x].athand[i]);
    }
    printf("\n");
}

void init(){
    for(int i = 0; i < maxn; ++ i){
        node[i].athand.clear();
        node[i].prep = -1;
        node[i].pos = -1;
        //printf("node[%d].prep = %d\n", i, node[i].prep);
    }
    memset(cd, 0, sizeof(cd));
    lastone = -1;
    ontable = -1;
    cdtop = 0;
    winner = -1;
}

int main(){
    //freopen("out.out", "w", stdout);

    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++ i){
            scanf("%d", cd + i);
        }
        int currentplayer = 0;
        drawcard(5, currentplayer);
        while(true){        //iterate players.
            //printf("%dth player left %d cards\n", currentplayer, node[currentplayer].athand.size());
            if(currentplayer == lastone){
                drawcard(1, currentplayer);
                //printf("draw cards\n");
                ontable = -1;
            }
            //test(currentplayer);
            if(ontable == -1){
                for(int i = 0; i < node[currentplayer].athand.size(); ++ i){
                    if(node[currentplayer].prep == -1){
                        node[currentplayer].prep = node[currentplayer].athand[i];
                        //printf("%d(%d)\n", node[currentplayer].prep, currentplayer);
                        node[currentplayer].pos = i;
                    }
                    else if(better(node[currentplayer].athand[i], node[currentplayer].prep)){
                        //printf("%d better than %d\n", node[currentplayer].athand[i], node[i].prep);
                        node[currentplayer].prep = node[currentplayer].athand[i];
                        //printf("%d(%d))\n", node[currentplayer].prep, currentplayer);
                        node[currentplayer].pos = i;
                    }
                }
            }
            else {
                for(int i = 0; i < node[currentplayer].athand.size(); ++ i){
                    if(node[currentplayer].prep == -1){
                        if(node[currentplayer].athand[i] == 2 && ontable != 2 || node[currentplayer].athand[i] == nxt(ontable)){
                            node[currentplayer].prep = node[currentplayer].athand[i];
                            node[currentplayer].pos = i;
                        }
                    }
                    else {
                        if(node[currentplayer].athand[i] == nxt(ontable)){
                            node[currentplayer].prep = node[currentplayer].athand[i];
                            node[currentplayer].pos = i;
                        }
                    }
                }
            }
            if(node[currentplayer].prep != -1){
                ontable = node[currentplayer].prep;
                //printf("ontable: %d (from %d)\n", ontable, currentplayer);
                lastone = currentplayer;
                node[currentplayer].athand.erase(node[currentplayer].athand.begin() + node[currentplayer].pos);
                node[currentplayer].prep = -1;
                node[currentplayer].pos = -1;
            }
            //test(currentplayer);
            if(node[currentplayer].athand.size() == 0){
                //printf("winner is %d\n", currentplayer);
                winner = currentplayer;
                break;
            }

            currentplayer = (currentplayer + 1) % n;
            /*if(cdtop >= m){
                printf("finished\n");
                break;
            }*/
        }
        printf("Case #%d:\n", ++ Case);
        for(int x = 0; x < n; ++ x){
            if(x == winner){
                printf("Winner\n");
                continue;
            }
            int pen = 0;
            for(int i = 0; i < node[x].athand.size(); ++ i){
                pen += node[x].athand[i];
            }
            printf("%d\n", pen);
        }
    }
    return 0;
}

/**

100
2 14
3 4 5 6 7  4 5 6 7 8  2 2 2 2

*/
