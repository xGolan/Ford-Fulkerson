#include "List.h"

List::List()
{
	_head = nullptr;
	_tail = nullptr;

}
List::~List()
{
	MakeEmpty();
}
void List::Insert(int data)
{
    LNode *newNode = new LNode(data);
	if (!_head)
	{
		_head = newNode;
		_tail = newNode;
	}
	else
	{
		_tail->SetNext(newNode);
		_tail = newNode;
	}
}
LNode *List::GetHead() const
{
	return _head;
}
LNode *List::GetTail() const
{
	return _tail;
}
void List::SetHead(LNode *newHead)
{
	_head = newHead;
}
void List::SetTail(LNode *newTail)
{
	_tail = newTail;
}
const List& List::operator=(const List& list)
{
	_head = list.GetHead();
	_tail = list.GetTail();
	return *this;
}
void List::MakeEmpty()
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


