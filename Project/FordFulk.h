#ifndef __FORDFULK_H
#define __FORDFULK_H
#include "Graph.h"
#include "Queue.h"
#include "PriorityQ.h"
#include "List.h"
#include "IO.h"
class FordFulk {
private:
	const Graph &_capacity;
	Graph *_flow, *_residual;
	int _s, _t, _maxFlow;
	int _size;

	bool FindPathByBFS(const Graph &G, int *parent, bool *visited, Queue &Q) const;
	bool FindPathByGreed(const Graph &G, int *parent, PriorityQ &Q, int *d) const;
	int SumEdgesFromStart(const Graph &G) const;
	void IncreasePathFlow(const int *parent, int amount);
	int FindMinEdgeInPath(const Graph &G, const int *parent) const;
	void FindMinCut(const Graph *G, bool *visited, List &S, List &T) const;
	void ResetFlow();


public:

	FordFulk(const Graph &G,int s, int t);
	~FordFulk();
	
	void CalcMaxFlow();
	void RunWithBFS();
	void RunWithGreed();
	static int Min(int a, int b);
	
	
};
#endif