#pragma once
#include <vector>
#include <iostream>
class DisjointSet
{
	typedef struct n
	{
		int root,depth;
	}Node;
	std::vector<Node> privNodes;

public:
	DisjointSet(int n);
	~DisjointSet();
	

	int getFather(int x);
	void link(int a, int b);
	void test();
};