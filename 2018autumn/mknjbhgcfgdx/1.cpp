#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;
const int sigma = 4;

struct Palindromic_Tree{
    int child[maxn][sigma], fail[maxn];
    int depth[maxn], cnt[maxn];
    int size, last, len;
    char s[maxn];
    int idx(char ch){
        return ch - 'a';
    }
    int new_node(int length){
        memset(child[size], 0, sizeof(child[size]));
        fail[size] = 0;
        depth[size] = length;
        cnt[size] = 0;
        return size++;
    }
    void Extend(int ch, int pos){
        int p = last;
        while (s[pos - depth[p] - 1] != s[pos]){
            p = fail[p];
        }
        if (!child[p][ch]){
            int now = new_node(depth[p] + 2), fa = fail[p];
            while (s[pos - depth[fa] - 1] != s[pos])
                fa = fail[fa];
            fail[now] = child[fa][ch];
            if (fail[now] == 0) fail[now] = 1;
            child[p][ch] = now;
        }
        last = child[p][ch];
        cnt[last]++;
    }
    void init(char *x){
        len = strlen(x + 1);
        for (int i = 1; i <= len; i++)
            s[i] = x[i];
        size = 0;
        new_node(-1);
        new_node(0);
        fail[0] = fail[1] = 0;
        depth[0] = -1;
        last = 1;
        for (int i = 1; i <= len; i++)
            Extend(idx(s[i]), i);
    }
    //long long getans(){
    //    long long ans = 0;
    //    for (int i = size - 1; i > 0; i--){
    //        cnt[fail[i]] += cnt[i];
    //        ans = max(ans, (long long) cnt[i] * depth[i]);
    //    }
    //    return ans;
    //}
}PT;
char s[maxn];

int main(){
    while(~scanf("%s", s + 1)){
        PT.init(s);
        printf("size = %d\n", PT.size);
    }
    return 0;
}