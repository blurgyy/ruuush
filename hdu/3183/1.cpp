#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
char in[maxn];

int main(){
    while(~scanf("%s%d", in, &n)){
        priority_queue<pair<char, int> > que;
        char ans[maxn] = {0};
        int len = strlen(in), tp = len - n;
        if(tp == 0){
            printf("0\n");
            continue;
        }
        for(int i = 0; i < tp; ++ i){
            ans[i] = in[i];
            //printf("(%c, %d)\n", ans[i], -i);
            que.push(make_pair(ans[i], -i));
        }
        for(int i = tp; i < len; ++ i){
            if(in[i] > que.top().first)continue;
            ans[-que.top().second] = '#';
            ans[tp++] = in[i];
            que.pop();
            que.push(make_pair(in[i], 1-tp));
        }
        int pos = 0;
        for(int i = 0; i < len; ++ i)
            if(ans[i] != '#' && ans[i] != '0'){
                pos = i;
                break;
            }
        bool no_output = true;
        for(int i = pos; i < len; ++ i){
            if(ans[i] != '#' && ans[i] != 0){
                no_output = false;
                printf("%c", ans[i]);
            }
        }
        if(no_output)printf("0");
        printf("\n");
    }
    return 0;
}