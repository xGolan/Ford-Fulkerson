#include "Graph.h"
Graph::Graph()
{
	_size = 0;
	_graph = nullptr;
	_allocated = false;
}
Graph::Graph(int n)
{
	_size = n;
	_graph = new int*[n+1];
	_allocated = true;
	for (int i = 0; i <= n; i++)
	{
		_graph[i] = new int[n+1];		
	}
	
}
Graph::Graph(const Graph &G)
{
	_size = G.GetSize();
	_graph = new int*[_size];
	_allocated = true;
	for (int i = 0; i < _size; i++)
	{
		_graph[i] = new int[_size];

	}
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_graph[i][j] = G._graph[i][j];
		}
	}
}
Graph::Graph(int** mat, int n)
{
	_allocated = false;
	_graph = mat;
}

Graph::~Graph()
{// changed to delete[]
	if (_allocated) {
		for (int i = 0; i < _size; i++)
		{
			delete[] _graph[i];

		}
		delete[] _graph;
	}
}
void Graph::MakeEmptyGraph(int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			_graph[i][j] = NULL;
		}
}

bool Graph::IsAdjacent(int u, int v) const
{
	if (_graph[u][v]>0)
		return true;
	return false;
}

List* Graph::GetAdjList(int u) const //Need to check if using a list is a must or not
{                             //Need to delete after use!
	List* list = new List();
	int curr = 0;
	for (int i = 1; i < _size; i++)
	{
		if(_graph[u][i]>0)
			list->Insert(i);
	}
	return list;
}

void Graph::AddEdge(int u, int v, int c)
{
	if (u<1 || u>_size || v<1 || v>_size || c <= 0|| u==v)
	{
		IO::InputInvalidMSG();
		exit(1);
	}
	if (_graph[u][v] > 0)
	{
		IO::EdgeExistMSG(u, v);
		exit(1);
	}

	_graph[u][v] = c;
}
void Graph::RemoveEdge(int u, int v)
{
	if(u>=0 && v>=0 && u<_size && v<_size)
		_graph[u][v] = 0;
}


int Graph::GetSize() const
{
	return _size;
}

const Graph& Graph::operator=(const Graph& G)
{
	if (this != &G)
	{
		if (_size == G._size)
		{
			_size = G._size;
			for (int i = 1; i < G._size; i++)
			{
				for (int j = 1; j < G._size; j++)
				{
					_graph[i][j] = G._graph[i][j];
				}
			}
		}
		else
		{
			IO::GraphAssignmentMSG();
			exit(1);
		}
	}
	return *this;
}
void Graph::IncreaseFlow(int u, int v, int value)
{
	_graph[u][v] += value;
	_graph[v][u] -= value; //Skew Symmetry
}



int Graph::GetEdgeValue(int u, int v) const
{
	if(u>0 && v>0 && u< _size && v< _size)
		return _graph[u][v];
	return 0;

}

void Graph::SetAllocation(bool b)
{
	_allocated = b;
}
