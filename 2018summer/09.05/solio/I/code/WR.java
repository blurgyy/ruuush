//
// White Rabbit solution
// by Eduardo Marques
//
import java.util.*;
import java.util.function.Consumer;
import java.io.*;

public class WR {
  // Lifecycle
  public static void main(String[] args) {
    new WR();
  }
  WR() {
    readInput();
    solveEquations();
    assert ensureTripConstraintsWereMet();
    System.out.println(shortestPath());
  }
  // Global parameters
  int N, A, R, C, T; 

  // Mapping of edges to variables in the equation system
  Map<Integer,Integer> edgeToVar = new HashMap<>();
  int edgeVar(int a, int b) {
    if (a > b) { int tmp = a; a = b; b = tmp; }
    int h = (a << 8) | b;
    Integer label = edgeToVar.get(h); 
    if (label == null) edgeToVar.put(h, label = edgeToVar.size());
    return label;
  }
  // GF(13) arithmetic
  static int add(int a, int b) { return (a + b ) % 13; }
  static int sub(int a, int b) { return (a - b + 13) % 13; }
  static int mul(int a, int b) { return (a * b ) % 13; }
  static int div(int a, int b) { return mul(a, inv(b)); }
  static final int INV[] = {-1, 1, 7, 9, 10, 8, 11, 2, 5, 3, 4, 6, 12 };
  static int inv(int n) {
    assert n != 0 : "n cannot be 0";
    assert mul(n,INV[n]) == 1 : "inv wrong for " + n;
    return INV[n];
  }

  // Equation solver (usual Gauss elimination + backward substitution)
  int[][] matrix; // matrix used by equation solver
  int[] travelTime; // travel times per edge (solution)

  void solveEquations() {
    // Gaussian elimination first
    for (int var = 0; var < C; var++) {
      // Find pivot , any != 0 will do; numerical instability is not an issue
      int rPivot = -1;
      for (int r = var; r < T; r++) {
         if (matrix[r][var] != 0) {
           rPivot = r;
           break;
         }
      } 
      assert printMatrix("Pivot step " + var + " r " + rPivot);
      assert rPivot != -1 : "Singular matrix - step " + var;

      // Swap matrix[var] and matrix[rPivot] (just reference copy)
      if (rPivot != var) {
        int[] tmp = matrix[rPivot];
        matrix[rPivot] = matrix[var];
        matrix[var] = tmp;
        assert printMatrix("Swapped " + var + " " + rPivot);
      }
      int inv = inv(matrix[var][var]);

      // Elimination step
      for (int r = var + 1; r < T; r++) {
        int f = mul(matrix[r][var], inv);
        for (int c = var + 1 ; c <= C; c++) {
          matrix[r][c] = sub(matrix[r][c], mul(matrix[var][c], f));
        }
        matrix[r][var] = 0;
      }
    }
    assert printMatrix("Echelon form");

    // Backward substitution now
    travelTime = new int[C];
    for (int var = C-1; var >= 0; var--) {
      int v = div(matrix[var][C], matrix[var][var]);
      travelTime[var] = matrix[var][C] = v;
      assert v >= 1 && v <= 12 :
         "wrong travel time for var " + var + " : " + v;
      matrix[var][var] = 1;
      for (int r = 0; r < var; r++) {
        matrix[r][C] = sub(matrix[r][C], mul(matrix[r][var], v));
        matrix[r][var] = 0;
      }
      assert printMatrix("Backward substituion step");
    }
    assert printMatrix("After solving");
  }
  // Graph representation
  BitSet[] adjMatrix; // 200 nodes (26 bytes per node) at most, 
                      // better than adjacency list
                      // iteration also cheaper (no Iterator objects etc)
  void addEdge(int a, int b) {
    adjMatrix[a].set(b);
    adjMatrix[b].set(a);
  } 

  void iterateNeib(int a, Consumer<Integer> action) {
    BitSet adj = adjMatrix[a];
    for (int b = adj.nextSetBit(0); b >= 0; b = adj.nextSetBit(b+1)) {
      action.accept(b);
    }
  }

  int shortestPath() {
    // Dijkstra's algorithm
    int[] dist = new int[N+1];
    BitSet seen = new BitSet(N+1);
    PriorityQueue<Integer> q 
       = new PriorityQueue<>(N, (a,b) -> dist[a] - dist[b]);
    Arrays.fill(dist, Integer.MAX_VALUE);
    dist[A] = 0;
    for (int i=1; i <= N; i++) q.offer(i);
    assert printSP("start", q, dist);
    while(q.peek() != R) {
      int a = q.poll();
      seen.set(a);
      iterateNeib(a, b -> {
        if (!seen.get(b)) { 
          int d = dist[a] + travelTime[edgeVar(a,b)]; 
          if (d < dist[b]) {
            // Rebalance priority queue
            q.remove(b);
            dist[b] = d;
            q.offer(b);
          }
        }
      });
      assert printSP("update "+ a , q, dist);
    }
    return dist[R];
  }

  // For double-check at the end (with -ea)
  int[][] trips;
  int[] times;
  
  BufferedReader in;
  StringTokenizer stok;

  void nextLine() { try { stok = new StringTokenizer(in.readLine(), " ");  } catch (IOException e) { throw new Error(e);} }
  int nextInt() { return Integer.parseInt( stok.nextToken() ); }

  void readInput() {
    // Note: two step init, C is not given beforehand 
    in = new BufferedReader(new InputStreamReader(System.in), 16384);
    nextLine();
    N = nextInt();
    A = nextInt();
    R = nextInt();
    T = nextInt();
    adjMatrix = new BitSet[N+1];
    for (int i=1; i<=N; i++) {
       adjMatrix[i] = new BitSet(N+1);
    }
    trips = new int[T][];
    times = new int[T];
    for (int i=0; i < T; i++) {
      nextLine();
      int time = nextInt(),
          plen = nextInt();
      int[] trip = trips[i] = new int[plen];
      times[i] = time;
      trip[0] = nextInt();
      for (int j=1; j < plen; j++) {
        trip[j] = nextInt();
        addEdge(trip[j-1], trip[j]);
        edgeVar(trip[j-1], trip[j]);
      }
    }
    C = edgeToVar.size();
    matrix = new int[T][C+1];
    for (int i = 0; i < T; i++) {
      int[] row = matrix[i];
      int[] trip = trips[i];
      for (int j=1; j < trip.length; j++) {
        int a = trip[j-1], b = trip[j], var = edgeVar(a,b);
        row[var] = add(row[var], 1);
      }
      row[C] = times[i];
    }
    assert printGraph();
    assert printMatrix("starting matrix");
  }
  // DEBUGGING
  boolean printMatrix(String label) {
    System.out.println(label);
    for (int[] row : matrix) {
      for (int v : row) {
        System.out.printf(" %2d", v); 
      }
      System.out.println();
    }
    return true;
  }
  boolean printGraph() {
    System.out.println("The graph");
    for (int a_ = 1; a_ <= N ; a_++) {
      final int a = a_;
      System.out.print(a + ":");
      iterateNeib(a, b -> {
        System.out.printf(" %d [%d]", b, edgeVar(a,b));
      });
      System.out.println();
    }
    return true;
  }
  boolean printTravelTimes() {
    System.out.println("Travel times");
    for (int a_ = 1; a_ <= N ; a_++) {
      final int a = a_;
      iterateNeib(a, b -> {
        if (a < b)
          System.out.printf("%d -> %d = %d\n", a, b, travelTime[edgeVar(a,b)]);
      });
    }
    return true;
  }
  boolean ensureTripConstraintsWereMet() {
    printTravelTimes();
    boolean success = true;
    System.out.println("Do they meet the constraints?");
    for (int t = 0; t < trips.length; t++) {
      int time = 0;
      for (int i = 1; i < trips[t].length; i++) {
        int a = trips[t][i-1], b = trips[t][i], v = edgeVar(a,b);
        time += travelTime[v];
      }
      time %= 13;
      if (time != times[t]) {
        System.out.printf("Wrong - trip %d - %d vs %d\n",
                          t, times[t], time);
        success = false;
      } else {
        System.out.printf("OK - trip %d\n", t);
      }
    }
    return success;
  }
  boolean printSP(String label, PriorityQueue q, int[] dist) {
    System.out.println("PQ - " + label);
    System.out.println(q.toString());
    System.out.println(Arrays.toString(dist));
    return true;
  }
}
