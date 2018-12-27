#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int type_N = 26;                  ///字符种类数
const int maxn = 300010;                ///Trie上的节点个数
const int LEN = 60;                     ///模板串长度

int T, n;
char in[LEN], text[1000010];

int idx(char ch){
    return ch - 'a';
}

struct Trie{
    /**/
    int nxt[maxn][type_N],              ///父子关系
        fail[maxn],                     ///fail
        cnt[maxn];                      ///cnt[i]: 节点i处结束的串个数
    int sz;
    /**/
    void init(){                        ///\brief   初始化
        memset(nxt, -1, sizeof(nxt));
        memset(fail, -1, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
        sz = 1;
    }
    void insert(const char *s){         ///\brief \param 插入
        int now = 0, index, tmp;
        while(*s){
            index = idx(*s);
            if(nxt[now][index] == -1){
                tmp = sz++;
                nxt[now][index] = tmp;
            }
            now = nxt[now][index];
            ++ s;
        }
        cnt[now] ++;
    }
    void Get_fail(){                    ///\brief 建立AC自动机
        queue<int> Q;
        Q.push(0);
        int now, son, anc;
        while(!Q.empty()){
            now = Q.front();
            Q.pop();
            for(int i = 0; i < type_N; ++ i){
                son = nxt[now][i];
                if(son == -1)continue;
                Q.push(son);
                if(now == 0){
                    fail[son] = 0;
                    continue;
                }
                anc = fail[now];
                while(anc != -1){
                    if(nxt[anc][i] != -1){
                        fail[son] = nxt[anc][i];
                        break;
                    }
                    anc = fail[anc];
                }
                if(anc == -1)
                    fail[son] = 0;
            }
        }
    }
    int Match(const char *s){       ///\brief \return 串s中模板串的出现次数
        int now = 0, index, match;
        int ret = 0;
        while(*s){
            index = idx(*s);
            while(now != 0 && nxt[now][index] == -1)
                now = fail[now];
            now = nxt[now][index];
            match = now;
            if(now == -1)now = 0;
            while(match != -1){
                ret += cnt[match];
                cnt[match] = 0;
                match = fail[match];
            }
            ++ s;
        }
        return ret;
    }
    /**/
}ac;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        ac.init();
        scanf("%d", &n);
        while(n--){
            scanf("%s", in);
            ac.insert(in);
        }
        scanf("%s", text);
        ac.Get_fail();
        printf("%d\n", ac.Match(text));
    }
    return 0;
}
