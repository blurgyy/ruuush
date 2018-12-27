#include<cstdio>

int main()
{
    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 60; j++)
            printf("%02d:%02d\n", i, j);
    }
    return 0;
}
