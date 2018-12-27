#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int T, x, y;
int len;
char s[maxn];
int rec[maxn], vrec[maxn], nrec[maxn];
int tot, vtot, ntot;
bitset<maxn> d, vow[2], nvow[2];

bool vowel(char ch){
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

void init(){
    tot = vtot = ntot = 0;
    len = strlen(s);
    for(int i = 0; i < len; ++ i){
        if(vowel(s[i])){
            s[i] = 'a';
        }
        else if(s[i] == '?'){
            rec[tot++] = i;
            continue;
        }
        else {
            s[i] = 'b';
        }
    }
    vow[0].reset();
    vow[1].reset();
    nvow[0].reset();
    nvow[1].reset();
    d.reset();
    for(int i = 0; i < x; ++ i){
        vow[0].set(i);
    }
    for(int i = 0; i < y; ++ i){
        nvow[1].set(i);
    }
}

int lbound(int arr[], int e, int left, int right){
    if(left >= right)return right;
    int mid = (left + right) / 2;
    if(e <= arr[mid])return lbound(arr, e, left, mid);
    return lbound(arr, e, mid + 1, right);
}

int ubound(int arr[], int e, int left, int right){
    if(left >= right)return right;
    int mid = (left + right + 1) / 2;
    if(e >= arr[mid])return ubound(arr, e, mid, right);
    return  ubound(arr, e, left, mid - 1);
}

bool exist(int arr[], int arr_size, int e){
    return arr[lbound(arr,e,0,arr_size-1)] == e;
}

bool count(int left, int right){
    return lbound(rec, left, 0, tot-1) == ubound(rec, right, 0, tot - 1);
}

int main(){
    int a[5] = {1,3,5,7,9};
    //printf("%d %d\n", ubound(a,6,0,4), lbound(a,4,0,4));
    scanf("%d", &T);
    int Case = 0;
    while(T --){
        printf("Case #%d: ", ++ Case);
        bool like = true;
        bool surprise = false;
        scanf("%s%d%d", s, &x, &y);
        init();
        //printf("%s\n", s);


        bool t0 = false;
        d.reset();
        for(int i = 0; i < len; ++ i){
            int idx = (s[i] == 'a' ? 0 : 1);
            d <<= 1;
            d.set(0);
            d &= vow[idx];
            if(d[x-1]){
                t0 = true;
                //printf("vowlen = %d, dislike(%d)\n", x, i-x+1);
            }
        }
        if(t0){
            printf("DISLIKE\n");
            continue;
        }

        t0 = false;
        d.reset();
        for(int i = 0; i < len; ++ i){
            int idx = (s[i] == 'b' ? 1 : 0);
            d <<= 1;
            d.set(0);
            d &= nvow[idx];
            if(d[y-1]){
                t0 = true;
                //printf("nvowlen = %d, dislike(%d)\n", y, i-y+1);
            }
        }
        if(t0){
            printf("DISLIKE\n");
            continue;
        }

        bool t1 = false, t2 = false;
        /**/
        for(int i = 0; i < tot; ++ i){
            vow[0].set(rec[i]);
        }
        d.reset();
        for(int i = 0; i < len; ++ i){
            int idx = ((s[i] == '?' || s[i] == 'a') ? 0 : 1);
            d <<= 1;
            d.set(0);
            d &= vow[idx];
            if(d[x-1]){
                vrec[vtot++] = i-x+1;
                t1 = true;
                //printf("dislike(%d)\n", i-x+1);
            }
        }
        /**/
        for(int i = 0; i < tot; ++ i){
            nvow[1].set(rec[i]);
        }
        d.reset();
        for(int i = 0; i < len; ++ i){
            int idx = ((s[i] == 'b' || s[i] == '?') ? 1 : 0);
            d <<= 1;
            d.set(0);
            d &= nvow[idx];
            if(d[y-1]){
                nrec[ntot++] = i-y+1;
                t2 = true;
                //printf("dislike(%d)\n", i-y+1);
            }
        }
        /**/
        //for(int i = 0; i < vtot; ++ i){
        //    printf("vrec[%d] = %d\n", i, vrec[i]);
        //}
        //for(int i = 0; i < ntot; ++ i){
        //    printf("nrec[%d] = %d\n", i, nrec[i]);
        //}

        bool dislike = false;
        for(int i = 0; i < vtot; ++ i){
            int vl = vrec[i], vr = vrec[i] + x - 1;
            if(exist(nrec,ntot,vr)){
                int pos = lbound(nrec, vr, 0, ntot-1);
                int nr = nrec[pos] + y - 1;
                //printf("checking(%d, %d)\n", vl, nr);
                if(count(vl, nr)){
                    dislike = true;
                }
            }
        }
        for(int i = 0; i < ntot; ++ i){
            int nl = nrec[i], nr = nrec[i] + y - 1;
            if(exist(vrec, vtot, nr)){
                int pos = lbound(vrec, nr, 0, vtot - 1);
                int vr = vrec[pos] + x - 1;
                //printf("checking(%d, %d)\n", nl, vr);
                if(count(nl, vr)){
                    dislike = true;
                }
            }
        }
        if(dislike){
            printf("DISLIKE\n");
            continue;
        }

        //printf("%d %d\n", t1, t2);
        /*if(t1 && t2){
            printf("DISLIKE\n");
        }
        else */
        if(t1 == false && t2 == false){
            printf("LIKE\n");
        }
        else {
            printf("SURPRISE\n");
        }
    }
    return 0;
}

/**

500

jzouih?vwliqoaicie??io?biztabkiapjhhivzocqjzg??kolvxzgi?nb?b?uuysrat?n?x 4 7

ut?ii?gne?z 3 3
//dislike

happybirthda? 3 4

happybirth?ay 3 5

happydirthd?y 3 5

hellow?rld 3 5

helllllowooorld 3 5

*/