#include "FordFulk.h"
#define bfs 0
#define greed 1

FordFulk::FordFulk(const Graph &G, int s, int t) : _capacity(G)
{
	_s = s;
	_t = t;
	_maxFlow = 0;
	_size = G.GetSize();
	_flow = new Graph(G.GetSize());
	_flow->MakeEmptyGraph(G.GetSize());
	_residual = new Graph(_capacity); //Make copy of capacity graph
}
FordFulk::~FordFulk()
{
	delete _flow;
	delete _residual;
}

void FordFulk::CalcMaxFlow()
{
	if (_s == _t)
		IO::SourceIsSinkMSG();
	else
	{
		RunWithBFS();
		ResetFlow();
		RunWithGreed();
	}
}

void FordFulk::RunWithBFS()
{
	int counter = 0; //Counts the number of augmenting pathes
	Queue Q;
	bool *visited = new bool[_size];
	int *parent = new int[_size];
	//int *path = new int[_size];
	int flowIncreaseValue;

	while (FindPathByBFS(*_residual, parent, visited, Q)) //FindPathByBFS returns true if found a path from s to t in _residual,
	{//                                                                                        saves the path in path
		flowIncreaseValue = FindMinEdgeInPath(*_residual, parent);
		IncreasePathFlow(parent, flowIncreaseValue);
		counter++;
		Q.MakeEmpty();
	}
	List S, T;
	FindMinCut(_residual, visited, S, T);
	_maxFlow = SumEdgesFromStart(*_flow);
	IO::PrintResults(_maxFlow, S, T, counter, bfs);

	delete[] visited;
	//delete[] path;
	delete[] parent;
}

bool FordFulk::FindPathByBFS(const Graph &G, int *parent,  bool *visited, Queue &Q) const
{
	int size = G.GetSize();
	for (int i = 1; i < size; i++)
	{
		visited[i] = false;
		parent[i] = NULL;
	}
	visited[_s] = true;
	Q.NQ(_s);

	int currVertex, currNeighbor, prevVertex=0; 
	LNode *currNeighborNode;
	List *adjList;
	while (!Q.IsEmpty() && !visited[_t])
	{
		currVertex = Q.DQ();
		adjList = G.GetAdjList(currVertex);
		currNeighborNode = adjList->GetHead();
		while (currNeighborNode)
		{
			currNeighbor = currNeighborNode->GetData();
			if (!visited[currNeighbor])
			{
				visited[currNeighbor] = true;
				parent[currNeighbor] = currVertex;
				Q.NQ(currNeighbor);
			}
			currNeighborNode = currNeighborNode->GetNext();
		}
		delete adjList;

	}
	if (!visited[_t])
		return false; //no augmenting path found
	return true;
}


void FordFulk::IncreasePathFlow(const int *parent, int amount)
{
	int currVertex = _t;
	while (parent[currVertex])
	{
		_flow->IncreaseFlow(parent[currVertex], currVertex, amount);
		_residual->IncreaseFlow(currVertex, parent[currVertex], amount);
		currVertex = parent[currVertex];
	}
}

int FordFulk::FindMinEdgeInPath(const Graph &G ,const int *parent) const
{//Finds minimum edge in path given by parent array, from sink to source(from t to s)
	int minEdge, currEdgeValue, currVertex;

	if (parent[_t])
	{
		minEdge = G.GetEdgeValue(parent[_t], _t); //Initial value of minEdge
	}
	else
		return 0;//sink has no parent, so flow is 0
	currVertex = parent[_t];
	while (parent[currVertex])
	{
		currEdgeValue = G.GetEdgeValue(parent[currVertex], currVertex);
		if (currEdgeValue < minEdge)
			minEdge = currEdgeValue;
		currVertex = parent[currVertex];
	}
	
	return minEdge;
}
void FordFulk::FindMinCut(const Graph *G, bool *visited, List &S, List &T) const
{
	Queue Q;
	int size = G->GetSize();
	for (int i = 1; i < size; i++)
		visited[i] = false;
	visited[_s] = true;
	Q.NQ(_s);
	int currVertex, currNeighbor;
	LNode *currNeighborNode;
	List *adjList;
	while (!Q.IsEmpty())
	{
		currVertex = Q.DQ();
		adjList = G->GetAdjList(currVertex); //finds adjacent vertices of currVertex on G		
		currNeighborNode = adjList->GetHead();
		while (currNeighborNode)
		{
			currNeighbor = currNeighborNode->GetData();
			if (!visited[currNeighbor])
			{
				visited[currNeighbor] = true;
				Q.NQ(currNeighbor);
			}
			currNeighborNode = currNeighborNode->GetNext();
		}

		delete adjList;
	}
	//update lists
	for (int i = 1; i < size; i++)
	{
		if (visited[i])
		{
			S.Insert(i);//add to S list
		}
		else
			T.Insert(i);
	}
}
int FordFulk::SumEdgesFromStart(const Graph &G) const
{//Valid due to conservation of flow
	int maxFlow = 0;
	List* adjList = G.GetAdjList(_s);
	LNode *currVertex = adjList->GetHead();
	while (currVertex)
	{
		maxFlow += G.GetEdgeValue(_s, currVertex->GetData());
		currVertex = currVertex->GetNext();
	}
	return maxFlow;
}
void FordFulk::ResetFlow()
{
	_maxFlow = 0;
	_flow->MakeEmptyGraph(_flow->GetSize());
	*_residual = _capacity;

}

bool FordFulk::FindPathByGreed(const Graph &G, int *parent, PriorityQ &PQ, int *d) const
{//Saving path information in parent array
	
	int u, v, c;
	List *adjList;
	LNode *currNeighborNode;
	HNode currVertexNode;    //Heap node
	for (int i = 0; i < _size; i++)
	{
		d[i] = INT_MIN;
		parent[i] = NULL;
	}
	d[_s] = INT_MAX;
	while (!PQ.IsEmpty())
	{
		currVertexNode = PQ.DeleteMax();
		u = currVertexNode.GetData();
		adjList = G.GetAdjList(u);
		currNeighborNode = adjList->GetHead();
		while (currNeighborNode)
		{
			v = currNeighborNode->GetData();
			c = Min(d[u], G.GetEdgeValue(u, v));
			if (c > d[v])
			{
				d[v] = c;
				parent[v] = u;
				PQ.IncreaseKey(v, d[v]);
			}

			currNeighborNode = currNeighborNode->GetNext();
		}

	}

	if (!parent[_t])
		return false;
	return true;
}

void FordFulk::RunWithGreed()
{
	//Initializations:
	int *d = new int[_size];
	int *parent = new int[_size];
	int *path = new int[_size];
	int flowIncreaseValue, counter = 0;//Counts the number of augmenting pathes
	HNode *arr = new HNode[_size];
	HNode *arr2 = new HNode[_size]; //for resetting the priority queue to starting values
	HNode node;
	for (int i = 0; i < _size; i++)
	{
		arr[i].SetKey(INT_MIN); //all unvisited
		arr[i].SetData(i);        //vertex number
		arr2[i].SetKey(INT_MIN); 
		arr2[i].SetData(i);
		d[i] = INT_MIN;
		parent[i] = NULL;
	}
	arr[_s].SetKey(INT_MAX);
	arr2[_s].SetKey(INT_MAX);

	PriorityQ temp(arr, _size);//Same as BuildHeap
	PriorityQ PQ(arr2, _size);//Using 2 copies to restore initial information before each iteration

	//Calculations:
	while (FindPathByGreed(*_residual, parent, PQ, d))
	{
		flowIncreaseValue = FindMinEdgeInPath(*_residual, parent);
		IncreasePathFlow(parent, flowIncreaseValue);
		counter++;
		PQ = temp;//Reset queue for next use
	}

	//Finding MinCut and maxFlow
	List S, T;
	Queue Q;
	bool *visited = new bool[_size];//for finding MinCut
	for (int i = 0; i < _size; i++)
		visited[i] = false;
	FindMinCut(_residual, visited, S, T);
	_maxFlow = SumEdgesFromStart(*_flow);

	IO::PrintResults(_maxFlow, S, T, counter, greed);
	delete[] d;
	delete[] visited;
	delete[] parent;
	delete[] path;
	delete[] arr;
	delete[] arr2;

}

int FordFulk::Min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}