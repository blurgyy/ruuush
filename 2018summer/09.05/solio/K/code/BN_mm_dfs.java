import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.LinkedList;

/**
 * @author Margarida Mamede
 */


public class BN_mm_dfs
{

    public static final int COORD_BASE = 1000;

    public static final int NODES_2D_BASE = 1000000;


    private Gr3D sculpture;

    private Gr2D projection;


    public BN_mm_dfs( int nNeedles )
    {
        sculpture = new Gr3D(nNeedles);
        projection = new Gr2D(nNeedles);
    }


    public void addNeedle( int x1, int y1, int z1, int x2, int y2, int z2 )
    {
        sculpture.addEdge(x1, y1, z1, x2, y2, z2);
        projection.addEdge(x1, y1, x2, y2);
    }
        

    // 0 - 3D acyclic / 2D acyclic 
    // 1 - 3D acyclic / 2D  cyclic 
    // 2 - 3D  cyclic / 2D acyclic 
    // 3 - 3D  cyclic / 2D  cyclic 
    //
    public int hasCycles( )
    {
        int result = 0;
        if ( projection.isCyclic() )
            result++;
        if ( sculpture.isCyclic() )
            result += 2;
        return result;
    } 


    public static void main( String[] args ) throws IOException
    {
        BufferedReader input = 
            new BufferedReader( new InputStreamReader(System.in) );

        int numNeedles = Integer.parseInt( input.readLine() );
        BN_mm_dfs design = new BN_mm_dfs(numNeedles);

        for ( int i = 0; i < numNeedles; i++ )
        {
            String[] tokens = input.readLine().split(" ");
            int x1 = Integer.parseInt( tokens[0] );
            int y1 = Integer.parseInt( tokens[1] );
            int z1 = Integer.parseInt( tokens[2] );
            int x2 = Integer.parseInt( tokens[3] );
            int y2 = Integer.parseInt( tokens[4] );
            int z2 = Integer.parseInt( tokens[5] );
            design.addNeedle(x1, y1, z1, x2, y2, z2);
        }
        input.close();

        int cycles = design.hasCycles();
        switch ( cycles ) 
        {
            case 0: 
                System.out.println("No true closed chains");
                System.out.println("No floor closed chains");
                break;
            case 1: 
                System.out.println("No true closed chains");
                System.out.println("Floor closed chains");
                break;
            case 2: 
                System.out.println("True closed chains");
                System.out.println("No floor closed chains");
                break;
            case 3: 
                System.out.println("True closed chains");
                System.out.println("Floor closed chains");
                break;
        }
    }


}


// *************************************************************************
//
// CLASS Gr --- Graph
//
// *************************************************************************

class Gr
{

    private Map<Integer,Integer> pts2nodes; 

    private int nNodes;

    private List<Integer>[] adjNodes;


    @SuppressWarnings("unchecked")
    public Gr( int maxEdges )
    {
        int maxNodes = 2 * maxEdges;
        pts2nodes = new HashMap<Integer,Integer>(maxNodes);
        nNodes = 0;
        adjNodes = ( List<Integer>[] ) new List[maxNodes];
        for ( int i = 0; i < maxNodes; i++ )
            adjNodes[i] = new LinkedList<Integer>();
    }


    protected void addEdge( int node1, int node2 )
    {
        adjNodes[node1].add(node2);
        adjNodes[node2].add(node1);
    }
        

    protected int getNode( int point )
    {
        Integer node = pts2nodes.get(point);
        if ( node == null )
        {
            node = nNodes++;
            pts2nodes.put(point, node);
        }
        return node;
    }


    public boolean isCyclic( )
    {
        byte[] colour = new byte[nNodes];

        for ( int n = 0; n < nNodes; n++ )
            if ( colour[n] == 0 )
                if ( this.isCyclic(colour, n, -1) )
                    return true;
                
        return false;
    } 


    public boolean isCyclic( byte[] colour, int node, int parent )
    {
        colour[node] = 1;

        for ( int n : adjNodes[node] )
            if ( n != parent )
                if ( ( colour[n] == 1 )
                     || 
                     ( colour[n] == 0 && this.isCyclic(colour, n, node) )
                   )
                    return true;

        colour[node] = 2;
        return false;
    } 


}


// *************************************************************************
//
// CLASS Gr3D --- Graph 3D
//
// *************************************************************************

class Gr3D extends Gr
{

    public static final int COORD_BASE = BN_mm_dfs.COORD_BASE;


    public Gr3D( int maxEdges )
    {
        super(maxEdges);
    }


    public void addEdge( int x1, int y1, int z1, int x2, int y2, int z2 )
    {
        int node1 = this.getNode(x1, y1, z1);
        int node2 = this.getNode(x2, y2, z2);
        super.addEdge(node1, node2);
    }
        

    private int getNode( int x, int y, int z )
    {
        int point = ( x * COORD_BASE + y ) * COORD_BASE + z;
        return super.getNode(point);
    }


}


// *************************************************************************
//
// CLASS G2D --- Graph 2D
//
// *************************************************************************

class Gr2D  extends Gr
{

    public static final int COORD_BASE = BN_mm_dfs.COORD_BASE;

    public static final long NODES_BASE = BN_mm_dfs.NODES_2D_BASE;


    private Set<Long> edges; 


    public Gr2D( int maxEdges )
    {
        super(maxEdges);
        edges = new HashSet<Long>(maxEdges);
    }


    public void addEdge( int x1, int y1, int x2, int y2 )
    {
        // Seft-loops are discarded.
        if ( x1 != x2 || y1 != y2 )  
        {
            int node1 = this.getNode(x1, y1);
            int node2 = this.getNode(x2, y2);
            // Existing edges are discarded.
            if ( this.addNewEdge(node1, node2) )
                super.addEdge(node1, node2);
        }
    }
        

    private int getNode( int x, int y )
    {
        int point = x * COORD_BASE + y;
        return super.getNode(point);
    }


    private boolean addNewEdge( int node1, int node2 )
    {
        long edge;
        if ( node1 < node2 )
            edge = node1 * NODES_BASE + node2;
        else
            edge = node2 * NODES_BASE + node1;
        return edges.add(edge);
    } 


}
