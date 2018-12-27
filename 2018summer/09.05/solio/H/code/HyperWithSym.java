import java.util.*;

// Hyper piramids solution - Eduardo Marques
// "Smart" solution: factors in symmetry
public class HyperWithSym {
  int N, H;
  TreeMap<Coord,Long> mem = new TreeMap<>(); 
  TreeSet<Long> base = new TreeSet<>();
  int[] current; 

  HyperWithSym() {
    Scanner inp = new Scanner(System.in);
    N = inp.nextInt();
    H = inp.nextInt() - 1;
    inp.close();
    mem.put(new Coord(new int[N]), 1L); // (0, 0, ..., 0) -> 1
    current = new int[N];
    go(0, 0, H);
    for (long v : base) {
      System.out.println(v);
    }
    assert keysInMemoAreWellFormed();
  }

  void go(int pos, int min, int max) {
    if (min <= max) {
      if (pos == N-1) {
        current[pos] = max;
        assert isOrdered(current);
        base.add( pascal(current.clone()) );
      } else {
        for (int i = min; i <= max; i++) {
          current[pos]  = i;
          go(pos + 1, i, max - i);
        }
      }
    }
  }

  long pascal(int[] v) {
     // A Coord instance is just a wrapper for an array (see def. below)
     // hashCode + equals are not usable directly together w/the memoization map
     Coord c = new Coord(v);
     Long opt_r = mem.get(c);     
     if (opt_r == null) {
	 long r = 0L;
	 for (int i=0; i < v.length; i++) {  
         if (v[i] > 0) {
           int[] v2 = v.clone();
           v2[i]--; 
           // lazy programmer :) ins. sort for c2[i] better but N will be low :)
           Arrays.sort(v2); 
           r += pascal(v2); 
         }
	 }
	 mem.put(c, r);
	 return r;
     } 
     else {
	 return (long) opt_r;
     }
  }


  static class Coord implements Comparable<Coord> {
    int[] values;
    int h;

    Coord(int[] v) { values = v; h = 0; } 

    @Override
    public boolean equals(Object o) { 
      return Arrays.equals(values, ((Coord) o).values);
    }

    @Override
    public int hashCode() {
      return h == 0 ? (h = Arrays.hashCode(values)) : h;
    }

    public int compareTo(Coord other) {
	if (this.values.length == other.values.length) {
	    for (int i=0; i<this.values.length; i++) {
		if (this.values[i] != other.values[i])
		    return this.values[i] - other.values[i];
	    }
	    return 0;
	} else {
	    throw new IllegalArgumentException();
	}	   
    }
  }
 




  public static void main(String[] args) { 
    new HyperWithSym(); 
  }
  // FOR DEBUGGING
  public boolean isOrdered(int[] v) {
    for (int i=1; i < v.length; i++) 
      assert v[i] >= v[i-1]
        : Arrays.toString(v) + " not well formed - pos: " + i;
    return true;
  }
  public boolean keysInMemoAreWellFormed() {
    for (Coord c : mem.keySet()) {
      assert isOrdered(c.values);
    }
    return true;
  }
}
