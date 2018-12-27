#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

struct node
{
    int val, id;
    bool operator< (node a){
        return val < a.val;
    }
}n[maxn];
int len, cnt[5], sum;
char in[maxn];

int bs(int e, int left = 0, int right = len){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(n[mid].val >= e)return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

bool by_id(node a, node b){
    return a.id < b.id;
}

void out(){
    int start = 0;
    for(int i = 0; i < len; ++ i){
        if(in[i] == 0 || in[i] == '0')continue;
        start = i;
        break;
    }
    for(int i = start; i < len; ++ i)
        printf("%c", in[i]);
    printf("\n");
}

int main(){
    while(~scanf("%s", in)){
        memset(cnt, 0, sizeof(cnt));
        len = strlen(in);
        sum = 0;
        for(int i = 0; i < len; ++ i)
            n[i].id = i;
        for(int i = 0; i < len; ++ i){
            n[i].val = (in[i] - '0') % 3;
            ++ cnt[n[i].val];
            sum += n[i].val;
            n[i].val = n[i].val == 0 ? 3 : n[i].val;
        }
        printf("sum = %d\n", sum);
        sum %= 3;
        if(!sum){
            printf("%s\n", in);
            continue;
        }
        sort(n, n + len);
        /*if(cnt[1] && cnt[2]){
            if(!((sum - 1) % 3))
                in[n[0].id] = 0;
            else
                in[n[bs(2)].id] = 0;
        }*/
        bool ans = true;
        if(sum == 1l){
            if(cnt[1])
                in[n[0].id] = 0;
            else if(cnt[2] > 1){
                int index = bs(2);
                in[n[index].id] = 0;
                if(index > 0 && n[index-1].val == 2)
                    in[n[index-1].id] = 0;
                else in[n[index+1].id] = 0;
            }
            else ans = false;
        }
        else {
            if(cnt[2])
                in[n[bs(2)].id] = 0;
            else if(cnt[1] > 1){
                in[n[0].id] = 0;
                in[n[1].id] = 0;
            }
            else ans = false;
        }
        if(ans)out();
        else printf("-1\n");
    }
    return 0;
}