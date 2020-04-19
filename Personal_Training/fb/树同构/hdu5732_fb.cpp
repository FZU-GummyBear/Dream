//#pragma GCC optimize(3)
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse2")
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


const int P = 1e9 + 31, se1 = 1e9 + 7, se2 = 1e9 + 21;

const int N = 1e5 + 7;
map<string, int> M[2];
int tim[2], siz[2][N], n, ans, u, v, an[N];
vi cen[2];
string ss[2][N], s1, s2;
vi g[2][N];
pii edge[N];
int p[N];

inline int upd(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
inline int mul(int a, int b) {return 1ll * a * b % P; }
struct Int{
	int a, b;
	Int(int a = 0, int b = 0) : a(a), b(b) {}
	inline Int operator + (const Int &c) const { return Int(upd(a, c.a), upd(b, c.b)); }
	inline Int operator ^ (const Int &c) const { return Int((a ^ c.a) % P, (b ^ c.b) % P); }
	inline Int operator - (const Int &c) const { return Int(upd(a, -c.a), upd(b, -c.b)); }
	inline Int operator * (const Int &c) const { return Int(mul(a, c.a), mul(b, c.b)); }
	inline bool operator == (const Int &c) const {return a == c.a && b == c.b;}
	inline bool operator < (const Int &c) const { if (a != c.a) return a < c.a; return b < c.b;}
} _0 = Int(), _1 = Int(1, 1), ha[2][N];
//----

void Assert(int o) {
	assert(o);
	if (!o) for( ;; );
}

int id(string s, int o) {
	if (M[o].count(s)) return M[o][s];
	tim[o]++;
	ss[o][tim[o]] = s;
	return M[o][s] = tim[o];
}

void dfs(int u, int fa, int o) {
	siz[o][u] = 1;
	int mx = -1;
	for (auto v : g[o][u]) if (v != fa) {
			dfs(v, u, o);
			mx = max(mx, siz[o][v]);
			siz[o][u] += siz[o][v];
		}
	mx = max(mx, n - siz[o][u]);
	if (mx < ans) {
		ans = mx;
		cen[o].clear();
		cen[o].pb(u);
	} else if (mx == ans) cen[o].pb(u);
	
}

int Q = 0;

bool cmp(int a, int b) {
	return ha[Q][a] < ha[Q][b];
}

void dfs2(int u, int fa, int o) {
	ha[o][u] = Int(23333, 23777);

	for (auto v : g[o][u]) if (v != fa) {
		dfs2(v, u, o);
		ha[o][u] = ha[o][u] * (ha[o][v] ^ Int(se1, se2));
	}
	rep(i, 0, sz(g[o][u])) if (g[o][u][i] == fa) {
		g[o][u].erase(g[o][u].begin() + i);
		Q = o;
		sort(all(g[o][u]), cmp);
		g[o][u].pb(fa);
		break;
	}
	if (fa == 0) {
		Q = o;
		sort(all(g[o][u]), cmp);
	}
}

void dfs3(int u, int u2, int fa) {
	an[u] = u2;
	//Assert(sz(g[0][u]) == sz(g[1][u2]));
	rep(i, 0, sz(g[0][u])) if (g[0][u][i] != fa) {
		int v = g[0][u][i], v2 = g[1][u2][i];
		dfs3(v, v2, u);
	}
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n) {
		if (n == 1) continue;
		rep(i, 0, 2) {
			M[i].clear(); tim[i] = 0; 
			rep(j, 1, n+1) g[i][j].clear();
		}
		rep(i, 1, n) {
			cin >> s1 >> s2;
			u = id(s1, 0), v = id(s2, 0);
			
			//u = i + 1; v = rand() % i + 1;
			//edge[i] = mp(u, v);
			g[0][u].pb(v);
			g[0][v].pb(u);
		}
		//rep(i, 1, n+1) p[i] = i;
		//random_shuffle(p + 1, p + n + 1);
		rep(i, 1, n) {
			cin >> s1 >> s2;
			u = id(s1, 1), v = id(s2, 1);
			
			//u = p[edge[i].fi], v = p[edge[i].se];
			g[1][u].pb(v);
			g[1][v].pb(u);
		}
		ans = n;
		dfs(1, 0, 0);
		ans = n;
		dfs(1, 0, 1);
		dfs2(cen[0][0], 0, 0);
		dfs2(cen[1][0], 0, 1);
		if (!(ha[1][cen[1][0]] == ha[0][cen[0][0]])) swap(cen[1][0], cen[1][1]), dfs2(cen[1][0], 0, 1);
		Assert(ha[1][cen[1][0]] == ha[0][cen[0][0]]);
		dfs3(cen[0][0], cen[1][0], 0);
		rep(i, 1, n+1) cout << ss[0][i] << " " << ss[1][an[i]] << endl;
	}
	return 0;
}


