#ifndef __QUEUE_H
#define __QUEUE_H
#include "LNode.h"
#include "IO.h"

class Queue {
private:
	LNode *_head;
	LNode *_tail;


public:

	
	Queue();
	~Queue();
	
	void MakeEmpty();
	bool IsEmpty() const;
	void NQ(int x);
	int DQ();
	

};



#endif