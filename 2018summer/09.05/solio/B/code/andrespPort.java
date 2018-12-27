// Port of Andre's solution to Java (Eduardo Marques)
// This one uses buffered I/O
import java.util.*;
import java.io.*;

class Coord implements Comparable<Coord> {
  int x, y; 
  Coord() { this(0,0); } ; 
  Coord(int x, int y) { this.x = x; this.y = y;}
  @Override
  public int compareTo(Coord o) {
    return - (x * o.y - y*o.x);
  }
}

public class andrespPort {
  public static void main(String[] args) { new andrespPort(); }
  
  andrespPort() {
    ArrayList<Coord> input = read();
    Coord solution = solve(input);
    assert doubleCheck(input, solution);
    System.out.println(solution.x + " " + solution.y); 
  }
  
  Coord solve(ArrayList<Coord> points) {
    TreeMap<Coord, Coord > events = new TreeMap<>();
    
    // Add events on the borders to guarantee that we consider them.
    events.put(new Coord(0, 1), new Coord());
    events.put(new Coord(-1, 0), new Coord());
    
    int superior = 0;  // Number of Coords in Q1 quadrant.
    int same = 0;      // Number of Coords in origin.
    int active = 0;    // Number of current Coords in Q2 and Q4 quadrant better
                       // than origin.
    
    int best_pos = points.size();
    int worst_pos = 0;
    
    for (Coord p : points) {
      if (p.x < 0 && p.y < 0) {}
      else if (p.x > 0 && p.y > 0) superior++;
      else if (p.x == 0 && p.y == 0) same++;
      else if (p.x <= 0 && p.y >= 0) {
        // events[Point(p.x, p.y)].first++;
        Coord e = events.get(p);
        if (e == null) { e = new Coord(); events.put(p, e); }
        e.x ++;

      }
      else if (p.x >= 0 && p.y <= 0) {
        active++;
        // events[Point(-p.x, -p.y)].second++;
        p = new Coord(- p.x, - p.y);
        Coord e = events.get(p);
        if (e == null) { e = new Coord(); events.put(p, e); }
        e.y ++;
      }
      else throw new Error("Bug!");
    }
    
    for (Coord p : events.values()) {
      // int tie_best_pos = superior + active - e.second.second;
      // int tie_worst_pos = superior + active + e.second.first + same;
      // active += e.second.first - e.second.second;
      int tie_best_pos = superior + active - p.y;
      int tie_worst_pos = superior + active + p.x + same;
      active += p.x - p.y;
      best_pos = Math.min(best_pos, tie_best_pos);
      worst_pos = Math.max(worst_pos, tie_worst_pos);
    }  
    return new Coord(best_pos + 1, worst_pos + 1);
  }

  boolean doubleCheck(ArrayList<Coord> input, Coord sol) {
      for (Coord p : input) {
        int tmp = p.x; p.x = p.y; p.y = tmp;
      }
      Coord sol2 = solve(input); 
      return sol.x == sol2.x && sol.y == sol2.y;
  }
  
  BufferedReader input;
  Coord readPoint() throws IOException {
    StringTokenizer tok = new StringTokenizer(input.readLine(), " ");
    return new Coord(Integer.parseInt(tok.nextToken()),
                     Integer.parseInt(tok.nextToken()));
  }
  ArrayList<Coord> read() {
    try {
      input = new BufferedReader(new InputStreamReader(System.in));
      int n = Integer.parseInt(input.readLine()) - 1;
      Coord maria = readPoint();
      ArrayList<Coord> points = new ArrayList<>();
      for (int i=0; i < n; i++) {
        Coord p = readPoint();
        p.x -= maria.x;
        p.y -= maria.y;
        points.add(p);
      }
      input.close();
      return points;
    } 
    catch(IOException e) {
      throw new Error(e);
    }
  }
}
