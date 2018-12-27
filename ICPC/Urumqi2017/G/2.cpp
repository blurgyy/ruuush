#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;
const int INF = 0x7fffffff;

char s1[maxn], s2[20], op[2];
int rec[maxn], rec2[maxn], Next[20];
int T, N, slen, plen;
struct segTree
{
    int left, right;
    int value;
    int lazy;
}Tree[maxn<<2];

void Build(int nowNode, int left, int right){
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    if(left == right){
        Tree[nowNode].value = rec[right];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
}

void change(int nowNode, int aleft, int aright, int add){
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(aleft <= left && right <= aright){
        Tree[nowNode].lazy += add;
        return;
    }
    int mid = (left + right)>>1;
    if(aleft <= mid)change(nowNode<<1, aleft, aright, add);
    if(mid < aright)change(nowNode<<1|1, aleft, aright, add);
}

void Update(int nowNode, int pos, char after){
    s1[pos-1] = after;
    int i = pos-1-(plen-1), j = 0, end = pos-1+(plen-1);
    while(i <= end){
        if(j == -1 || s1[i] == s2[j])
            ++ i, ++ j;
        else j = Next[j];
        if(j == plen){
            if(rec2[i] == 0)change(1, i, strlen(s1), 1);
            j = Next[j];
        }
        else{
            if(rec2[i] == 1)change(1, 1, strlen(s1), -1);
        }
    }
}

int Query(int nowNode, int node){
    if(Tree[nowNode].left == Tree[nowNode].right)
        return Tree[nowNode].value + Tree[nowNode].lazy;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    int mid = (left + right)>>1;
    if(node <= mid){
        Tree[nowNode<<1].lazy += Tree[nowNode].lazy;
        Tree[nowNode].lazy = 0;
        return Query(nowNode<<1, node);
    }
    else{
        Tree[nowNode<<1|1].lazy += Tree[nowNode].lazy;
        Tree[nowNode].lazy = 0;
        return Query(nowNode<<1|1, node);
    }
}

void Get_next(){
    int i = 0, j = -1;
    memset(Next, 0, sizeof(Next));
    Next[0] = -1;
    while(i < plen){
        if(j == -1 || s2[i] == s2[j]){
            ++ i, ++ j;
            if(s2[i] == s2[j])
                Next[i] = Next[j];
            else Next[i] = j;
        }
        else j = Next[j];
    }
}

void KMP(){
    int slen = strlen(s1);
	if(plen == 1){
        for(int i = 0; i < slen; ++ i){
            if(s1[i] == s2[0])
                rec[i+1] = rec[i] + 1;
            else rec[i+1] = rec[i];
        }
        return;
    }
	int i = 0, j = 0, p = 0;
	while(i < slen){
        if(j == -1 || s1[i] == s2[j])
            ++ i, ++ j;
        else
            j = Next[j];
        if(j == plen){
            rec[i] = ++ p;
            rec2[i] = 1;
            j = Next[j];
        }
    }
    for(int i = 1; i <= slen; ++ i)
        if(rec[i] == 0)rec[i] = rec[i-1];
}

int main(){
    scanf("%d", &T);
    while(T--){
        memset(rec, 0, sizeof(rec));
        scanf("%d", &N);
        scanf("%s%s", s1, s2);
        slen = strlen(s1);
        plen = strlen(s2);
        Get_next();
        KMP();
        //for(int i = 1; i <= strlen(s1); ++ i)
          //  printf("%d ", rec[i]);
        //printf("\n");AC
        Build(1, 1, strlen(s1));
        while(N--){
            scanf("%s", op);
            if(!strcmp(op, "C")){
                int pos;
                char change[2];
                scanf("%d%s", &pos, change);
                Update(1, pos, change[0]);
            }
            else{
                int s, e;
                scanf("%d%d", &s, &e);
                int ans = 0;
                if(e - s + 1 < plen)ans = 0;
                else ans = Query(1, e) - Query(1, s);
                int wwwww = 0;
                int li = s + plen - 2;
                for(int i = s + 1; i <= li; i ++){
                   //printf("%d\n", i);
                    if(rec[i] != rec[i - 1]){
                     //   printf("%d %d\n", rec[i], rec[i - 1]);
                        wwwww = 1;
                        break;
                    }
                }
                printf("%d\n", max(0, ans - wwwww));
            }
        }
    }
    return 0;
}

/**

1
5
AABBABA
AA
Q 1 3
C 6 A
Q 2 7
C 2 B
Q 1 5


5
abababa
aba
Q 1 3
Q 1 5
Q 1 7
Q 3 5
Q 2 7

*/
