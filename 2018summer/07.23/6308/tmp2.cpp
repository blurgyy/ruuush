#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("in.in", "r", stdin);
	freopen("in2.in", "w", stdout);

	int x, a, b;
	double c;
	scanf("%d", &x);
	printf("%d\n", x);
	while(~scanf("%d%d UTC+%lf", &a, &b, &c)){
		cout << a << ' ' << b << " UTC-" << c << endl;
		//printf("%d %d UTC-%g\n", a, b, c);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}