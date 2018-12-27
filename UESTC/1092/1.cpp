#include <bits/stdc++.h>
//#include <cstdio>
//#include <cstring>
//#include <set>
//#include <algorithm>
using namespace std;

unordered_set<string> g;

string a;

int main(){
	int time = 20000;
	while(time--){
		cin >> a;
		g.insert(a);
	}
	printf("%d\n", g.size());
	return 0;
}