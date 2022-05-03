#ifndef __LNODE_H
#define __LNODE_H
#include <iostream>
using namespace std;

//LNode - For List
class LNode {
private:
	int _data;
	LNode *_next;
public:
	LNode(int data);
	LNode(int data, LNode *next);
	~LNode();
	LNode *GetNext() const;
	int GetData() const;
	void SetData(int data);
	void SetNext(LNode *next);
	friend ostream& operator<<(ostream& os, const LNode &N)
	{
		os << N._data;
		return os;
	};
	
	
};
#endif