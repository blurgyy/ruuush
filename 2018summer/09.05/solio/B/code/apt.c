//  Author: Ana Paula Tomas
//  October 2016
//-------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define ABOVE 0
#define BELOW 1
#define EQUAL 2

#define MAXN 100000

typedef struct {
  int num, den;
} FRAC;

typedef struct {
  char state; 
  FRAC point;
} EVENT;

#define STATE(X) ((X).state)
#define POINT(X) ((X).point)
#define NUM(X) ((X).num)
#define DEN(X) ((X).den)

int compare(FRAC,FRAC);

EVENT Points[MAXN];
int NPoints;

EVENT evento(int x,int y,int x1,int y1,char state){
  EVENT e;  
  e.point.num = y1-y;
  e.point.den = x-y-(x1-y1);   // (x-x1)+(y1-y)
  if (e.point.den < 0) {
    e.point.num = -e.point.num;
    e.point.den= -e.point.den;
  }
  STATE(e) = state;
  return e;
}

int cmpfunc (const void * a, const void * b)
{
  return compare(POINT(*(EVENT *)a), POINT(*(EVENT *)b));
}

int main()
{
  int x1, y1, x, y, n, i, below, above, aux,  tmp_equal0 = 0, eps_above = 0;

  int defPos[3] = {0}, tmpPos[2] = {0}, worst, bsf;
  FRAC f;

  scanf("%d",&n);

  scanf("%d%d",&x1,&y1);  // maria
  NPoints = 0;
  for(i=1; i < n; i++) {
    scanf("%d%d",&x,&y); 
    f.num = y1-y;
    f.den = x-y-(x1-y1);   // (x-x1)+(y1-y)
    if (f.den == 0) {
      if (y==y1) defPos[EQUAL]++;
      else if (y > y1) defPos[ABOVE]++;
      // else defPos[BELOW]++;
    } else {
      if (f.den < 0) {
	f.den = -f.den;
	f.num = -f.num;
      }
      if (f.num < 0 || f.num > f.den) {
	// sem interseccao
        if (y > y1) defPos[ABOVE]++;
	// else defPos[BELOW]++
      } else if (f.num == 0) {
	// y == y1   and x1 != x
        tmp_equal0++; // intersect at 0
	if (x > x1) {
	  eps_above++;
          defPos[ABOVE]++;
	}
	// else defPos[BELOW]++;
      } else {
	if (y > y1) {
	  tmpPos[ABOVE]++;
	  Points[NPoints++] = evento(x,y,x1,y1,0); // above
	} else {  // y < y1
	  tmpPos[BELOW]++;
	  Points[NPoints++] = evento(x,y,x1,y1,1); // below
	}
      }
    }
  }

  worst = (defPos[ABOVE]-eps_above)+tmp_equal0+defPos[EQUAL]+tmpPos[ABOVE]+1;
  bsf = (defPos[ABOVE]-eps_above)+tmpPos[ABOVE]+1;

  if (NPoints) {
    qsort(Points,NPoints,sizeof(EVENT),cmpfunc);
    
    i = 0;
    while(i<NPoints) {
      below = 0; above = 0;
      if (STATE(Points[i]) == 1) {
	tmpPos[BELOW]--; below++;
      }
      else {
	tmpPos[ABOVE]--; above++;
      }

      while(++i < NPoints && compare(POINT(Points[i]),POINT(Points[i-1]))== 0) {
	if (STATE(Points[i]) == 1) {
	  tmpPos[BELOW]--; below++;
	}
	else {
	  tmpPos[ABOVE]--; above++;
	}
      }

    
      aux = defPos[ABOVE]+defPos[EQUAL]+tmpPos[ABOVE]+below+above+1;
      if (aux > worst) worst = aux;
      aux = defPos[ABOVE]+tmpPos[ABOVE]+1;
      if (aux < bsf) bsf = aux;

      defPos[ABOVE] += below;
      // defPos[BELOW] += above;
    }
  }

  printf("%d %d\n",bsf,worst);
    
  return 0;
}

// returns negative number if x < y, positive if x > y, 0 otherwise.
int compare(FRAC x,FRAC y)
{
  return NUM(x)*DEN(y)-NUM(y)*DEN(x); 
}

