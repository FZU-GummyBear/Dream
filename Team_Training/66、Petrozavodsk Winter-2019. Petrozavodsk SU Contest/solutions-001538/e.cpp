#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int> > g[100005];
set<pair<int, int> > s[100005];
int sa[100005];
int sb[100005];

set<pair<int, int> > ans_a[100005];
set<pair<int, int> > ans_b[100005];


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	double st = clock();
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back({i+1, b});
		g[b].push_back({i+1, a});
	}
	
	//need 3 edge!!!!
	int a, b;
	cin >> a >> b;	
	fill(sa, sa + n + 1, -1);
	fill(sb, sb + n + 1, -1);
	for(auto x : g[a])
		sa[x.second] = x.first;
	for(auto x : g[b])
		sb[x.second] = x.first;


	for(int i = 1; i <= n; i++)
		if(i != a && i != b)
			for(auto x : g[i])
				if(sa[x.second] != -1 && x.second != a && x.second != b){
						ans_a[i].insert({max(x.first, sa[x.second]), x.second});
						if(ans_a[i].size() == 4)
							ans_a[i].erase(--ans_a[i].end());
				}

	for(int i = 1; i <= n; i++)
		if(i != a && i != b)
			for(auto x : g[i])
				if(sb[x.second] != -1 && x.second != a && x.second != b){
						ans_b[i].insert({max(x.first, sb[x.second]), x.second});
						if(ans_b[i].size() == 4)
							ans_b[i].erase(--ans_b[i].end());
				}


	int ans = m+1;
	for(int v = 1; v <= n; v ++)
		for(auto u : g[v])
		{
			for(auto ua : ans_a[u.second])
				for(auto vb : ans_b[v])
				{
					//cerr << v << " " << u.second << " " << ua.second << " " << vb.second << "\n";
					//cerr << " -> " << max(u.first, max(ua.first, vb.first)) << endl;
					if(ua.second != vb.second && ua.second != v && vb.second != u.second)
					{
						ans = min(ans, max(u.first, max(ua.first, vb.first)));	
						
					}
				}
		}          	

	if(ans != m+1)
		cout << ans << "\n";
	else
		cout << -1 << "\n";
   	cerr << "time = " << (double)(clock() - st)/ CLOCKS_PER_SEC << endl;
	
	return 0;
}