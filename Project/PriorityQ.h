#ifndef __PRIORITYQ_H
#define __PRIORITYQ_H
#include "HNode.h"

class PriorityQ {
private:
	HNode* _arr;
	int _maxSize;
	int _heapSize;
	int _allocated;
	int *_location;// location[i] holds the index of the node with data i in the heap array
	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void FixHeap(int index);
	void LocationUpdate(int currLoc);


public:
	PriorityQ();
	PriorityQ(int size = 0);
	PriorityQ(HNode *A, int n);
	~PriorityQ();
	void MakeEmpty();
	bool IsEmpty() const;
	int Max() const;
	HNode DeleteMax();
	void Insert(HNode node);
	void IncreaseKey(int vertex, int newKey);
	
	const PriorityQ& operator=(const PriorityQ& heap);
};



#endif