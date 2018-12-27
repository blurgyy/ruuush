// Bribing Eve solution - Eduardo Marques
import java.util.*;
import java.io.*;

class Value { 
  int q2, q4; 
  Value(int q2, int q4) { this.q2 = q2; this.q4 = q4; }
  public String toString() { return String.format("[%3d,%3d]", q2, q4); }
}

class Point implements Comparable<Point> {
  int x, y;
  Point(int x, int y) {
    this.x = x; this.y = y;
  }
  @Override
  public int compareTo(Point o) {
    return  (x * o.y - y * o.x);
  }
  @Override
  public String toString() { return String.format("(%3d,%3d)", x,y); }
}

public class edrdo {
  public static void main(String[] args) throws IOException { new edrdo(); }

  TreeMap<Point,Value> sweep = new TreeMap<>();
  BufferedReader 
    input = new BufferedReader(new InputStreamReader(System.in));

  edrdo() throws IOException {
    int N  = Integer.parseInt(input.readLine());
    Point maria = readPoint(); 
    int    q1 = 0, q2 = 0, q3 = 0, q4 = 0, tie = 0;
    for (int i=1; i < N; i++) {
      Point p = readPoint();
      int x = p.x - maria.x;
      int y = p.y - maria.y;
      if (x == 0 && y == 0) tie ++;
      else {
        int g = agcd(x,y); x /= g; y /= g;
        if (x > 0 && y > 0) q1++;
        else if (x < 0 && y < 0) q3++; // not used, but useful for debugging
        else if (x < 0 || (x== 0 && y >= 0)) { 
           q2 ++; v(-x, y).q2 ++;
           assert debug("q2 %s", v(-x,y));
        } 
        else {
           q4++; v(x, -y).q4 ++;
           assert debug("q4 %s", v(x,-y));
        }
      }
    }
    input.close();
    assert debug("q1=%d q2=%d q3=%d q4=%d tie=%d", q1, q2, q3, q4, tie);
    assert debug(sweep);
    int better = q4;
    int best = q2 + q4, worst = 0;
    assert debug(sweep);
    for (Value v : sweep.values()) {
      int b = better - v.q4; 
      int w = better + v.q2; 
      better += (v.q2 - v.q4);
      best = Math.min(b, best);
      worst = Math.max(w, worst);
    }
    best += 1 + q1;
    worst += 1 + q1 + tie;
    System.out.println(best + " " + worst);
  }
  Value v(int x, int y) {
    Point key = new Point(x,y);
    Value value = sweep.get(key);
    if (value == null) {
      sweep.put(key, value = new Value(0,0));
    }
    return value;
  }
  Point readPoint() throws IOException {
    StringTokenizer tok = new StringTokenizer(input.readLine(), " ");
    return new Point(Integer.parseInt(tok.nextToken()), 
                     Integer.parseInt(tok.nextToken())); 
  }
  static int agcd(int a, int b) { 
    while (b != 0) { int tmp = b; b = a % b; a = tmp; }
    return Math.abs(a); 
  }
  // Debugging
  static boolean debug(Object o) { 
    return debug("%s %s", o.getClass().getSimpleName(), o.toString()); 
  }
  static boolean debug(String fmt, Object... args) { 
    System.err.printf(fmt, args); 
    System.err.println();
    return true;
  }
}
