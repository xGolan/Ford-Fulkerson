#ifndef __IO_H
#define __IO_H

#include "Graph.h"
#include <fstream>
#include <iostream>
//Class for Input and Output handling
class Graph;
class IO {
private:
	ifstream _fp;


	void NewLineCheck();
	void SameLineCheck();
	void ReadInt(int &n);
	void ValidateInitial(int n, int m, int s, int t) const;
public:
	IO(char *fileName);
	~IO();

	//Input
	void InputInitial(int &n, int &m, int &s, int &t);
	void InputEdges(Graph &G, int n, int m);
	bool IsDigit(char c);

	//Ouput
	static void SourceIsSinkMSG();
	static void InputInvalidMSG();
	static void PrintResults(int flow, const List &S, const List &T, int counter, bool greedy);
	static void QueueEmptyMSG();
	static void EdgeExistMSG(int u, int v);
	static void EmptyQueueMSG();
	static void FullQueueMSG();
	static void GraphSelfLoopMSG(int v);
	static void GraphNegativeEdgeMSG(int u, int v);
	static void GraphAssignmentMSG();
};
#endif