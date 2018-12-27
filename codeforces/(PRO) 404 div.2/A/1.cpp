#include<stdio.h>
#include<string.h>
#include<algorithm>
int main()
{
    char cmp[6][20] = {{0}, "Tetrahedron", "Cube", "Octahedron", "Dodecahedron", "Icosahedron"};
    int n;
    while(~scanf("%d", &n))
    {
        int ans = 0;
        while(n--)
        {
            char s[20];
            scanf("%s", s);
            if(!strcmp(s, cmp[1]))ans += 4;
            if(!strcmp(s, cmp[2]))ans += 6;
            if(!strcmp(s, cmp[3]))ans += 8;
            if(!strcmp(s, cmp[4]))ans += 12;
            if(!strcmp(s, cmp[5]))ans += 20;
        }
        printf("%d\n", ans);
    }
    return 0;
}
