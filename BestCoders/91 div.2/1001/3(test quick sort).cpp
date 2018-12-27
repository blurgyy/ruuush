#include<stdio.h>
void quicksort(int n[], int left, int right)
{
    int i = left, j = right, key = n[i];
    if(left >= right)return;
    while(i < j)
    {
        while(i < j && n[j] <= key)j--;
        n[i] = n[j];
        while(i < j && n[i] >= key)i++;
        n[j] = n[i];
    }
    n[i] = key;
    quicksort(n, left, i-1);
    quicksort(n, i+1, right);
}

int main()
{
    int n[i];
}
