#include "PerfectMatching.h"
#include <iostream>
using namespace std;

struct PerfectMatching::Options options;
PerfectMatching *pm;
int node_num, edge_num;
// case 'j': options.fractional_jumpstart = false;
// case 'm': options.dual_LP_threshold = atof(&argv[i][2]); (0<th<1)
// case 'd': options.dual_greedy_update_option = atoi(&argv[i][2]); (1<op<2)
// case 'b': options.update_duals_before = true;
// case 'a': options.update_duals_after = true;
// case 'V': options.verbose = false;

extern "C" int Init()
{
	cout << "Initialized blossom5" << endl;
	// options.fractional_jumpstart = false;
	// options.dual_LP_threshold = atof(&argv[i][2]);
	// options.dual_greedy_update_option = atoi(&argv[i][2]);
	// options.update_duals_before = true;
	// options.update_duals_after = true;
	options.verbose = false;
	return 0;
}

extern "C" int Process(int nNodes, int nEdges, int *edges, int *weights)
{
	node_num = nNodes; edge_num = nEdges;
	pm = new PerfectMatching(node_num, edge_num);
	int e;
	for (e=0; e<edge_num; e++)
    	pm->AddEdge(edges[2*e], edges[2*e+1], weights[e]);

	pm->options = options;

	pm->Solve();
	return 0;
}

extern "C" int PrintMatching()
{
	cout << node_num << " " << node_num/2 << endl;
	int i, j;
	for (i=0; i<node_num; i++)
	{
		j = pm->GetMatch(i);
		if (i < j)
			cout << i << " " << j << endl;
	}

	return 0;
}

extern "C" int GetMatching(int * matching)
{
	// matching = new int[2*node_num];
	int nMatching=0;
	int i, j, k=0;
	for (i=0; i<node_num; i++)
	{
		j = pm->GetMatch(i);
		if (i < j)
		{
			matching[k++] = i; matching[k++] = j;
		}
	}
	nMatching = k;
	return nMatching;
}

extern "C" int Clean()
{
	cout << "Cleaned-up blossom5" << endl;
	delete pm;
	return 0;
}
