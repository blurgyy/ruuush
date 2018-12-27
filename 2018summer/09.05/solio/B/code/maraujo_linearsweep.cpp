#include <cstdio>
#include <vector>
#include <algorithm>

#define EPS 1e-6

using namespace std;

int n;
int m1, m2;
int mm;
int best, worst;

vector<pair<double, bool> > events;

int nabove = 0, nbelow = 0;

int main() {
  scanf("%d", &n);
  scanf("%d %d", &m1, &m2);
  mm = m1-m2;

  int x1, x2;
  for (int i = 0; i < n-1; i++) {
    scanf("%d %d", &x1, &x2);
    if (x2 > m2 || (x2 == m2 && x1 < m1)) nabove++;
    if (m2 > x2 || (m2 == x2 && m1 < x1)) nbelow++;
    int cm = x1-x2;
    if (cm != mm) {
      double x = (x2 == m2?0.0:double(x2-m2)/(mm - cm));
      //printf("%d\t%d\t%lf\t%d\t%d\t%d\t%d\t%d\n", x1, x2, x, (x1 == m1 ? x2 < m2 : x1 > m1), x2, m2, mm, cm);
      if (x >= 0.0-EPS && x <= 1.0+EPS)
	events.push_back(make_pair(x, (x1 == m1 ? x2 < m2 : x1 > m1))); // going up
    }
  }

  //printf("nabove = %d nbelow = %d\n", nabove, nbelow);
  best = nabove+1;
  worst = n-nbelow;
  
  sort(events.begin(), events.end());

  for (size_t i = 0; i < events.size(); i++) {
    int cntup = events[i].second;
    int cntdown = !events[i].second;
    
    while (i+1 < events.size() && events[i].first+EPS > events[i+1].first) {
      cntup += events[i+1].second;
      cntdown += !events[i+1].second;
      i++;
    }
    best = min(best, nabove + 1 - cntdown);
    worst = max(worst, n-nbelow + cntup);
   
    nabove = nabove + cntup - cntdown;
    nbelow = nbelow - cntup + cntdown;

    //printf("%lu %lf cntup: %d cntdown: %d nabove: %d nbelow: %d best: %d worst: %d\n", i, events[i].first, cntup, cntdown, nabove, nbelow, best, worst);
  } 

  printf("%d %d\n", best, worst);
  return 0;
}
