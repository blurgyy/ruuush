// [SWERC 2016] Passwords - Pedro Ribeiro (DCC/FCUP)
// DP + Aho-Corasick (Java, trie with map, state in map)

import java.util.*;

class Node implements Comparable<Node>{
    static Node root;
    static int count = 0;
    HashMap<Character, Node> child;
    boolean word;
    Node fail;
    int pos;

    Node() {
	child = new HashMap<Character, Node>();
	word = false;
	if (count==0) root = this;
	pos  = count++;
    }

    void insert(String s) {
	if (s.length()==0) word = true;
	else {
	    if (child.get(s.charAt(0)) == null) child.put(s.charAt(0), new Node());
	    child.get(s.charAt(0)).insert(s.substring(1));
	}	
    }

    Node exists(String s) {
	if (s.length()==0) return this;
	if (child.get(s.charAt(0)) != null) return child.get(s.charAt(0)).exists(s.substring(1));
	return null;	
    }

    void makeFailLinks(String cur) {
	int len = cur.length();
	Node aux = null;
	for (int i=1; i<=len; i++) {
	    aux = root.exists(cur.substring(i));
	    if (aux != null) break;
	}
	fail = aux;
	
	for (Map.Entry<Character, Node> e : child.entrySet())
	    e.getValue().makeFailLinks(cur + e.getKey());
    }

    Node next(char c) {
	if (child.get(c) != null) return child.get(c);
	else if (this != root)    return fail.next(c);
	else return root;
    }

    public int compareTo(Node n) {
	return pos - n.pos;
    }
}

class State implements Comparable<State> {
    int len;
    Node node;
    boolean lower, upper, digit;

    State(int len, Node node, boolean lower, boolean upper, boolean digit) {
	this.len = len; this .node = node;
	this.lower = lower; this.upper = upper; this.digit = digit;
    }
    
    public int compareTo(State s) {
	if (len != s.len) return (len<s.len)?1:-1;
	if (lower != s.lower) return lower?1:-1;
	if (upper != s.upper) return upper?1:-1;
	if (digit != s.digit) return digit?1:-1;
	return node.compareTo(s.node);
    }
}

class ac_pribeiro_map {
    static int a, b, n;
    static TreeMap<State, Integer> dp;
    static final int MOD = 1000003;
    
    static int go(State s) {
	if (dp.get(s)==null) {
	    if (s.node.word) return 0;
	    int ans = 0;
	    if (s.len>=a && s.upper && s.lower && s.digit) ans++;
	    if (s.len < b) {
		for (char c='a'; c<='z'; c++)
		    ans = (ans + go(new State(s.len+1, s.node.next(c), true, s.upper, s.digit))) % MOD;
		for (char c='a'; c<='z'; c++)
		    ans = (ans + go(new State(s.len+1, s.node.next(c), s.lower, true, s.digit))) % MOD;
		for (int i=0; i<=9; i++) {
		    Node n = s.node.root;
		    if (i==0)      n = s.node.next('o');
		    else if (i==1) n = s.node.next('i');
		    else if (i==3) n = s.node.next('e');
		    else if (i==5) n = s.node.next('s');
		    else if (i==7) n = s.node.next('t');
		    ans = (ans + go(new State(s.len+1, n, s.lower, s.upper, true))) % MOD;
		}
	     }
	    dp.put(s, ans);
	    return ans;
	}
	return dp.get(s);
    }
    
    public static void main(String args[]) {
	Scanner in = new Scanner(System.in);

	Node black_list = new Node();
	
	a = in.nextInt();
	b = in.nextInt();
	n = in.nextInt();
	String dic[] = new String[n];
	for (int i=0; i<n; i++) dic[i] = in.next();

	for (int i=0; i<n; i++) {
	    int j;
	    for (j=0; j<n; j++)
		if (i!=j && dic[i].contains(dic[j])) break;
	    if (j==n) black_list.insert(dic[i]);
	}
	black_list.makeFailLinks("");

	dp = new TreeMap<State, Integer>();
	System.out.println(go(new State(0, black_list, false, false, false)));
    }
}
