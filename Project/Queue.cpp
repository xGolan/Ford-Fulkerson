
#include "Queue.h"

Queue::Queue()
{
	_head = nullptr;
	_tail = nullptr;
}
Queue::~Queue()
{
	MakeEmpty();
}

void Queue::MakeEmpty()
{
	LNode *temp, *currNode = _head;

	while (currNode)
	{
		temp = currNode->GetNext();
		delete currNode;
		currNode = temp;
	}
	_head = _tail = nullptr;

}

bool Queue::IsEmpty() const
{
	return(!_head);
}
void Queue::NQ(int x)
{
	LNode *newNode = new LNode(x);
	if (IsEmpty())
	{
		_head = _tail = newNode;
	}
	else
	{
		_tail->SetNext(newNode);
		_tail = newNode;
	}

}
int Queue::DQ()
{
	LNode temp(*_head);
	if (IsEmpty())
	{
		IO::QueueEmptyMSG();
		exit(1);
	}
	delete _head;
	_head = temp.GetNext();
	if (!_head)
		_tail = nullptr;
	return temp.GetData();
}