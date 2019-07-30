#include <cstdio>
typedef long long ll;

ll n;

int main(){
	scanf("%I64d", &n);
	if(n == 0){
		printf("0\n");
		return 0;
	}
	n += 1;
	if(n % 2 == 0)
		n /= 2;
	printf("%I64d\n", n);
	return 0;
}