#include "LNode.h"

LNode::LNode(int data)
{
	_data = data;
	_next = NULL;
}
LNode::LNode(int data, LNode *next)
{
	_data = data;
	_next = next;
}
LNode::~LNode()
{

}
void LNode::SetData(int data)
{
	_data = data;
}
void LNode::SetNext(LNode *next)
{
	_next = next;
}
int LNode::GetData() const
{
	return _data;
}
LNode *LNode::GetNext() const
{
	return _next;
}