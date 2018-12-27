#include <bits/stdc++.h>
using namespace std;
const double LOG = (log(10)/log(2));

double m;
int Case = 0;

int main(){
	while(~scanf("%lf", &m)){
		printf("Case #%d: %d\n", ++ Case, (int)(m/LOG));
	}
	return 0;
}