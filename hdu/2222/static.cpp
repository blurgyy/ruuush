//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<queue>
using namespace std;
const int type_N = 26;
const int maxn = 1e6;
const int LEN = 60;

int n;
char in[LEN], text[1000010];

int idx(char ch){                                   ///\param   字符
    return ch - 'a';                                ///\return  index
}

struct Trie{
    int fail[maxn],                                 ///fail
        nxt[maxn][type_N],                          ///每个节点的nxt
        cnt[maxn],                                  ///cnt[i]: 在节点i结束的串个数
        sz;                                         ///树大小
    char ch[maxn];                                  ///当前结点字符

    void init(){                                    ///\brief   初始化
        memset(fail, -1, sizeof(fail));
        memset(nxt, -1, sizeof(nxt));
        memset(cnt, 0, sizeof(cnt));
        sz = 1;
    }
    void insert(const char *s){                     ///\param \brief   插入串
        int index;
        int now = 0, tmp;
        while(*s){
            index = idx(*s);
            if(nxt[now][index] == -1){
                tmp = sz ++;
                memset(nxt[tmp], -1, sizeof(nxt[tmp]));
                nxt[now][index] = tmp;
            }
            now = nxt[now][index];
            ++ s;
        }
        ++ cnt[now];
        //printf("cnt[%d] = %d\n", now, cnt[now]);
    }
    void Get_fail(){                                ///\brief 建立AC自动机
        queue<int> Q;
        Q.push(0);
        int now, son, anc;
        while(Q.size()){
            //printf("Q.size = %d\n", Q.size());
            now = Q.front();
            Q.pop();
            for(int i = 0; i < type_N; ++ i){
                //printf("fail[0] = %d\n", fail[0]);
                son = nxt[now][i];
                //printf("son = %d, now = %d, i = %d", son ,now, i);
                //printf("son = %d");
                //getchar();
                if(son + 1){                        //if(son != -1)
                    Q.push(son);
                    if(now == 0){
                        fail[son] = 0;
                        continue;
                    }
                    anc = fail[now];
                    while(anc + 1){                 //while(anc != -1)
                        if(nxt[anc][i] + 1){        //if(nxt[anc][i] != -1)
                            fail[son] = nxt[anc][i];
                            break;
                        }
                        anc = fail[anc];
                    }
                    if(!(anc + 1))                  //if(anc == -1)
                        fail[son] = 0;
                }
            }
        }
    }
    int Match(char *s){                             ///\brief 查找串s中出现过的模板串的次数
        //printf("wtf");
        int index, now = 0, match;
        int ret = 0;
        while(*s){
            //printf("%c", *s);
            index = idx(*s);
            while(now && !(nxt[now][index] + 1))       //while(now != 0 && nxt[now][index] == -1)
                now = fail[now];
            now = nxt[now][index];
            match = now;
            if(!(now + 1))                          //if(now == -1)
                now = 0;
            //printf("match = %d\n", match);
            //int Time = 0;
            while(match + 1){
                //if(Time++ > 10500000)printf("wa!!\n");
                ret += cnt[match];
                //printf("cnt[%d] = %d", match, cnt[match]);
                //getchar();
                match = fail[match];
            }
            ++ s;
        }
        return ret;
    }
}ac;

int main(){
    int T;
    ac.init();
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        while(n--){
            scanf("%s", in);
            ac.insert(in);
        }
        scanf("%s", text);
        ac.Get_fail();
        printf("%d\n", ac.Match(text));
        for(int i = 0; i < ac.sz; ++ i){
            ac.fail[i] = -1;
            memset(ac.nxt[i], -1, sizeof(ac.nxt[i]));
            ac.cnt[i] = 0;
        }
        ac.sz = 1;
    }
    return 0;
}

/**

5
abc bc a b c
abc

5
she he say shr her
yasherhs

*/
