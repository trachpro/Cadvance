

#include "jrb.h"
typedef JRB Graph;

Graph createGraph() {
  return make_jrb();
}

Graph checkGraph(Graph g) {
  if(g == NULL) {
     return  make_jrb();
  }

  return (JRB)jval_v(g->val);
}

addEdge(Graph g, int v1, int v2) {
  
  Graph graph1 = jrb_find_int(g,v1);
  Graph graph2 = jrb_find_int(g,v2);

  graph1 = checkGraph(graph1);

  graph2 = checkGraph(graph2);

  jrb_insert_int(graph1, v2, new_jval_i(1));
  jrb_insert_int(graph2, v1, new_jval_i(1));

  jrb_insert_int(g, v2, new_jval_v(graphV2));
  jrb_insert_int(g, v1, new_jval_v(graphV1));
}

int adjacent(Graph g, v1, v2) {
  Graph graph1 = jrb_find_int(g, v1);
  Graph graph2 = jrb_find_int(g, v2);
  
  Graph x = jrb_find_int(graph1, v2),
    y = jrb_find_int(graph1, v2);

  return x->val && y->val;
}

int getAdjacentVertices(Graph g, int v, int *output) {
  Graph x = jrb_find_int(g,v);
  Graph node;

  x = checkGraph(x);
  int total = 0;
  
  jrb_traverse(node, g) {
    output[total++] = node->key;
  }

  return total;
}

int main()
{
  Graph g = creatGraph();

  addEdge(g,0,1);
  addEdge(g,1,2);
  addEdge(g,1,3);

  int output[5];
  int len = getAdjacentVertices(g, 1, output);
  for(int i = )
}
