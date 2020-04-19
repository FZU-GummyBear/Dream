#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r=1;
	for(; b; b>>=1,a=mul(a,a)) {
		if(b&1)r=mul(r,a);
	}
	return r;
}
//----

// time : O(n^3)
// id : 0 .. n-1
struct blossom {
	static const int N = 20005;
	vi g[N];
	int u, v, n, match[N], q[N], L, R;
	int pred[N], b[N], s, t, newb;
	bool inq[N], inb[N], inp[N];

	void init(int _n) { n = _n; rep(i, 0, n) g[i].clear(); }

	void link(int u, int v) { g[u].pb(v); g[v].pb(u); }

	void push(int u) { q[R++] = u; inq[u] = 1; }

	int pop() { return q[L++]; }

	int LCA(int u,int v) {
		rep(i, 0, n) inp[i]=0;
		while(1) {
			inp[u = b[u]] = 1;
			if (u == s) break;
			u = pred[match[u]];
		}
		while(1) {
			if (inp[v = b[v]]) break;
			v = pred[match[v]];
		}
		return v;
	}

	void ResetTrace(int u) {
		int v;
		while(b[u] != newb) {
			v = match[u];
			inb[b[u]] = inb[b[v]] = 1;
			u = pred[v];
			if(b[u] != newb) pred[u] = v;
		}
	}

	void Blossom(int u,int v) {
		newb = LCA(u,v);
		rep(i, 0, n) inb[i] = 0;
		ResetTrace(u);
		ResetTrace(v);
		if(b[u] != newb) pred[u] = v;
		if(b[v] != newb) pred[v] = u;
		rep(i, 0, n) if (inb[b[i]]) {
			b[i] = newb;
			if (!inq[i]) push(i);
		}
	}

	bool Find(int u) {
		bool found = 0;
		rep(i, 0, n) pred[i] = -1, b[i] = i, inq[i] = 0;
		s = u, t = -1, L = R = 0;
		push(s);
		while(L < R) {
			int u = pop();
			per(i, 0, sz(g[u])) {
				int v = g[u][i];
				if (b[u] != b[v] && match[u] != v)
					if(v == s || (match[v] >= 0 && pred[match[v]] >= 0))
						Blossom(u, v);
					else if(pred[v] == -1) {
						pred[v]=u;
						if (match[v] >= 0) push(match[v]);
						else return t = v, 1;
					}
			}
		}
		return found;
	}
	void AugmentPath() {
		int u = t, v, w;
		while(u >= 0) {
			v = pred[u], w = match[v];
			match[v] = u, match[u] = v;
			u = w;
		}
	}

	int solve() {
		int res = 0;
		rep(i, 0, n) match[i] = -1;
		// random_shuffle maybe faster
		rep(i, 0, n) if (match[i] == -1) if (Find(i)) AugmentPath();
		rep(i, 0, n) if (match[i] != -1) res++;
		return res / 2;
	}
} G;

const int N = 110;
int n, m, x, y, ans, mex[300];
string s[N];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] == '.';
}

int id(int x, int y, int o) {
	return (x - 1) * m + y - 1 + o * n * m;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) {
		cin >> s[i];
		s[i] = " " + s[i];
	}
	G.init(n * m * 2);
	rep(i, 1, n+1) rep(j, 1, m+1) {
		if (s[i][j] == '+') {
			G.link(id(i, j, 0), id(i, j, 1));
			rep(k, 0, 4) {
				x = i + dx[k];
				y = j + dy[k];
				if (check(x, y)) G.link(id(i, j, 0), id(x, y, 0)), G.link(id(i, j, 1), id(x, y, 0));
			}
			ans--;
		} else if (s[i][j] == '*') {
			G.link(id(i, j, 0), id(i, j, 1));
			rep(k, 0, 4) {
				x = i + dx[k];
				y = j + dy[k];
				if (check(x, y)) {
					if (k < 2) G.link(id(i, j, 0), id(x, y, 0));
					else G.link(id(i, j, 1), id(x, y, 0));
				}
			}
			ans--;
		}
	}
	G.solve();
	rep(i, 1, n+1) rep(j, 1, m+1) if (s[i][j] != '.') {
		int u = id(i, j, 0), v = id(i, j, 1);
		if (G.match[u] != -1 && G.match[v] != -1 && G.match[u] != v) {
			rep(k, 'a', 'z'+1) mex[k] = 0;
			rep(k, -2, 3) rep(l, -2, 3) {
				x = i + k;
				y = j + l;
				if (x >= 1 && x <= n && y >= 1 && y <= m) mex[s[x][y]] = 1; 
			}
			rep(k, 'a', 'z'+1) if (!mex[k]) {
				s[i][j] = k;
				x = G.match[u] / m + 1, y = G.match[u] % m + 1;
				s[x][y] = k;
				x = G.match[v] / m + 1, y = G.match[v] % m + 1;
				s[x][y] = k;
				break;
			} 
		} 
	} 
	rep(i, 1, n+1) cout << s[i].substr(1, sz(s[i])) << endl;
	return 0;
}

