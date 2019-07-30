#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

char s[maxn];
int r[2][3][maxn];

void init(){
    memset(r, 0x3f, sizeof(r));
}

int main(){
    while(~scanf("%s", s+1)){
        init();
        int len = strlen(s+1);
        for(int i = 1; i <= len; ++ i){
            for(int j = i-1; j >= 0 && r[0][s[i]-'a'][j] == inf; -- j){
                r[0][s[i]-'a'][j] = i;
            }
        }
        for(int i = len; i; -- i){
            for(int j = i+1; j <= len+1 && r[1][s[i]-'a'][j] == inf; ++ j){
                r[1][s[i]-'a'][j] = i;
            }
        }
        // for(int i = 0; i <= len+1; ++ i){
        //     printf("%d%c", r[1][0][i], " \n"[i==len+1]);
        // }
        int front = 0, rear = len+1;
        string ans;
        string s1, s2;
        while(true){
            int dist_a = max(abs(r[0][0][front] - front), abs(r[1][0][rear] - rear));
            int dist_b = max(abs(r[0][1][front] - front), abs(r[1][1][rear] - rear));
            int dist_c = max(abs(r[0][2][front] - front), abs(r[1][2][rear] - rear));
            // printf("dist_a = %d\n", dist_a);
            // printf("dist_b = %d\n", dist_b);
            // printf("dist_c = %d\n", dist_c);
            char id = '*';
            if(dist_a <= dist_b && dist_a <= dist_c){
                id = 'a';
            }
            else if(dist_b <= dist_a && dist_b <= dist_c){
                id = 'b';
            }
            else if(dist_c <= dist_a && dist_c <= dist_b){
                id = 'c';
            }
            else {
                id = '~';
                printf("wtf~\n");
                exit(-1);
            }
            front = r[0][id-'a'][front];
            rear = r[1][id-'a'][rear];
            if(front > rear){
                s1 = ans.substr(0, ans.length()/2);
                s2 = ans.substr(ans.length()/2, ans.length()/2);
                reverse(s1.begin(), s1.end());
                reverse(s2.begin(), s2.end());
                break;
            }
            if(front == rear){
                s1 = ans.substr(0, ans.length()/2);
                s2 = ans.substr(ans.length()/2, ans.length()/2);
                reverse(s1.begin(), s1.end());
                s1 += s[front];
                reverse(s2.begin(), s2.end());
                break;
            }
            if(front < rear){
                ans = s[front] + ans;
                ans = ans + s[rear];
            }
        }
        int lenans = s1.length() + s2.length();
        if(lenans < len / 2){
            printf("IMPOSSIBLE\n");
        }
        // reverse(ans, ans+lenans/2);
        // reverse(ans+(lenans+1)/2, ans + lenans);
        // cout << ans << endl;
        cout << s1 << s2 << endl;
    }
    return 0;
}
