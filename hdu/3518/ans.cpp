#include <cstring>  
#include <algorithm>  
#include <cstdio>  
#include <iostream>  
#define MAX 1007  
  
using namespace std;  
  
char s[MAX];  
int r[MAX],sa[MAX],wa[MAX],wb[MAX],wv[MAX],wss[MAX],rk[MAX],height[MAX];  
  
int cmp ( int *r , int a , int b , int len )  
{  
    return r[a]==r[b]&&r[a+len]==r[b+len];  
}  
  
void da ( int* r , int* sa , int n , int m )  
{  
    int i,j,p, *x = wa , *y = wb , *t;  
    for ( i = 0 ; i < m ; i++ ) wss[i] = 0;  
    for ( i = 0 ; i < n ; i++ ) wss[x[i] = r[i]]++;  
    for ( i = 0 ; i < m ; i++ ) wss[i] += wss[i-1];  
    for ( i = n-1 ; i >= 0 ; i-- ) sa[--wss[x[i]]] = i;  
  
    for ( j = 1 , p = 1 ; p < n ; j *= 2 , m = p )  
    {  
        for ( p = 0 , i = n - j ; i < n ; i++ ) y[p++] = i;  
        for ( i = 0 ; i < n ; i++ ) if ( sa[i] >= j ) y[p++] = sa[i]-j;  
        for ( i = 0 ; i < n ; i++ ) wv[i] = x[y[i]];  
        for ( i = 0 ; i < m ; i++ ) wss[i] = 0;  
        for ( i = 0 ; i < n ; i++ ) wss[wv[i]]++;  
        for ( i = 0 ; i < m ; i++ ) wss[i] += wss[i-1];  
        for ( i = n-1 ; i >= 0 ; i-- ) sa[--wss[wv[i]]] = y[i];  
        for ( t = x , x = y , y = t , p = 1 , x[sa[0]] = 0 , i = 1 ; i < n ; i++ )  
            x[sa[i]] = cmp ( y , sa[i-1] , sa[i] , j ) ? p-1 : p++;  
    }  
}  
  
void calheight ( int *r , int *sa , int n )  
{  
    int i , j , k = 0;  
    for ( i = 1 ; i <= n ; i++ ) rk[sa[i]] = i;  
    for ( i = 0 ; i < n ; height[rk[i++]] = k )   
        for ( k?k--:0, j = sa[rk[i]-1] ; r[i+k] == r[j+k] ; k++ );  
}  
  
int main ( )  
{  
    while ( scanf ( "%s" , s ) )  
    {  
        if ( s[0] == '#' ) break;  
        int len = strlen ( s );  
        for ( int i = 0 ; i < len ; i++ ) r[i] = s[i] -'a' + 1;  
        r[len] = 0;  
        da ( r , sa , len+1 , 27 );  
        calheight ( r , sa , len );  
        int ans = 0;  
        for ( int i = 1 ; i <= (len+1)/2 ; i++ )  
        {  
            int maxn = -1 , minn = MAX;  
            for ( int j = 2 ; j <= len ; j++ )  
            {  
                if ( height[j] >= i )  
                {  
                    int temp = max ( sa[j] , sa[j-1] );  
                    maxn = max ( temp , maxn );  
                    temp = min ( sa[j] , sa[j-1] );  
                    minn = min ( temp , minn );  
                }  
                else   
                {  
                    if ( maxn - minn >= i ) ans++;  
                    minn = MAX , maxn = -1;  
                }  
            }  
            if ( maxn - minn >= i ) ans++;  
        }  
        printf ( "%d\n" , ans );  
    }  
}  