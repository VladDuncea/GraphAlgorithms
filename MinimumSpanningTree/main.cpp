#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge
{
	int x, y, c;
};

bool cmp(edge a,edge b)
{
	return a.c < b.c;
}

void treeUnion(int x,int y)
{
	//By size
	if (count(x) < count(y))
		swap(x, y);
	cnt[x] += cnt[y];
	father[y] = x;
	//Todo by rank
	//Heavy path decomposition
}

int findRoot(int x)
{
	if (father[x] != x)
	{
		father[x] = findRoot(father[x]);
		return father[x];
	}
	return x;
}

void kruskal(vector<edge> edges)
{
	sort(edges.begin(), edges.end(), cmp);
	vector<edge> answer;
	for (auto e : edges)
	{
		//if (conex(e.x, e.y))
		//	answer.push_back(e);
		if (findRoot(e.x) != findRoot(e.y))
		{
			treeUnion(findRoot(e.x), findRoot(e.y));
			answer.push_back(e);
		}
	}
}

//PRIM

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

int main()
{

}