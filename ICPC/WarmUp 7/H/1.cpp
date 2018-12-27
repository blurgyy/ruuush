#include<bits/stdc++.h>
using namespace std;

char in[5];
int n, idx[130];
vector<int> F[5], E[5];

void ID(){
    for(int i = '2'; i <= '9'; ++ i)
        idx[i] = i - '0';
    idx['X'] = 10;
    idx['J'] = 11;
    idx['Q'] = 12;
    idx['K'] = 13;
    idx['A'] = 1;
    idx['C'] = 1;
    idx['D'] = 2;
    idx['H'] = 3;
    idx['S'] = 4;
}

int main(){
    while(~scanf("%d", &n)){
        ID();
        for(int i = 1; i <= 4; ++ i)
            F[i].clear(), E[i].clear();
        while(n--){
            scanf("%s", in);
            printf("%d%d ", idx[in[0]], idx[in[1]]);
            F[idx[in[1]]].push_back(idx[in[0]]);
        }
        printf("\n");
        for(int i = 1; i <= 4; ++ i){
            int s1 = F[i].size();
            for(int j = 0; j < s1; ++ j){
                for(int k = 1; k <= 4; ++ k){
                    if(k == i)continue;
                    int s2 = F[k].size();
                    for(int l = 0; l < s2; ++ l){
                        if(F[i][j] == F[k][l])
                            E[i].push_back(k);
                    }
                }
            }
        }
        for(int i = 1; i <= 4; ++ i){
            sort(E[i].begin(), E[i].end());
            //E[i].erase(unique(E[i].begin(), E[i].end()), E[i].end());
        }
        for(int i = 1; i <= 4; ++ i){
            printf("%d: ", i);
            for(int j = 0; j < E[i].size(); ++ j)
                printf("%d ", E[i][j]);
            printf("\n");
        }
        for(int i = 1; i <= 4; ++ i){

        }
    }
    return 0;
}