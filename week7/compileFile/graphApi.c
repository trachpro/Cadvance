#include<stdio.h>
#include<stdlib.h>
#include "graphApi.h"

Graph createGraph(int sizemax) {
  Graph a;

  a.sizemax = sizemax;

  a.matrix = (int*)malloc(sizeof(int)*sizemax*sizemax);

  if(!a.matrix) {
    printf("not enough memory to create graph!\n");
  }

  return a;
}

void addEdge(Graph g, int x, int y) {

  int posx = x * g.sizemax + y;
  int posy = y * g.sizemax + x;

  g.matrix[posx] = 1;
  g.matrix[posy] = 1;
}

int adjacent(Graph g, int v1, int v2) {
  
  return g.matrix[v1 * g.sizemax + v2] || g.matrix[v2 * g.sizemax + v1];

}

int getAdjacentVertices(Graph g, int vertex, int* output) {

  int ind = 0;
  for(int i = vertex - 1; i <  g.sizemax; i++){
    if(i < 0) continue;
    if(adjacent(g, vertex, i)) {
      output[ind++] = i;
    }
  }
}

void initOutput(int *output, int size) {
  for(int i = 0 ; i< size; i++) {
    output[i] = - 1;
  }
}
