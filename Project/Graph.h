#ifndef __GRAPH_H
#define __GRAPH_H
#include "List.h"
#include "IO.h"
class Graph
{
private:
	int** _graph;
	int _size;
	bool _allocated;
public:
	Graph();
	Graph(int n);
	Graph(int** mat, int n);
	Graph(const Graph &G);
	~Graph();
	
	void MakeEmptyGraph(int n);
	bool IsAdjacent(int u, int v) const;
	List *GetAdjList(int u) const;
	void AddEdge(int u, int v, int c);
	void RemoveEdge(int u, int v);
	int GetEdgeValue(int u, int v) const;
	void IncreaseFlow(int u, int v, int value);
	int GetSize() const;
	void SetAllocation(bool b);
	const Graph& operator=(const Graph& G);

};
#endif
