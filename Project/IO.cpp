#include "IO.h"


IO::IO(char *fileName)
{
	_fp = ifstream(fileName);
}
IO::~IO()
{
	_fp.close();
}
void IO::InputInitial(int &n, int &m, int &s, int &t)
{
	ReadInt(n);
	ReadInt(m);
	NewLineCheck();
	ReadInt(s);
	NewLineCheck();
	ReadInt(t);
	ValidateInitial(n, m, s, t);

}
void IO::InputEdges(Graph &G, int n, int m)
{
	int i, j, c;
	char currChar; //Input validity tester
	for (int loop = 0; loop < m; loop++)
	{
		NewLineCheck();
		ReadInt(i);
		SameLineCheck();
		ReadInt(j);
		SameLineCheck();
		ReadInt(c);
		
		G.AddEdge(i, j, c);
	}

	if (_fp >> currChar)
	{//Input file has more information than stated
		InputInvalidMSG();
		exit(1);
	}
}

void IO::InputInvalidMSG()
{
	cout << "Invalid input!\n";
}

void IO::PrintResults(int flow, const List &S, const List &T, int counter, bool greedy)
{
	if (greedy)
		cout << "Greedy method:" << endl;
	else
		cout << "BFS method:" << endl;
	cout << "Max flow = " << flow << endl;
	cout << "Min cut: S =" << S<<". ";
	cout << "T =" << T << endl;
	cout << "Number of iterations = " << counter << endl << endl;
}
void IO::QueueEmptyMSG()
{
	cout << "Error! Queue is empty.\n";
}
void IO::EdgeExistMSG(int u, int v)
{
	cout << "Invalid input! Edge ("<<u<<", "<<v<<") already exist.\n" << endl;
}
void IO::EmptyQueueMSG()
{
	cout << "Error! Queue is empty.\n";
}
void IO::FullQueueMSG()
{
	cout << "Error! Queue is full.\n";
}
void IO::GraphSelfLoopMSG(int v)
{
	cout << "Invalid input! Graph has a self loop at vertex " << v <<"."<< endl;
}
void IO::GraphNegativeEdgeMSG(int u, int v)
{
	cout << "Invalid input! Edge (" << u << ", " << v << ") "<<"is negative." << endl;
}
void IO::GraphAssignmentMSG()
{
	cout << "Error! Cannot duplicate graph, graphs are different sizes\n";
}
void IO::NewLineCheck()
{
	char currChar;
	if (!(_fp.get(currChar)))
	{
		InputInvalidMSG();
		exit(1);
	}
	while (currChar == ' ')
	{
		if (!(_fp.get(currChar)))
		{
			InputInvalidMSG();
			exit(1);
		}
	}
	if (currChar != '\n')
	{
		InputInvalidMSG();
		exit(1);
	}
}
void IO::ReadInt(int &n)
{//Tries to read int from current position in file, exits with a message if failed to read int
	if (!(_fp >> n))
	{
		InputInvalidMSG();
		exit(1);
	}
}
bool IO::IsDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
void IO::ValidateInitial(int n, int m, int s, int t) const
{
	if (n <= 0 || m < 0 || s<0 || t<0 || s>n || t>n)
	{
		InputInvalidMSG();
		exit(1);
	}
}
void IO::SameLineCheck()
{
	char currChar;
	if (!(_fp.get(currChar)))
	{
		InputInvalidMSG();
		exit(1);
	}
	while (currChar == ' ')
	{
		if (!(_fp.get(currChar)))
		{
			InputInvalidMSG();
			exit(1);
		}
	}
	if (!IsDigit(currChar))
	{
		InputInvalidMSG();
		exit(1);
	}
	_fp.unget();
}
void IO::SourceIsSinkMSG()
{
	cout << "Source is also the sink, infinite flow\n";
}