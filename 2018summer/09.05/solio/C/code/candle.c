//  Author: Sergio Crisostomo
//  November 2016
//-------------------------------------------------

#include <stdio.h>

#define RSTART 4
#define TSTART 3

int main(){
	int d, Rsum, Tsum, Rbox, Tbox, Ra, Ta;

	scanf("%d", &d);
	scanf("%d", &Rbox);
	scanf("%d", &Tbox);
	
	Rsum=0;
	Tsum=0;
	Ra = RSTART;
	Ta = TSTART;

	while(Rsum + Tsum < Rbox + Tbox){
		Rsum += Ra;
		Ra++;
		if(Ra >= TSTART + d){
			Tsum += Ta;
			Ta++;
		}
	}
	printf("%d\n", Rbox-Rsum);
	return 0;
}

