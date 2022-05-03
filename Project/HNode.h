#ifndef __HNODE_H
#define __HNODE_H
//HNode - For Priority Queue

class HNode {
private:
	int _data;
	int _key;
public:
	HNode();
	HNode(int data, int key);
	int GetData() const;
	int GetKey() const;
	void SetData(int data);
	void SetKey(int key);
	bool operator>(const HNode &node) const;
	bool operator>(int num) const;
	bool operator<(const HNode &node) const;
	bool operator<(int num) const;
	const HNode& operator=(const HNode &node);
};

#endif