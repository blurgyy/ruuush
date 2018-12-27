import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

/**
 * @author Margarida Mamede
 */


public class BN_mm_uf
{

    public static final int COORD_BASE = 1000;

    public static final int NODES_2D_BASE = 1000000;


    private AG3D sculpture;

    private boolean scIsCyclic;

    private AG2D projection;

    private boolean prIsCyclic;


    public BN_mm_uf( int nNeedles )
    {
        sculpture = new AG3D(nNeedles);
        scIsCyclic = false;
        projection = new AG2D(nNeedles);
        prIsCyclic = false;
    }


    // 0 - 3D acyclic / 2D acyclic 
    // 1 - 3D acyclic / 2D  cyclic 
    // 2 - 3D  cyclic / 2D acyclic 
    // 3 - 3D  cyclic / 2D  cyclic 
    //
    public int addNeedle( int x1, int y1, int z1, int x2, int y2, int z2 )
    {
        int result = 0;
        if ( prIsCyclic || !projection.addEdge(x1, y1, x2, y2) )
        {
            prIsCyclic = true;
            result++;
        }
        if ( scIsCyclic || !sculpture.addEdge(x1, y1, z1, x2, y2, z2) )
        {
            scIsCyclic = true;
            result += 2;
        }
        return result;
    }
        

    public static void main( String[] args ) throws IOException
    {
        BufferedReader input = 
            new BufferedReader( new InputStreamReader(System.in) );

        int numNeedles = Integer.parseInt( input.readLine() );
        BN_mm_uf design = new BN_mm_uf(numNeedles);

        int cycles = 0;
        for ( int i = 0; i < numNeedles && cycles < 3; i++ )
        {
            String[] tokens = input.readLine().split(" ");
            int x1 = Integer.parseInt( tokens[0] );
            int y1 = Integer.parseInt( tokens[1] );
            int z1 = Integer.parseInt( tokens[2] );
            int x2 = Integer.parseInt( tokens[3] );
            int y2 = Integer.parseInt( tokens[4] );
            int z2 = Integer.parseInt( tokens[5] );
            cycles = design.addNeedle(x1, y1, z1, x2, y2, z2);
        }
        input.close();

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
// CLASS AG3D --- Acyclic Graph 3D
//
// *************************************************************************

class AG3D
{

    public static final int COORD_BASE = BN_mm_uf.COORD_BASE;

 
    private Map<Integer,Integer> pts2nodes; 

    private int nNodes;

    private UnionFind comps;


    public AG3D( int maxEdges )
    {
        int maxNodes = 2 * maxEdges;
        pts2nodes = new HashMap<Integer,Integer>(maxNodes);
        nNodes = 0;
        comps = new UnionFind(maxNodes);
    }


    public boolean addEdge( int x1, int y1, int z1, int x2, int y2, int z2 )
    {
        int node1 = this.getNode(x1, y1, z1);
        int node2 = this.getNode(x2, y2, z2);
        int rep1 = comps.find(node1);
        int rep2 = comps.find(node2);
        if ( rep1 == rep2 )
            return false;

        comps.union(rep1, rep2);
        return true;
    }
        

    private int getNode( int x, int y, int z )
    {
        int point = ( x * COORD_BASE + y ) * COORD_BASE + z;
        Integer node = pts2nodes.get(point);
        if ( node == null )
        {
            node = nNodes++;
            pts2nodes.put(point, node);
        }
        return node;
    }


}


// *************************************************************************
//
// CLASS AG2D --- Acyclic Graph 2D
//
// *************************************************************************

class AG2D
{

    public static final int COORD_BASE = BN_mm_uf.COORD_BASE;

    public static final long NODES_BASE = BN_mm_uf.NODES_2D_BASE;


    private Map<Integer,Integer> pts2nodes; 

    private int nNodes;

    private UnionFind comps;

    private Set<Long> edges; 


    public AG2D( int maxEdges )
    {
        int maxNodes = 2 * maxEdges;
        pts2nodes = new HashMap<Integer,Integer>(maxNodes);
        nNodes = 0;
        comps = new UnionFind(maxNodes);
        edges = new HashSet<Long>(maxEdges);
    }


    public boolean addEdge( int x1, int y1, int x2, int y2 )
    {
        if ( x1 == x2 && y1 == y2 )
            // Seft-loops are discarded.
            return true;
        
        int node1 = this.getNode(x1, y1);
        int node2 = this.getNode(x2, y2);
        if ( !this.addEdge(node1, node2) )
            // Existing edges are discarded.
            return true;

        int rep1 = comps.find(node1);
        int rep2 = comps.find(node2);
        if ( rep1 == rep2 )
            return false;

        comps.union(rep1, rep2);
        return true;
    }
        

    private int getNode( int x, int y )
    {
        int point = x * COORD_BASE + y;
        Integer node = pts2nodes.get(point);
        if ( node == null )
        {
            node = nNodes++;
            pts2nodes.put(point, node);
        }
        return node;
    }


    private boolean addEdge( int node1, int node2 )
    {
        long edge;
        if ( node1 < node2 )
            edge = node1 * NODES_BASE + node2;
        else
            edge = node2 * NODES_BASE + node1;
        return edges.add(edge);
    } 


}


// *************************************************************************
//
// CLASS UnionFind
//
// *************************************************************************

class UnionFind
{

    private int[] partition; 


    public UnionFind( int domainSize )
    {  
        partition = new int[domainSize];
        for ( int i = 0; i < domainSize; i++ )
            partition[i] = -1;
    }


    // With path compression.
    public int find( int element )
    {
        return this.findPathCompr(element);
    }


    private int findPathCompr( int element )
    {
        if ( partition[element] < 0 )
            return element;

        partition[element] = this.findPathCompr( partition[element] );
        return partition[element];
    }


    // Union by rank.
    public void union( int rep1, int rep2 )
    {  
        if ( partition[rep1] <= partition[rep2] )
        {
            if ( partition[rep1] == partition[rep2] )
                partition[rep1]--;
            partition[rep2] = rep1;
        }
        else
            partition[rep1] = rep2;
    }


}
