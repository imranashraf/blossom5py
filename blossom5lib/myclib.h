#ifndef myclib_h
#define myclib_h

int Init();
int Process(int node_num, int edge_num, int *edges, int *weights);
int PrintMatching();
int GetMatching(int * matching);
int Clean();

#endif
