#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef long double ld;

const int inf = 1e9;
const ll inf64 = 1e18;

#define vec vector
#define ALL(x) (x).begin(), (x).end()

struct MCMF {

	struct Edge {
		int fr, to, cp, fl, cs, id;
	};

	int n, S, T;
	vec< Edge > es;
	vec< vec< int > > g;
	vec< ll > dist, phi;
	vec< int > from;

	MCMF(int _n, int _S, int _T):
		n(_n), S(_S), T(_T)
	{
		g.resize(n);
	}

	void add_edge(int fr, int to, int cp, int cs, int id) {
		g[fr].push_back((int)es.size());
		es.push_back({fr, to, cp, 0, cs, id});
		g[to].push_back((int)es.size());
		es.push_back({to, fr, 0, 0, -cs, -1});
	}

	void assign_capacity(int id, int cp) {
		es[2 * id].cp = cp;
	}

	void clear() {
		dist.clear();
		phi.clear();
		from.clear();
		for (Edge& e : es) {
			e.fl = 0;
		}
	}

	void init_phi() {
		dist.assign(n, 0);
		phi = dist;
		return;
		dist[S] = 0;
		for(int any, iter = 0;iter < n - 1;iter++) { // Ford Bellman
			any = 0;
			for(Edge e : es) {
				if(e.fl == e.cp) continue;
				if(dist[e.to] - dist[e.fr] > e.cs) {
					dist[e.to] = dist[e.fr] + e.cs;
					any = 1;
				}
			}
			if(!any) break;
		}
		phi = dist;
	}

	bool Dijkstra() {
		dist.assign(n, inf64);
		from.assign(n, -1);
		dist[S] = 0;
		priority_queue< pair< ll, int >, vec< pair< ll, int > >, greater< pair< ll, int > > > pq;
		pq.push({dist[S], S});
		while(!pq.empty()) {
			int v;
			ll di;
			tie(di, v) = pq.top();
			pq.pop();
			if(di != dist[v]) continue;
			for(int ps : g[v]) {
				Edge &e = es[ps];
				if(e.fl == e.cp) continue;
				if(dist[e.to] - dist[e.fr] > e.cs + phi[e.fr] - phi[e.to]) {
					dist[e.to] = dist[e.fr] + e.cs + phi[e.fr] - phi[e.to];
					from[e.to] = ps;
					pq.push({dist[e.to], e.to});
				}
			}
		}
		for(int v = 0;v < n;v++) {
			phi[v] += dist[v];
		}
		return dist[T] < inf64;
	}

	pll find_mcmf() {
		init_phi();
		ll flow = 0, cost = 0;
		while(Dijkstra()) {
			int mn = inf;
			for(int v = T;v != S;v = es[ from[v] ].fr) {
				mn = min(mn, es[from[v]].cp - es[from[v]].fl);
			}
			flow += mn;
			for(int v = T;v != S;v = es[ from[v] ].fr) {
				es[ from[v] ].fl += mn;
				es[ from[v] ^ 1 ].fl -= mn;
			}
		}
		for(Edge &e : es) {
			if(e.fl >= 0)
				cost += 1ll * e.fl * e.cs;
		}
		return make_pair(flow, cost);
	}

	map<int, int> getRes() {
		map<int, int> res;
		for (Edge e : es) {
			res[e.id] = e.fl;
		}
		return res;
	}
};


int main() {

#ifdef debug
	freopen("input.txt", "r", stdin);
#endif

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<int> holes = {
		1, 1, 2, 1, 0, 0, 1, 1, 0, 1,
		0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	int n;
	ll k;

	cin >> n >> k;

	if (k < 0 || k > 2 * n) {
		cout << "-1\n";
		return 0;
	}

	string s;

	cin >> s;

	vector<int> cnt(52);

	for (char c : s) {
		if (c >= 'a' && c <= 'z') {
			cnt[(c - 'a') * 2 + 1]++;
		} else {
			cnt[(c - 'A') * 2]++;
		}
	}

	int S = 54;
	int T = 55;
	int B = 52;
	int A = 53;
	int C = 56;
	int nn = 57;

	MCMF mcmf(nn, S, T);

	//    void add_edge(int fr, int to, int cp, int cs, int id)

	int id = 0;

	for (int i = 0; i < 52; i++) {
		mcmf.add_edge(S, i, cnt[i], 0, id++);
	}

	vector<int> idToA(52), idToB(52), idToC(52);
	vector<int> mnToA(52), mnToB(52), mnToC(52);

	for (int i = 0; i < 52; i++) {
		int toB = inf;
		int toA = inf;
		int toC = inf;
		for (int j = 0; j < 52; j++) {
			int dist = i <= j ? j - i : 52 - i + j;
			if (holes[j] == 2) {
				toB = min(toB, dist);
			}
			if (holes[j] == 1) {
				toA = min(toA, dist);
			}
			if (holes[j] == 0) {
				toC = min(toC, dist);
			}
		}
		mcmf.add_edge(i, B, cnt[i], toB, (idToB[i] = id++));
		mcmf.add_edge(i, A, cnt[i], toA, (idToA[i] = id++));
		mcmf.add_edge(i, C, cnt[i], toC, (idToC[i] = id++));
		mnToA[i] = toA;
		mnToB[i] = toB;
		mnToC[i] = toC;
	}

	int Bid, Aid, Cid;

	mcmf.add_edge(B, T, 0, 0, (Bid = id++));
	mcmf.add_edge(A, T, 0, 0, (Aid = id++));
	mcmf.add_edge(C, T, 0, 0, (Cid = id++));

	int best_c2 = -1;
	int best_score = inf;

	auto calc_score = [&](int c2) -> int {
		int c1 = k - 2 * c2;
		int c0 = n - c1 - c2;
		if (c0 < 0) return inf;
		mcmf.assign_capacity(Bid, c2);
		mcmf.assign_capacity(Aid, c1);
		mcmf.assign_capacity(Cid, c0);
		mcmf.clear();
		pll tmp = mcmf.find_mcmf();
		if (tmp.first == c2 + c1 + c0) {
			return tmp.second;
		} else {
			return inf;
		}
	};

	int bl = 0;
	int br = k / 2;
	int bm1, bm2;

	while (br - bl > 2) {
		bm1 = bl + (br - bl) / 3;
		bm2 = br - (br - bl) / 3;
		if (calc_score(bm1) < calc_score(bm2)) {
			br = bm2;
		} else {
			bl = bm1;
		}
	}

	for (int c2 = bl; c2 <= br; c2++) {
		int tmp_score = calc_score(c2);
		if (tmp_score < best_score) {
			best_score = tmp_score;
			best_c2 = c2;
		}
	}

	cout << best_score << "\n";

	mcmf.assign_capacity(Bid, best_c2);
	mcmf.assign_capacity(Aid, k - 2 * best_c2);
	mcmf.assign_capacity(Cid, n - best_c2 - (k - 2 * best_c2));
	mcmf.clear();

	pll tmp = mcmf.find_mcmf();

	map<int, int> res = mcmf.getRes();

	vector<int> cntToA(52), cntToB(52), cntToC(52);

	for (int i = 0; i < 52; i++) {
		cntToA[i] = res[idToA[i]];
		cntToB[i] = res[idToB[i]];
		cntToC[i] = res[idToC[i]];
	}

	for (char c : s) {
		int i;
		if (c >= 'a' && c <= 'z') {
			i = (c - 'a') * 2 + 1;
		} else {
			i = (c - 'A') * 2;
		}
		int j;
		if (cntToA[i] > 0) {
			cntToA[i]--;
			j = (i + mnToA[i]) % 52;
		} else if (cntToB[i] > 0) {
			cntToB[i]--;
			j = (i + mnToB[i]) % 52;
		} else if (cntToC[i] > 0) {
			cntToC[i]--;
			j = (i + mnToC[i]) % 52;
		} else {
			j = i;
		}
		if (j % 2) {
			cout << char('a' + j / 2);
		} else {
			cout << char('A' + j / 2);
		}
	}

	cout << "\n";

	return 0;
}
