//Golan Aharoni - 205377880
/*
=================================================================================================================
PROGRAM INSTRUCTIONS:
The program opens an input txt file which its name is passed to the main function.
The program translate the text from the input file into a graph, and then calculates the maximum flow possible
  with Ford-Fulkerson algorithm. The program will use Ford-Fulkerson algorithm twice, first by choosing the
  augmenting path by BFS(Edmonds-Karp), then by choosing the augmenting path which increases the current flow the most.


Input:  - txt file name (The file contains graph information).

Output: - Maximum flow.
		- The minimum cut between the vertices (shows the vertices in each side of the cut).
		- Amount augmentations that have been made to find the maximum flow.
=================================================================================================================
*/


#include "FordFulk.h"
#include <fstream>
#include "IO.h"
#include <string.h>


int main(int argc, char* argv[])
{
	int s, t, n, m;
	char* inputFileName = _strdup(argv[1]);
	IO InputTranslator(inputFileName);
	InputTranslator.InputInitial(n, m, s, t);

	Graph G(n + 1);  //Row 0 and column 0 will be ignored in this program
	G.MakeEmptyGraph(n + 1);

	InputTranslator.InputEdges(G, n, m);

	FordFulk Algo(G, s, t);
	Algo.CalcMaxFlow();

	delete[] inputFileName;
}
