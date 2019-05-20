#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include "DisjointSet.h"
using namespace std;

struct edge_weight
{
	int x, y, c;
	bool operator<(const edge_weight& rhs) const
	{
		return c > rhs.c;
	}
};

struct edge
{
	int x, y;
};

struct node
{
	int degree;
	list<edge_weight> edges;
};

bool cmp(edge_weight a, edge_weight b)
{
	return a.c < b.c;
}

#pragma region Havel-Hakimi

bool cmphh(pair<int, int>& a, pair<int, int>& b)
{
	return a.second > b.second;
}


vector <pair<int, int>> sort_interclass(vector <pair<int, int>> a, vector <pair<int, int>> b)
{
	vector<pair<int, int>> aux;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size())
	{
		if (a[i].second > b[j].second)
		{
			aux.push_back(a[i++]);
		}
		else
		{
			aux.push_back(b[j++]);
		}
	}

	while (i < a.size())
		aux.push_back(a[i++]);

	while (j < b.size())
		aux.push_back(b[j++]);

	return aux;
}

vector<edge> havel_hakimi(vector<int> seq)
{
	//Necesary conditions
	int n = seq.size();
	int sum = 0;
	for (auto x : seq)
	{
		//Check for negative degree
		if (x<0 || x>n - 1)
			return vector<edge>();
		sum += x;
	}

	//Check for odd sum
	if (sum % 2 != 0)
		return vector<edge>();

	//Try to make graph

	vector<edge> answer;
	//Create a pair of sequence +node id
	vector<pair<int, int>> vpair;
	int id = 0;
	for (auto x : seq)
	{
		vpair.push_back({ id,x });
		id++;
	}
	//Sort sequence
	sort(vpair.begin(), vpair.end(), cmphh);

	while (!vpair.empty())
	{
		//All deegrees are 0
		if (vpair[0].second == 0)
			return answer;

		for (int i = 1; i <= vpair[0].second; i++)
		{
			//Can't create graph
			if (vpair[i].second == 0)
				return vector<edge>();

			vpair[i].second--;
			answer.push_back({ vpair[0].first,vpair[i].first });
		}

		//sort interclasare
		vpair = sort_interclass(vector<pair<int, int>>(vpair.begin() + 1, vpair.begin() + vpair[0].second + 1), vector<pair<int, int>>(vpair.begin() + vpair[0].second + 1, vpair.end()));
	}
	return answer;
}

#pragma endregion

#pragma region Prufer

/*
vector<int> codifPrufer(vector<edge> edges)
{
	return ;
}
*/
vector<edge> decodifPrufer(vector<int> codif)
{
	//Num of nodes 
	int n = codif.size() + 2;
	//Vector of edges
	vector<edge> answer;
	//Vector of degree
	vector<int> deg;
	deg.resize(n,1);

	for (int i = 0; i < n-2; i++)
	{
		deg[codif[i]]++;
	}

	int i, last,p;
	i = p = 0;
	last = -1;
	while(p < n - 2)
	{
		if (deg[i] == 1)
		{
			answer.push_back({ codif[p], i });
			deg[i] = 0;
			deg[codif[p]]--;
			//Set i back 
			if (last != -1)
			{
				i = last;
				last = -1;
			}

			//Check if we have a new 1 degree
			if (deg[codif[p]] == 1)
			{
				last = i;
				i = codif[p]-1;
			}
			p++;
		}
		i++;
		
	}

	//Add the last edge
	answer.push_back({ i,n - 1 });

	return answer;
}

#pragma endregion

#pragma region Kruskal
vector<edge_weight> kruskal(vector<edge_weight> edges, int n)
{
	//Create the disjoint set
	DisjointSet dj(n);
	sort(edges.begin(), edges.end(), cmp);
	vector<edge_weight> answer;
	int select = 0;
	for (auto e : edges)
	{
		if (dj.getFather(e.x) != dj.getFather(e.y))
		{
			dj.link(dj.getFather(e.x), dj.getFather(e.y));
			answer.push_back(e);
			select++;
			if (select == n)
				break;
		}
	}
	return answer;
}

#pragma endregion

#pragma region Prim
vector<edge_weight> prim(vector<edge_weight> edges,int n)
{
	vector<node> nodes;
	nodes.resize(n);
	for (auto e : edges)
	{
		nodes[e.x].edges.push_back(e);
		nodes[e.y].edges.push_back(e);
	}

	vector<bool> vizitat(n, 0);
	vizitat[0] = 1;
	vector<edge_weight> answer;
	edge_weight chosen= edge_weight();
	priority_queue<edge_weight> Q;
	for (edge_weight e : edges)
		if (vizitat[e.x] == 1 || vizitat[e.y] == 1)
			Q.push(e);

	while (answer.size() < n-1)
	{
		chosen = Q.top();
		Q.pop();
		if (vizitat[chosen.x] + vizitat[chosen.y] == 1)
		{
			if (vizitat[chosen.x] == 0)
				swap(chosen.x, chosen.y);
			for (auto e : nodes[chosen.y].edges)
				Q.push(e);

			vizitat[chosen.x] = vizitat[chosen.y] = 1;
			answer.push_back(chosen);
		}
	}
	return answer;
}
#pragma endregion

int main()
{
	///Havel Hakimi
	/*
	cout << "HavelHakimi \n";
	vector<edge> answ = havel_hakimi({ 3,4,2,1,3,4,1,2 });
	*/

	///Prufer
	cout << "Prufer \n";
	vector<edge> answ = decodifPrufer({ 6,3,2,0,3,5,6,0 });
	if (answ.empty())
	{
		cout << "Secventa incorecta\n";
	}
	else
	{
		for (auto e : answ)
			cout << e.x + 1 << " " << e.y + 1 << "\n";
	}
	

	ifstream fin;
	fin.open("date2.in");
	int n, m;
	fin >> n >> m;
	vector<edge_weight> edges;
	vector<edge_weight> answer;
	for (int i = 0; i < m; i++)
	{
		int x, y, c;
		fin >> x >> y >> c;
		edges.push_back(edge_weight{ x,y,c });
	}

	///Kruskal
	//cout << "Kruskal \n";
	//answer = kruskal(edges,n);

	///Prim
	cout << "Prim \n";
	answer = prim(edges, n);


	//print result on screen
	for (auto e : answer)
	{
		cout << e.x+1 << " " << e.y + 1 << endl;
	}
}

