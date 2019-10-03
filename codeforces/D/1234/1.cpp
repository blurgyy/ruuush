#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int SIGMA = 26;

struct STN{
    int left, right;
    int cnt[SIGMA];
    STN(){
        left = right = -1;
        memset(cnt, 0, sizeof(cnt));
    }
}Tree[maxn<<2];
char s[maxn];
int q, op, pos, l, r;

void pushUp(int now){
    for(int i = 0; i < SIGMA; ++ i){
        Tree[now].cnt[i] = Tree[now<<1].cnt[i] + Tree[now<<1|1].cnt[i];
    }
}

void build(int left, int right, int now = 1){
    Tree[now].left = left;
    Tree[now].right = right;
    if(left == right){
        Tree[now].cnt[s[right]-'a'] = 1;
        return;
    }
    int mid = left + right >> 1;
    build(left, mid, now << 1);
    build(mid + 1, right, now << 1 | 1);
    pushUp(now);
}

void update(int pos, char ch, int now = 1){
    int left = Tree[now].left;
    int right = Tree[now].right;
    if(left == right){
        Tree[now].cnt[s[right]-'a'] = 0;
        Tree[now].cnt[ch-'a'] = 1;
        s[right] = ch;
        return;
    }
    int mid = left + right >> 1;
    if(pos <= mid) update(pos, ch, now << 1);
    else update(pos, ch, now << 1 | 1);
    pushUp(now);
}

void query(int qleft, int qright, set<int> &rec, int now = 1){
    int left = Tree[now].left;
    int right = Tree[now].right;
    if(qleft <= left && right <= qright){
        for(int i = 0; i < SIGMA; ++ i){
            if(Tree[now].cnt[i]){
                rec.insert(i);
            }
        }
        return;
    }
    int mid = left + right >> 1;
    if(qleft <= mid)query(qleft, qright, rec, now << 1);
    if(qright > mid)query(qleft, qright, rec, now << 1 | 1);
}

int main(){
    while(~scanf("%s%d", s+1, &q)){
        int len = strlen(s+1);
        build(1, len);
        while(q --){
            scanf("%d", &op);
            if(op == 1){
                char ch[2];
                scanf("%d%s", &pos, ch);
                update(pos, ch[0]);
            }
            else if(op == 2){
                scanf("%d%d", &l, &r);
                set<int> rec;
                query(l, r, rec);
                printf("%d\n", (int)(rec.size()));
            }
            else {
                printf("wtf\n");
            }
        }
    }
    return 0;
}
