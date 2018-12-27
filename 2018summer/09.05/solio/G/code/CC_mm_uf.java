import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.BitSet;

/**
 * @author Margarida Mamede
 */


public class CC_mm_uf
{

    private int nRows;

    private int nCols;

    private int nNodes;

    private int[][][] tiling;

    private Node[] graph;

    private UnionFind comps;


    private List<Integer> corridor;

    private int corRoot;

    private int corSize;

    private List<Integer>[] critical;

    private boolean[] isCritical;



    public CC_mm_uf( int numRows, int numCols )
    {
        nRows = numRows;
        nCols = numCols;
        nNodes = 0;
        tiling = new int[2][nRows][nCols];
    }


    public void addRow( int rowIdx, String row )
    {
        for ( int i = 0; i < nCols; i++ )
        {
            if ( row.charAt( 2*i ) == '0' )
                tiling[0][rowIdx][i] = nNodes++;
            else
                tiling[0][rowIdx][i] = -1;

            if ( row.charAt( 2*i+1 ) == '0' )
                tiling[1][rowIdx][i] = nNodes++;
            else
                tiling[1][rowIdx][i] = -1;
        }
    }


    public int corridorSize( )
    {
        this.buildGraph();
        corRoot = comps.corridorRoot();
        if ( corRoot < 0 )
            return 0;

        corSize = comps.size(corRoot);
        if ( !this.isMinimal() )
            return 0;

        return corSize;
    }


    private void buildGraph( )
    {
        graph = new Node[nNodes];
        for ( int i = 0; i < nNodes; i++ )
            graph[i] = new Node();
        comps = new UnionFind(nNodes);
        this.setSides();
        this.compAdjs();
        
    }


    private void setSides( )
    {
        int lastRow = nRows - 1;
        int lastCol = nCols - 1;

        for ( int i = 0; i < nCols; i++ )
        {
            this.setSide(tiling[0][0][i], 0);

            if ( i % 2 == 0 )
                this.setSide(tiling[1][0][i], 0);

            this.setSide(tiling[1][lastRow][i], 1);

            if ( ( lastRow + i ) % 2 == 0 )
                this.setSide(tiling[0][lastRow][i], 1);
        }

        for ( int i = 0; i < nRows; i++ )
        {
            this.setSide(tiling[0][i][0], 2);

            if ( i % 2 != 0 )
                this.setSide(tiling[1][i][0], 2);

            this.setSide(tiling[1][i][lastCol], 3);

            if ( ( lastCol + i ) % 2 != 0  )
                this.setSide(tiling[0][i][lastCol], 3);
        }
    }


    private void setSide( int node, int side )
    {
        if ( node >= 0 )
        {
            graph[node].setSide(side);
            comps.setSide(node, side);
        }
    }


    private void compAdjs( )
    {
        List<Integer> adjs = new ArrayList<Integer>(3);
        int t, i, j;
        int node, rep1, rep2;

        for ( t = 0; t < 2; t++ )
            for ( i = 0; i < nRows; i++ )
                for ( j = 0; j < nCols; j++ )
                    if ( ( node = tiling[t][i][j] ) >= 0 )
                    {
                        this.compAdjs(adjs, t, i, j);
                        for ( int n : adjs )
                        {  
                            graph[node].setAdj(n);
                            graph[n].incDegree();
                            rep1 = comps.find(node);
                            rep2 = comps.find(n);
                            if ( rep1 != rep2 )
                                comps.union(rep1, rep2);
                        }
                    }
    }
    

    // Only to the left or to the top.
    private void compAdjs( List<Integer> adjs, int type, int row, int col )
    {
        adjs.clear();
        int sum = row + col;

        if ( type == 0 )
        {
            // To the left
            if ( col > 0 )
            {
                this.addToAdjs(adjs, tiling[1][row][col - 1]);
                if ( sum % 2 == 0 )
                    this.addToAdjs(adjs, tiling[0][row][col - 1]);
            }
            // To the top
            if ( row > 0 )
            {
                this.addToAdjs(adjs, tiling[1][row - 1][col]);
                if ( sum % 2 != 0 )
                    this.addToAdjs(adjs, tiling[0][row - 1][col]);
            }
        }
        else
        {
            // To the left
            if ( sum % 2 == 0 )
                this.addToAdjs(adjs, tiling[0][row][col]);
            else if ( col > 0 )
                this.addToAdjs(adjs, tiling[1][row][col - 1]);

            // To the top
            if ( sum % 2 != 0 )
                this.addToAdjs(adjs, tiling[0][row][col]);
            else if ( row > 0 )
                this.addToAdjs(adjs, tiling[1][row - 1][col]);
        }
    }


    private void addToAdjs( List<Integer> adjs, int node )
    {
        if ( node >= 0 )
            adjs.add(node);
    }
        

    
    @SuppressWarnings("unchecked")
    private boolean isMinimal( )
    {
        corridor = new ArrayList<Integer>(corSize);
        critical = new List[6];
        for ( int d = 1; d < critical.length; d++ )
            critical[d] = new LinkedList<Integer>();
        isCritical = new boolean[nNodes];
        int degree;

        for ( int i = 0; i < nNodes; i++ )
            if ( comps.find(i) == corRoot )
            {
                corridor.add(i);
                degree = graph[i].getDegree();
                if ( degree == 1 || degree == 5 )
                {
                    critical[degree].add(i);
                    isCritical[i] = true;
                }
            }

        this.nodesInCycles();

        for ( int d = critical.length - 1; d > 0; d-- )
            for ( int n : critical[d] )
                if ( this.canRemove(n) )
                    return false;
        
        return true;
    }


    private void nodesInCycles( )
    {
        comps = new UnionFind(nNodes);
        int rep1, rep2;

        for ( int n : corridor )
            comps.setSides(n, graph[n].getSides());

        for ( int n : corridor )
            for ( int m : graph[n].getAdjs() )
            {  
                rep1 = comps.find(n);
                rep2 = comps.find(m);
                if ( rep1 != rep2 )
                    comps.union(rep1, rep2);
                else 
                {  
                    this.addToCritical(n);
                    break;
                }
            }
    }


    private void addToCritical( int node )
    {
        if ( !isCritical[node] )
        {  
            critical[graph[node].getDegree()].add(node);
            isCritical[node] = true;
        }
        for ( int m : graph[node].getAdjs() )
            if ( !isCritical[m] )
            {  
                critical[graph[m].getDegree()].add(m);
                isCritical[m] = true;
            }
    }


    private boolean canRemove( int node )
    {
        comps = new UnionFind(nNodes);
        int rep1, rep2;

        for ( int n : corridor )
            comps.setSides(n, graph[n].getSides());

        for ( int n : corridor )
            if ( n != node )
                for ( int m : graph[n].getAdjs() )
                    if ( m != node )
                    {  
                        rep1 = comps.find(n);
                        rep2 = comps.find(m);
                        if ( rep1 != rep2 )
                            comps.union(rep1, rep2);
                    }
        return comps.corridorRoot() >= 0;
    }


    public static void main( String[] args ) throws IOException
    {
        BufferedReader input = 
            new BufferedReader( new InputStreamReader(System.in) );

        int numTests = Integer.parseInt( input.readLine() );
        for ( int t = 0; t < numTests; t++ )
        {
            String[] tokens = input.readLine().split(" ");
            int numRows = Integer.parseInt( tokens[0] );
            int numCols = Integer.parseInt( tokens[1] );
            CC_mm_uf cairo = new CC_mm_uf(numRows, numCols);

            for ( int i = 0; i < numRows; i++ )
                cairo.addRow(i, input.readLine());

            int size = cairo.corridorSize();
            if ( size > 0 )
                System.out.println(size);
            else
                System.out.println("NO MINIMAL CORRIDOR");
        }
        input.close();
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

    private BitSet[] sides; 


    public UnionFind( int domainSize )
    {  
        partition = new int[domainSize];
        sides = new BitSet[domainSize];
        for ( int i = 0; i < domainSize; i++ )
        {  
            partition[i] = -1;
            sides[i] = new BitSet(4);
        }
    }


    public void setSides( int element, BitSet elemSides  )
    {
        sides[element].or(elemSides);
    }


    public void setSide( int element, int side )
    {
        sides[element].set(side);
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


    // Union by size.
    public void union( int rep1, int rep2 )
    {  
        if ( partition[rep1] <= partition[rep2] )
        {
            partition[rep1] += partition[rep2];
            partition[rep2] = rep1;
            sides[rep1].or( sides[rep2] );
        }
        else
        {
            partition[rep2] += partition[rep1];
            partition[rep1] = rep2;
            sides[rep2].or( sides[rep1] );
        }
    }


    public int size( int rep )
    {  
        return -partition[rep];
    }


    public int corridorRoot( )
    {  
        for ( int i = 0; i < partition.length; i++ )
            if ( partition[i] < 0 && sides[i].cardinality() == 4 )
                return i;
        return -1;
    }


}


// *************************************************************************
//
// CLASS Node
//
// *************************************************************************

class Node
{

    private List<Integer> adjs;

    private int degree;

    private BitSet sides;


    public Node( )
    {
        adjs = new LinkedList<Integer>();
        degree = 0;
        sides = new BitSet(4);
    }


    public void setAdj( int node )
    {
        adjs.add(node);
        degree++;
    }


    public void incDegree( )
    {
        degree++;
    }


    public void setSide( int side )
    {
        sides.set(side);
    }


    public List<Integer> getAdjs( )
    {
        return adjs;
    }


    public int getDegree( )
    {
        return degree;
    }


    public BitSet getSides( )
    {
        return sides;
    }


}


    
