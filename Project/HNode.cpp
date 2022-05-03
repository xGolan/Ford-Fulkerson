#include "HNode.h"
HNode::HNode()
{
	_data = 0;
	_key = 0;
}
HNode::HNode(int data, int key)
{
	_data = data;
	_key = key;
}
int HNode::GetData() const
{
	return _data;
}
int HNode::GetKey() const
{
	return _key;
}
void HNode::SetData(int data)
{
	_data = data;
}
void HNode::SetKey(int key)
{
	_key = key;
}
bool HNode::operator>(const HNode &node) const
{
	if (_key > node.GetKey())
		return true;
	return false;
}
bool HNode::operator<(const HNode &node) const
{
	if (_key < node.GetKey())
		return true;
	return false;
}
bool HNode::operator>(int num) const
{
	if (_key > num)
		return true;
	return false;
}
bool HNode::operator<(int num) const
{
	if (_key < num)
		return true;
	return false;
}
const HNode& HNode::operator=(const HNode &node)
{
	if (this != &node)
	{
		_data = node.GetData();
		_key = node.GetKey();
	}
	return *this;
}