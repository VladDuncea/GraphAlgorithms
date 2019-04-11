#include "DisjointSet.h"


DisjointSet::DisjointSet(int n)
{
	Node nd;
	nd.depth = 0;
	nd.root = -1;
	for (int i=0;i<n;i++)
	{
		privNodes.push_back(nd);
	}
		
}

DisjointSet::~DisjointSet()
{
}

int DisjointSet::getFather(int x)
{
	//If the node is not alone
	if (privNodes[x].root != -1)
	{
		//Re link the node to the top
		//Road compression
		privNodes[x].root = getFather(privNodes[x].root);
		//Return the father
		return privNodes[x].root;
	}
	return x;
}

void DisjointSet::link(int a, int b)
{
	//By rank
	int fatherA, fatherB;
	//Get 
	fatherA = getFather(a);
	fatherB = getFather(b);
	//link optimised(the small subtree is linked to the big subtree)
	if (privNodes[a].depth == privNodes[b].depth)
	{
		privNodes[b].root = a;
		privNodes[a].depth++;
	}
	else if (privNodes[a].depth < privNodes[b].depth)
		privNodes[a].root = b;
	else
		privNodes[b].root = a;

	//Heavy path decomposition
}

void DisjointSet::test()
{
	for (auto e : privNodes)
		std::cout << e.root << " ";
}
