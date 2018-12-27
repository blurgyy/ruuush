#include<cstdio>
#include<iostream>
#include<map>
#include<string>

std::map<std::string, int> ans;
std::string color;
int n;

int main(){
    while(~scanf("%d", &n) && n){
        ans.clear();
        while(n--){
            std::cin >> color;
            ++ ans[color];
        }
        int cnt = 0;
        std::string final;
        for(std::map<std::string, int>::iterator iter = ans.begin(); iter != ans.end(); ++ iter)
            if((*iter).second > cnt){
                cnt = (*iter).second;
                final = (*iter).first;
            }
        std::cout << final << std::endl;
    }
    return 0;
}