
typedef struct {
  int *matrix;
  int sizemax;
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v1, int* output);
void initOutput(int * output, int size);
