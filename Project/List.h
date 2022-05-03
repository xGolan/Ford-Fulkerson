#ifndef __LIST_H
#define __LIST_H
#include "LNode.h"

class List
{
private:
	LNode *_head, *_tail;
public:
	List();
	~List();
	void Insert(int data);
	LNode *GetHead() const;
	LNode *GetTail() const;
	void SetHead(LNode *newHead);
	void SetTail(LNode *newTail);
	const List& operator=(const List& list);
	void MakeEmpty();
	friend ostream& operator<<(ostream& os, const List &L)
	{
		LNode *currListNode = L._head;
		while (currListNode->GetNext())
		{
			os << " " << *currListNode <<",";
			currListNode = currListNode->GetNext();
		}
		os <<" "<< *currListNode;
		return os;
	};
};
#endif