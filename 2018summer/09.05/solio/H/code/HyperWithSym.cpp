
// HyperWithSymp solution - Eduardo Marques
// Port from Java code
#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdint>

using namespace std;
typedef vector<int64_t> Coord;

// hash function (a so-called "functor")
struct HashFunc {
   size_t operator()(const Coord& c) const {
      size_t h = 17;
      for(auto v : c) {
          h += 31 * h + v;
      }
      return h;
   }
};
typedef unordered_map<Coord,int64_t,HashFunc> Memory;
typedef set<int64_t> NumberSet;

class HyperWithSym {
public:
  HyperWithSym(int n, int h) 
    : N(n), H(h), mem(50, HashFunc()) {
  }

  void solve() {
    Coord zero(N);
    mem[zero] = 1;
    current = zero;
    go(0, 0, H);
  }
  void printBase() {
    for (int64_t v : base) {
      cout << v << '\n';
    }
  }

private:
  int N, H;
  Memory mem;
  NumberSet base;
  Coord current; 


  void go(int pos, int min, int max) {
    if (min <= max) {
      if (pos == N-1) {
        current[pos] = max;
        base.insert( pascal(current) );
      } else {
        for (int i = min; i <= max; i++) {
          current[pos]  = i;
          go(pos + 1, i, max - i);
        }
      }
    }
  }

  int64_t pascal(const Coord& c) {
     int64_t r = mem[c]; 
     if (r == 0) {
       for (auto i = 0; i < c.size(); i++) { 
         if (c[i] != 0) {
           Coord c2 = c;
           c2[i]--; 
           // lazy programmer :) ins. sort for c2[i] better but N will be low :)  
           sort(c2.begin(), c2.end()); 
           r += pascal(c2); 
         }
       }
       mem[c] = r;
     }
     return r;
  }
};
int main(int argc, char** argv) {
  int N, H;
  cin >> N >> H;
  H--;
  HyperWithSym solver(N,H);
  solver.solve();
  solver.printBase();
  return 0;
}
