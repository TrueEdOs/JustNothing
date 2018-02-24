/*
	Cruscal algotithm with dsu
*/

#include<bits/stdc++.h> 
using namespace std;

const int maxn = 1000005;

struct edge
{
	int x, y, len;
	edge(int x, int y, int len):x(x), y(y), len(len){};
	bool operator<(edge a)
	{
		return this->len < a.len;
	}
};
vector<edge> edges;
vector<int> anc, sz;
int n, m;

void initializing()
{
	cin >> n >> m;
	for(int i = 0; i < m; i++)
	{
		int x, y, len;
		cin >> x >> y >> len;
		x--;y--;
		edges.push_back( *(new edge(x, y, len)));
	}
	
	sort(edges.begin(), edges.end());
	sz.assign(n, 1);
	anc.resize(n);
	for(int i = 0; i < n; i++)
		anc[i] = i;
}

int getAnc(int v)
{
	return anc[v] = (v == anc[v] ? v: getAnc(anc[v]));
}

bool unionSet(edge x)
{
	int a = getAnc(x.x), b = getAnc(x.y);
	if(a == b)
		return false;
	if(sz[a] < sz[b])
		swap(a, b);
	
	anc[b] = a;
	sz[a] += a;
	return true;
}
vector<edge> solve()
{
	vector<edge> ans;
	initializing();
	for(int i = 0; i < m; i++)
		if(unionSet(edges[i]))
			ans.push_back(edges[i]);
	return ans;
}

int main() 
{
	//freopen("input", "r", stdin);
	ios_base::sync_with_stdio(false);
	solve();
	return 0;
}
