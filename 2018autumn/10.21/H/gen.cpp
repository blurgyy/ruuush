#include <bits/stdc++.h>
using namespace std;
const char *vow = "aeiou";
const char *nvow = "bcdfghjklmnpqrstvwxyz";

int vowlen = strlen(vow);
int nvowlen = strlen(nvow);

void vowel(){
    printf("%c", vow[rand()%vowlen]);
}

void nvowel(){
    printf("%c", nvow[rand()%nvowlen]);
}

int main(){
    srand(time(NULL));
    //int T = rand() % 10 + 1;
    int T = 3;
    printf("%d\n", T);
    while(T --){
        int len = rand() % 1000000 + 10;
        for(int i = 0; i < len; ++ i){
            if(rand() % 3){
                if(rand() % 3)
                    vowel();
                else
                    nvowel();
            }
            else 
                printf("?");
        }
        printf(" %d %d\n\n", rand() % 5 + 1, rand() % 3 + 1);
    }

    return 0;
}