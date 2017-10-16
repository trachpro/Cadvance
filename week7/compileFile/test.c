#include "graphApi.h"
#include<stdio.h>

int main()
{
  Graph g = createGraph(5);
  addEdge(g, 0,1);
  addEdge(g, 1,2);
  addEdge(g, 1,3);

  int output[5];
  initOutput(output, 5);
  getAdjacentVertices(g, 1, output);

  for(int i = 0 ; i < 5; i++) {
    if(output[i]!=-1) {
      printf("%5d",output[i]);
    }
  }
  printf("\n");

  free(g.matrix);
}
