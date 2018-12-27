//#include <bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 205;
const int maxm = 20005;

struct Node{
    vector<int> athand;
    int pos, prep;
}node[maxn];
int T, Case = 1;
int n, m;
int lastplayer, winner, ontable, piletop;
int cards[maxm];
int nonsense;

int nxt(int x){
    if(x == 2)return -1;
    if(x == 13)return 1;
    return x + 1;
}

bool better(int a, int b){
    if(ontable != -1){
        int dsgn = nxt(nxt(ontable));
        if(a == dsgn)return false;
        if(b == dsgn)return true;
        return false;
    }
    else {
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
}

void drawcard(int count = 5, int currentplayer = 0){
    int now = currentplayer;
    for(int cnt = 0; cnt < count && piletop < m; ++ cnt)
        node[now].athand.push_back(cards[piletop++]);
    now = (now + 1) % n;
    while(now != currentplayer && piletop < m){
        for(int cnt = 0; cnt < count && piletop < m; ++ cnt)
            node[now].athand.push_back(cards[piletop++]);
        now = (now + 1) % n;
    }
}

int fp(int a, int b){
    int ans = 1;
    while(b){
        if(b&1)ans = (ans * a);
        a = (a * a);
        b >>= 1;
    }
    return ans;
}

void init(){
    for(int i = 0; i < maxn; ++ i){
        node[i].athand.clear();
        node[i].prep = -1;
        node[i].pos = -1;
    }
    memset(cards, 0, sizeof(cards));
    lastplayer = -1;
    ontable = -1;
    piletop = 0;
    winner = -1;
}

int main(){
	nonsense = fp(39, 900);
    scanf("%d", &T);
    while(T --){
        init();
        printf("Case #%d:\n", Case ++);
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++ i){
            scanf("%d", cards + i);
        }
        int currentplayer = 0;
        int now = currentplayer;
	    for(int cnt = 0; cnt < 5 && piletop < m; ++ cnt)
	        node[now].athand.push_back(cards[piletop++]);
	    now = (now + 1) % n;
	    while(now != currentplayer && piletop < m){
	        for(int cnt = 0; cnt < 5 && piletop < m; ++ cnt)
	            node[now].athand.push_back(cards[piletop++]);
	        now = (now + 1) % n;
	    }
        while(true){
            if(currentplayer == lastplayer){
                drawcard(1, currentplayer);
                ontable = -1;
            }
            if(ontable == -1){
                for(int i = 0; i < node[currentplayer].athand.size(); ++ i){
                    if(node[currentplayer].prep == -1){
                        node[currentplayer].prep = node[currentplayer].athand[i];
                        node[currentplayer].pos = i;
                    }
                    else if(better(node[currentplayer].athand[i], node[currentplayer].prep)){
                        node[currentplayer].prep = node[currentplayer].athand[i];
                        node[currentplayer].pos = i;
                    }
                }
            }
            else {
                for(int i = 0; i < node[currentplayer].athand.size(); ++ i){
                    if(node[currentplayer].prep != -1){
                        if(node[currentplayer].athand[i] == nxt(ontable)){
                            node[currentplayer].prep = node[currentplayer].athand[i];
                            node[currentplayer].pos = i;
                        }
                    }
                    if(node[currentplayer].prep == -1){
                        if(node[currentplayer].athand[i] == 2 && ontable != 2 || node[currentplayer].athand[i] == nxt(ontable)){
                            node[currentplayer].prep = node[currentplayer].athand[i];
                            node[currentplayer].pos = i;
                        }
                    }
                }
            }
            if(node[currentplayer].prep != -1){
                ontable = node[currentplayer].prep;
                lastplayer = currentplayer;
                node[currentplayer].athand.erase(node[currentplayer].athand.begin() + node[currentplayer].pos);
                node[currentplayer].prep = -1;
                node[currentplayer].pos = -1;
            }
            if(node[currentplayer].athand.size() == 0){
                winner = currentplayer;
                break;
            }
            currentplayer = (currentplayer + 1) % n;
        }
        for(int x = 0; x < n; ++ x){
            if(x == winner){
                printf("Winner\n");
                continue;
            }
            int penalty = 0;
            for(int i = 0; i < node[x].athand.size(); ++ i){
                penalty += node[x].athand[i];
            }
            printf("%d\n", penalty);
        }
    }
    return 0;
}

/**

100
2 14
3 4 5 6 7  4 5 6 7 8  2 2 2 2

*/