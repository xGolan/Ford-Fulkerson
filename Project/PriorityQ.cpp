#include "PriorityQ.h"
#include "IO.h"

//change to max priority queue
//change heap methods to private
PriorityQ::PriorityQ()
{
	_arr = nullptr;
	_maxSize = 0;
	_heapSize = 0;
	_allocated = 0;
	_location = nullptr;
}
PriorityQ::PriorityQ(int size)
{
	_arr = new HNode[size];
	_maxSize = size;
	_heapSize = 0;
	_allocated = 1;
	int *_location = new int[_maxSize]; //_location[i] saves the index in which vertex i is present in the heap array

}


PriorityQ::PriorityQ(HNode *A, int size)// same as buildHeap
{//BuildHeap
	_heapSize = _maxSize = size;
	_arr = A;
	_allocated = 0;
	_location = new int[_maxSize];
	for (int i = 0; i < _maxSize; i++)
	{
		_location[i] = i;
	}
	for (int i = size / 2 - 1; i >= 0; i--)
		FixHeap(i);

}

PriorityQ::~PriorityQ()
{
	if (_allocated)
		delete[] _arr;
	_arr = NULL;
	if(_location)
		delete[] _location;
}

int PriorityQ::Parent(int node)
{
	return (node - 1) / 2;
}

int PriorityQ::Left(int node)
{
	return (2 * node + 1);
}
int PriorityQ::Right(int node)
{
	return (2 * node + 2);
}

void PriorityQ::FixHeap(int index)
{
	int max;
	int left = Left(index);
	int right = Right(index);

	if (left<_heapSize && _arr[left]>_arr[index])
		max = left;
	else 
		max = index;
	if (right <_heapSize && _arr[right]>_arr[max])
		max = right;

	if (max != index)
	{
		//swap max with index
		
		HNode temp = _arr[index];
		_arr[index] = _arr[max];
		_arr[max] = temp;

		//Swap location information
		int loc = _location[_arr[index].GetData()];
		_location[_arr[index].GetData()] = _location[_arr[max].GetData()];
		_location[_arr[max].GetData()] = loc;

		FixHeap(max);
	}

}

HNode PriorityQ::DeleteMax()
{
	if (_heapSize < 1)
	{
		IO::EmptyQueueMSG();
		exit(1);
	}
	HNode max = _arr[0];
	_heapSize--;
	_arr[0] = _arr[_heapSize];
	_location[_arr[_heapSize].GetData()] = 0; //Update location
	FixHeap(0);
	return max;
}

void PriorityQ::Insert(HNode node)
{
	if (_heapSize == _maxSize)
	{
		IO::FullQueueMSG();
		exit(1);
	}
	int i = _heapSize;
	_heapSize++;
	while (i > 0 && _arr[Parent(i)] < node)
	{
		_location[i] = _location[Parent(i)];
		_arr[i] = _arr[Parent(i)];
		i = Parent(i);
	}
	_location[i] = _location[node.GetData()];
	_arr[i] = node;
}


int PriorityQ::Max() const
{
	return _arr[0].GetData();
}

bool PriorityQ::IsEmpty() const
{
	if (_heapSize > 0)
		return false;
	return true;
}
void PriorityQ::MakeEmpty()
{
	_heapSize = 0;
}

void PriorityQ::IncreaseKey(int vertex, int newKey)
{
	int currLoc= _location[vertex];
	_arr[_location[vertex]].SetKey(newKey);
	HNode tempNode;
	while ((currLoc > 0) && _arr[Parent(currLoc)] < _arr[currLoc])
	{

		LocationUpdate(currLoc);
		//Swap nodes
		tempNode = _arr[currLoc];
		_arr[currLoc] = _arr[Parent(currLoc)];
		_arr[Parent(currLoc)] = tempNode;
		
		currLoc = Parent(currLoc);
	}
}

const PriorityQ& PriorityQ::operator=(const PriorityQ& Q)
{
	if (this != &Q)
	{
		if (_allocated)
			delete[] _arr;
		_heapSize = Q._heapSize;
		_maxSize = Q._maxSize;
		_allocated = 1;
		_arr = new HNode[_heapSize];
		for (int i = 0; i < _heapSize; i++)
		{
			_arr[i] = Q._arr[i];
			_location[i] = Q._location[i];
		}
	}
	return *this;
}
void PriorityQ::LocationUpdate(int currLoc)
{//Swaps the location of currLoc with its parent
	int tempLoc = currLoc;
	_location[_arr[currLoc].GetData()] = _location[_arr[Parent(currLoc)].GetData()];
	_location[_arr[Parent(currLoc)].GetData()] = tempLoc;
}