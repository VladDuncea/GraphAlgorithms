#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "DisjointSet.h"
using namespace std;

struct edge
{
	int x, y, c;
};

bool cmp(edge a,edge b)
{
	return a.c < b.c;
}

void kruskal(vector<edge> edges,int n)
{
	//Create the disjoint set
	DisjointSet dj(n);
	sort(edges.begin(), edges.end(), cmp);
	vector<edge> answer;
	for (auto e : edges)
	{
		if (dj.getFather(e.x) != dj.getFather(e.y))
		{
			dj.link(dj.getFather(e.x), dj.getFather(e.y));
			answer.push_back(e);
		}
	}
	//print result on screen
	for (auto e : answer)
	{
		cout << (char) (e.x+'a') << " "<< (char) (e.y+'a')<<endl;
	}
}

//PRIM
/*
void prim(vector<edge> edges)
{
	vector<bool> vizitat(n + 1, 0);
	vizitat[1] = 1;
	vector<edge> answer;
	edge chosen;
	priority_queue<edge> Q;
	for (edge e : edges)
		if (vizitat[e.x] == 1 || vizitat[e.y] == 1)
			Q.push(e);

	for (int i = 0; i < n; i++)
	{
		int mn = INFINITY;
		//Optiunea 1
		for (auto e : edges)
		{
			if (vizitat[e.x] + vizitat[e.y] == 1 && e.c<mn)
			{
					mn = e.c;
					chosen = e;
			}
		}
		//Optiunea 2 coada de prioritati
		while (!Q.empty())
		{
			chosen = Q.top(); 
			Q.pop();
			if (vizitat[chosen.x] + vizitat[chosen.y] == 1)
			{
				if (vizitat[chosen.x] == 0)
					swap(chosen.x, chosen.y);
				for (auto e : adiac[chosen.y])
					Q.push(e);
			}
			vizitat[chosen.x] = vizitat[chosen.y] = 1;
			answer.push_back(chosen);

		}

		//Final
		vizitat[chosen.x] = vizitat[chosen.y] = 1;
		answer.push_back(chosen);
	}
	
}
*/
int main()
{
	ifstream fin;
	fin.open("date.in");
	int n,m;
	fin >> n >> m;
	vector<edge> edges;
	for (int i = 0; i < m; i++)
	{
		int x, y, c;
		fin >> x >> y >> c;
		edges.push_back(edge{ x,y,c });
	}
	kruskal(edges,n);

}