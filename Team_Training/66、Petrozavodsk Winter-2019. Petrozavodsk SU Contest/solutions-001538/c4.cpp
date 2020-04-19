#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 260;
const int MAXL = 1010;
int N;
int L;
char G[MAXL][MAXL];

const int MAXV = MAXN * MAXN * 4;
int V;
int vertInd[MAXL][MAXL];
int vertX[MAXV];
int vertY[MAXV];

const int MAXE = MAXV * 3;
int E;
int edgeInd[MAXL][MAXL];
pair<int, int> edges[MAXE];
vector<int> deletes[MAXE];

const int S = 1 << 21;
int T;
vector<int> ops[S * 2];

int sources[3][2];

int par[MAXV];
int sz[MAXV];
void initDSU() {
	for (int i = 0; i < V; i++) par[i] = -1, sz[i] = 1;
}
int getPar(int a) {
	return (par[a] == -1) ? a : getPar(par[a]);
}
int solve(int i) {
	// insert the things
	vector<int> undo;
	for (int e : ops[i]) {
		int u = getPar(edges[e].first);
		int v = getPar(edges[e].second);
		if (u == v) continue;
		if (sz[u] > sz[v]) swap(u, v);
		sz[v] += sz[u];
		par[u] = v;
		undo.push_back(u);
	}

	int res;
	if (i >= S) {
		bool good = (i-S < T);
		for (int z = 0; good && z < 3; z++) {
			if (getPar(sources[z][0]) != getPar(sources[z][1])) {
				good = false;
				break;
			}
		}
		res = good;
	} else {
		res = solve(2*i) + solve(2*i+1);
	}

	reverse(undo.begin(), undo.end());
	for (int u : undo) {
		int v = par[u];
		sz[v] -= sz[u];
		par[u] = -1;
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	cin >> N;
	L = 4 * N - 1;
	{ string trash; getline(cin, trash); }
	for (int i = 0; i < L; i++) {
		string s; getline(cin, s);
		for (int j = 0; j < L; j++) {
			G[i][j] = s[j];
		}
		G[i][L] = '\0';
	}

	memset(vertInd, -1, sizeof(vertInd));
	for (int i = 0; i < L; i++) {
		int j = 0;
		while (G[i][j] == ' ') {
			G[i][j] = 'X';
			G[i][L-j-1] = 'X';
			j++;
		}

		int r = L-1-j;

		if (G[i][j] == '_') {
			j += 2;
		} else if (G[i][j] == '/') {
			j ++;
		} else if (G[i][j] == '\\') {
			j += 3;
		} else assert(false);

		for (; j <= r; j += 4) {
			vertInd[i][j] = V++;
			vertX[vertInd[i][j]] = i;
			vertY[vertInd[i][j]] = j;
			char c = G[i][j];
			if ('A' <= c && c <= 'Z') {
				sources[c - 'A'][0] = vertInd[i][j];
			} else if ('a' <= c && c <= 'z') {
				sources[c - 'a'][1] = vertInd[i][j];
			} else if (c == ' ') {
				// noop
			} else assert(false);
			G[i][j] = ' ';
		}
	}

	memset(edgeInd, -1, sizeof(edgeInd));
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (G[i][j] == 'X') continue;
			if (G[i][j] == ' ') continue;
			if (G[i][j] == '@') continue;

			if (G[i][j] == '_') {
				if (i == 0 || i == L-1 || G[i-1][j] == 'X' || G[i+1][j] == 'X') {
					G[i][j] = '@';
					continue;
				}
				edgeInd[i][j] = E++;
				edges[edgeInd[i][j]] = pair<int, int>(vertInd[i-1][j], vertInd[i+1][j]);
			} else if (G[i][j] == '/') {
				if (i == 0 || j == 0 || j == L-1 || G[i-1][j-1] == 'X' || G[i][j+1] == 'X') {
					G[i][j] = '@';
					continue;
				}
				edgeInd[i][j] = E++;
				edges[edgeInd[i][j]] = pair<int, int>(vertInd[i-1][j-1], vertInd[i][j+1]);
			} else if (G[i][j] == '\\') {
				if (i == 0 || j == 0 || j == L-1 || G[i-1][j+1] == 'X' || G[i][j-1] == 'X') {
					G[i][j] = '@';
					continue;
				}
				edgeInd[i][j] = E++;
				edges[edgeInd[i][j]] = pair<int, int>(vertInd[i-1][j+1], vertInd[i][j-1]);
			} else assert(false);
			assert(edges[edgeInd[i][j]].first != -1);
			assert(edges[edgeInd[i][j]].second != -1);
		}
	}

	/*
		 for (int i = 0; i < L; i++) {
		 cerr << G[i] << '\n';
		 }
		 cerr << '\n';
	 */

	T = 0;
	auto addEvt = [&](int a, int b) {
		if (a == -1) return;
		if (b == -1) return;
		assert(a != b);
		int curTime = T++;
		deletes[a].push_back(curTime);
		deletes[b].push_back(curTime);
	};
	for (int i = 0; i < V; i++) {
		int x = vertX[i], y = vertY[i];
		addEvt(edgeInd[x][y-1], edgeInd[x-1][y]);
		addEvt(edgeInd[x-1][y], edgeInd[x][y+1]);
		addEvt(edgeInd[x][y+1], edgeInd[x+1][y+1]);
		addEvt(edgeInd[x+1][y+1], edgeInd[x+1][y]);
		addEvt(edgeInd[x+1][y], edgeInd[x+1][y-1]);
		addEvt(edgeInd[x+1][y-1], edgeInd[x][y-1]);
	}

	for (int e = 0; e < E; e++) {
		deletes[e].push_back(T);
		for (int cur = 0, i = 0; i < int(deletes[e].size()); cur = deletes[e][i]+1, i++) {
			int nxt = deletes[e][i];
			for (int a = cur + S, b = nxt + S; a < b; a /= 2, b /= 2) {
				if (a & 1) {
					ops[a].push_back(e);
					a++;
				}
				if (b & 1) {
					--b;
					ops[b].push_back(e);
				}
			}
		}
	}

	//cerr << T << '\n';
	initDSU();
	int ans = solve(1);
	cout << ans << '\n';

	return 0;
}

