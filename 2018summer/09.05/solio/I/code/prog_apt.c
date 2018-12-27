/*---------------------------------------------------
/  Author: Ana Paula Tomas
/  Date: November 2016
/  Solves "white rabbit"
/---------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

#define NMAX 201
#define CMAX 200

#define INFTY CMAX*13+1

static int INV13[13] = {0,1,7,9,10,8,11,2,5,3,4,6,12}; // not defined for 0
#define NORM13(V) ((V)%13 >= 0? (V)%13: 13+(V)%13)

int Mat[CMAX+1][CMAX+1], D[CMAX];

typedef struct edge {
  int vertex, weight;
  struct edge *nxt;
} EDGE;

#define DEST(edge) ((edge) -> vertex)
#define WEIGHT(edge) ((edge) -> weight)
#define NXTADJ(edge) ((edge) -> nxt)

typedef struct {
  EDGE *adjs;
} NODE;

#define DIST(no) ((no).dist)
#define ADJS(no) ((no).adjs)


NODE Graph[NMAX+1];

void elementary_transf(int pivot,int r,int lines,int cols){
  int j;

  for (j=1;j<=cols;j++) {
    Mat[lines][j] -= Mat[r][j]*pivot;
    Mat[lines][j] = NORM13(Mat[lines][j]);
  }
  D[lines] -= D[r]*pivot;
  D[lines] = NORM13(D[lines]);
}    

EDGE *new_edge(int v,int weight,EDGE* nxt) {
  EDGE *e = (EDGE *) malloc(sizeof(EDGE));
  DEST(e) = v;
  WEIGHT(e) = weight;
  NXTADJ(e) = nxt;
  return e;
}

void find_graph(int n, int ntrips) {
  int lines=0, columns=0, oldcolumns, ne;
  int vbas[CMAX+1], Column[CMAX+1][2], i, j, t, x, y, aux;
  int Index[NMAX+1][NMAX+1] = {0};

  for(t=0;t<ntrips && lines < n*(n-1)/2 && lines < CMAX;t++) {
    scanf("%d%d%d",&D[lines],&ne,&x);
    oldcolumns = columns; // after oldcolumns previous rows have 0's
      
    for(j=1;j<ne;j++){
      scanf("%d",&y);
      if (Index[x][y]==0) {
	Index[x][y] = Index[y][x] = ++columns;
	Mat[lines][columns]=1;
	Column[columns][0]=x; Column[columns][1]=y;
      }  else { // invariant: Mat[lines] is zero in each iteration
	Mat[lines][Index[x][y]]++;
	Mat[lines][Index[x][y]] = NORM13(Mat[lines][Index[x][y]]);
      }
      x = y;
    }

    // reduce (triangular form)
    for(i=0; i < lines; i++)
      if(Mat[lines][vbas[i]]) 
	elementary_transf(Mat[lines][vbas[i]],i,lines,oldcolumns);  
      
    for(j=1;j<=columns && Mat[lines][j]==0;j++);
    if (j <= columns) {  // not a redundant trip  (a new constraint)
      vbas[lines] = j;   // basic variable  (pivot for the new constraint)
      if (Mat[lines][j] != 1) {
	aux = INV13[Mat[lines][j]];
	Mat[lines][j] = 1;  // pivot will be 1
	while(++j <= columns) {
	  Mat[lines][j] *= aux;
	  Mat[lines][j] = NORM13(Mat[lines][j]);
	}
	D[lines] *= aux;
	D[lines] = NORM13(D[lines]);
      }
      lines++;
    }
  }

  // backwards substitution to solve the system (in triangular form) 
  for(i=lines-2;i>=0;i--) {
    for(j=i+1;j<lines;j++)
      D[i] -= Mat[i][vbas[j]]*D[j];
    D[i] = NORM13(D[i]);
#ifdef DEBUG
    printf("(%d,%d):%d\n",Column[vbas[i]][0],Column[vbas[i]][1],D[i]);
#endif
  }

  // construct graph
  for(i=1;i<=n;i++) 
    ADJS(Graph[i])= NULL;

  for(i=0;i<lines;i++) {
    x = Column[vbas[i]][0];
    y = Column[vbas[i]][1];
    ADJS(Graph[x]) = new_edge(y,D[i],ADJS(Graph[x]));
    ADJS(Graph[y]) = new_edge(x,D[i],ADJS(Graph[y]));
  }
}


//=========================  heapmin ==============================

typedef struct qnode {
  int vert, vertkey;
} QNODE;

typedef struct heapMin {
  int sizeMax, size;
  QNODE *a;
  int *pos_a;
} HEAPMIN;

//---------  available functions and macros (heapmin) --------------------

HEAPMIN *build_heap_min(int v[], int n);
int extractMin(HEAPMIN *q);   // retorna v 
void decreaseKey(int v, int newkey, HEAPMIN *q);


#define POSINVALIDA 0

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

static void heapify(int i,HEAPMIN *q);
static void swap(int i,int j,HEAPMIN *q);
static int compare(int i, int j, HEAPMIN *q);
static int pos_valida(int i,HEAPMIN *q);

static int compare(int i, int j, HEAPMIN *q){
  if (q -> a[i].vertkey < q -> a[j].vertkey)
    return -1;
  if (q -> a[i].vertkey == q -> a[j].vertkey)
    return 0;
  return 1;
}


static int pos_valida(int i, HEAPMIN *q) {
  return (i >= 1 && i <= q -> size);
}

int extractMin(HEAPMIN *q) {
  int vertv = q -> a[1].vert;
  swap(1,q->size,q);
  q -> pos_a[vertv] = POSINVALIDA;  //  vertv was removed
  q -> size--;
  heapify(1,q);
  return vertv;
}

void decreaseKey(int vertv, int newkey, HEAPMIN *q){
  int i = q -> pos_a[vertv];
  q -> a[i].vertkey = newkey;

  while(i > 1 && compare(i,PARENT(i),q) < 0){
    swap(i,PARENT(i),q);
    i = PARENT(i);
  }
}


static void heapify(int i,HEAPMIN *q) {
  // min-heap 
  int l, r, smallest;
  l = LEFT(i);
  if (l > q -> size) l = i;
  r = RIGHT(i);
  if (r > q -> size) r = i;
  
  smallest = i;
  if (compare(l,smallest,q) < 0) 
    smallest = l;
  if (compare(r,smallest,q) < 0) 
    smallest = r;
  
  if (i != smallest) {
    swap(i,smallest,q);
    heapify(smallest,q);
  }
}

static void swap(int i,int j,HEAPMIN *q){
  QNODE aux;
  q -> pos_a[q -> a[i].vert] = j;
  q -> pos_a[q -> a[j].vert] = i;
  aux = q -> a[i];
  q -> a[i] = q -> a[j];
  q -> a[j] = aux;
}



HEAPMIN *build_heap_min(int vec[], int n){
  // the elements are in vec[1] .. vec[n] 
  // builds the corresponding heapMin in time O(n)
  HEAPMIN *q = (HEAPMIN *)malloc(sizeof(HEAPMIN));
  int i;
  q -> a = (QNODE *) malloc(sizeof(QNODE)*(n+1));
  q -> pos_a = (int *) malloc(sizeof(int)*(n+1));
  q -> sizeMax = n; // position 0 is kept free
  q -> size = n;   
  for (i=1; i<= n; i++) {
    q -> a[i].vert = i;
    q -> a[i].vertkey = vec[i];
    q -> pos_a[i] = i;  // initial position of the ith element in the heap
  }

  for (i=n/2; i>=1; i--) 
    heapify(i,q);
  return q;
}




int dijkstra(int source,int target,int nverts) {
  int dist[nverts+1], i, v, w;
  HEAPMIN *heap;
  EDGE *adj;

  // init heap 
  for(i=0;i <= nverts; i++) 
    dist[i] = INFTY;

  dist[source]=0;
  heap = build_heap_min(dist,nverts);

  while((v = extractMin(heap))!= target) {
    adj = ADJS(Graph[v]);
    while(adj != NULL) {
      w = DEST(adj);
      if (dist[w] > dist[v]+WEIGHT(adj)) {
	dist[w] = dist[v]+WEIGHT(adj);
        decreaseKey(w,dist[w],heap);
      } 
      adj = NXTADJ(adj);
    }
  }
  return dist[target];
}





#ifdef DEBUG
int weight_edge(int s,int t) {
  EDGE *edge = ADJS(Graph[s]);
  while (edge != NULL && DEST(edge) != t) edge = NXTADJ(edge);
  if (edge == NULL) {
    fprintf(stderr,"Error in the graph?\n");
    exit(EXIT_FAILURE);
  }
  return WEIGHT(edge);
}

void checksol(int nargs,char *args[]) {
  FILE *f;
  int ntrips, length, d, lixo, nt, x, y, i;
  if (nargs > 1) {
    f = fopen(args[1],"r");
    fscanf(f,"%d%d%d%d", &lixo,&lixo,&lixo,&ntrips);
    for(i=0; i< ntrips; i++) {
      length = 0;
      fscanf(f,"%d%d%d", &d,&nt,&x);
      while(--nt > 0) {
	fscanf(f,"%d", &y);
	length += weight_edge(x,y);
	x = y;
      }
      if (length%13 != d) {
	fprintf(stderr,"Error: trip %d: d = %d length = %d\n",i+1,d,length);
	exit(EXIT_FAILURE);
      } else  fprintf(stderr,"Ok trip %d\n",i+1);
    }
  }
}
#endif



int main(int nargs,char *args[]) {

  int n,alice,hole,ntrips;

  scanf("%d%d%d%d", &n,&alice,&hole,&ntrips);

  find_graph(n,ntrips);
  
#ifdef DEBUG
  checksol(nargs,args);
#endif  

  printf("%d\n",dijkstra(alice,hole,n));

  return 0;
}



