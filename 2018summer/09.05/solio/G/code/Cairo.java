/*
  SWERC 2016 
  Problem G - Cairo Corridor
  solution using DFS + checking critical points
  @author: Pedro Vasconcelos
 */

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;


public class Cairo {
    static int N, M;
    static boolean tiling[][][];
    static boolean visited[][][];  

    /* border checks 
     */
    static boolean topBorder(Pos p) {
	if ((p.i+p.j)%2 ==0) 
	    return p.i == 0;
	else
	    return p.i == 0 && p.k==0;
    }

    static boolean bottomBorder(Pos p) {
	if ((p.i + p.j)%2 == 0) 
	    return (p.i == N-1);
	else
	    return (p.i == N-1 && p.k==1);
    }

    static boolean leftBorder(Pos p) {
	if ((p.i+p.j)%2 == 0) 
	    return (p.j==0 && p.k==0);
	else
	    return (p.j==0);
    }

    static boolean rightBorder(Pos p) {
	if ((p.i+p.j)%2==0)
	    return (p.j == M-1 && p.k==1);
	else
	    return (p.j == M-1);
    }


    static void addTile(List<Pos> lst, int i, int j, int k) {
	if(tiling[i][j][k]) 
	    lst.add(new Pos(i,j,k));
    }


    static List<Pos> adjacents(Pos p) {
	ArrayList<Pos> lst = new ArrayList<>(); 
	int i, j, k;
	i = p.i;
	j = p.j;
	k = p.k;
	
	if ((i+j) % 2 == 0) {
	    addTile(lst, i,j,1-k);
	    if(i+1<N) addTile(lst, i+1,j,0);
	    if(i>0) addTile(lst, i-1,j,1);
	    if (k==1) {
		if(j+1<M) { 
		    addTile(lst, i,j+1,0);
		    addTile(lst, i,j+1,1); 
		}
	    } else {
		if(j>0) { 
		    addTile(lst, i,j-1,0);
		    addTile(lst, i,j-1,1);
		}
	    }
	} else {
	    addTile(lst, i,j,1-k);
	    if(j+1<M) addTile(lst, i,j+1,0);
	    if(j>0) addTile(lst, i,j-1,1);
	    if(k==1) {
		if (i+1<N) { 
		    addTile(lst, i+1,j,0);
		    addTile(lst, i+1,j,1);
		}
	    } else {
		if (i>0) {
		    addTile(lst, i-1,j,0);
		    addTile(lst, i-1,j,1);
		}
	    }
	}
	
	return lst;
    }


    static int degree(Pos p) {
	return adjacents(p).size();
    }


    static List<Pos> dfs(Pos p) {
	// reset visited array
	for(int i=0; i<N; i++)
	    for(int j=0; j<M; j++)
		for(int k=0; k<=1; k++)
		    visited[i][j][k] = false;

	List<Pos> acc = new ArrayList<>();
	List<Pos> queue = new ArrayList<>();
	queue.add(p);
	dfs_worker(queue, acc);
	return acc;
    }

    static void dfs_worker(List<Pos> queue, List<Pos> acc) {
	if (queue.isEmpty()) 
	    return;

	Pos p = queue.remove(0);

	if (visited[p.i][p.j][p.k]) 
	    dfs_worker(queue, acc);
	else {
	    visited[p.i][p.j][p.k] = true;
	    acc.add(p);
	    dfs_worker(adjacents(p), acc);
	    dfs_worker(queue, acc);
	}
    }


    static boolean reachesBorders(List<Pos> scc) {
	boolean t=false, b=false, l=false, r=false;
	for (Pos p : scc) {
	    t |= topBorder(p);
	    b |= bottomBorder(p);
	    l |= leftBorder(p);
	    r |= rightBorder(p);
	}
	return (t && b && l && r);
    }

    /* check if a connected component is a corridor
     */
    static boolean checkCorridor(List<Pos> scc) {
	if (!reachesBorders(scc)) 
	    return false;

	// count leaves and position with degree >= 3
	int leaves = 0, degree3 = 0;
	// critical nodes
	List<Pos> critical = new ArrayList<>();

	for (Pos p : scc) {
	    int d = degree(p);
	    if (d==1) {
		leaves ++;
		if (!critical.contains(p))
		    critical.add(p);		
	    }
	    else if(d >=3) {
		degree3 ++;
		if (!critical.contains(p))
		    critical.add(p);
		for (Pos q : adjacents(p))
		    if (!critical.contains(q))
			critical.add(q);
	    }
	    if (leaves > 4 || degree3 > 6) 
		return false;
	}
	
	// check disconection of critical positions
	for(Pos p : critical) {
	    if (!checkDisconnection(p)) 
		return false;
	}
	return true;
    }

    static boolean checkDisconnection(Pos p) {
	tiling[p.i][p.j][p.k] = false;
	Pos q = adjacents(p).get(0); // must be non-empty
	List<Pos> scc = dfs(q);
	tiling[p.i][p.j][p.k] = true;
	return (!reachesBorders(scc));
    }


    static int findCorridor() {
	for (int i=0; i<N; i++)
	    for (int j=0;j<M; j++)
		for (int k=0; k<=1; k++)
		    if (tiling[i][j][k] && !visited[i][j][k]) {
			List<Pos> scc = dfs(new Pos(i,j,k));
			if (checkCorridor(scc)) 
			    return scc.size();
		    }
	return 0;  // NOT FOUND
    }
    

    /* read one tiling
     */
    static void readTiling(BufferedReader in) throws IOException {
	String[] tokens = in.readLine().split(" ");
	N = Integer.parseInt(tokens[0]);
	M = Integer.parseInt(tokens[1]);

	tiling = new boolean[N][M][2];
	visited = new boolean[N][M][2];
	for(int i = 0; i<N; i++) {
	    String line = in.readLine();
	    for(int j=0; j<M; j++) {
		for (int k=0; k<=1; k++) {
		    char c = line.charAt(2*j + k);
		    if(c=='0') 
			tiling[i][j][k] = true;
		    else if (c=='1')
			tiling[i][j][k] = false;
		    else 
			throw new IllegalArgumentException();
		}
	    }
	}
    }


    public static void main(String args[]) {
	BufferedReader in = 
	    new BufferedReader( new InputStreamReader(System.in) );
	try {
	    int T = Integer.parseInt(in.readLine());
	    for(int i = 0; i<T; i++) {
		readTiling(in);   
		int size = findCorridor();
		if (size == 0) 
		    System.out.println("NO MINIMAL CORRIDOR");
		else 
		    System.out.println(size);
	    }
	} catch (IOException e) {
	    System.out.print(e);
	}
    }
}


class Pos {
    public int i, j, k;
	
    public Pos (int i, int j, int k) {
	this.i = i;
	this.j = j;
	this.k = k;
    }

    public String toString() {
	return ("(" +  i + ","+ j + ","+ k + ")");
    }

    public boolean equals(Object other) {
	if (other == null || !(other instanceof Pos))
	    return false;
	Pos that = (Pos)other;
	return (this.i == that.i && 
		this.j == that.j &&
		this.k == that.k);
    }
}
