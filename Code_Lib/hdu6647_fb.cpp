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
typedef uniform_int_distribution<ll> RR;
mt19937 gen(998244353);
ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7, se = 23333, se2 = rnd(1, INT_MAX), se3 = rnd(1, INT_MAX);
int T, n, u, v, f[N], jc[N], inv[N], ans;
vi g[N];
unordered_set<ll> S;

struct Int{
	int a, b;
	Int(int a = 0, int b = 0) : a(a), b(b) {}
	inline Int operator + (const Int &c) const { return Int(add(a, c.a), add(b, c.b)); }
	inline Int operator - (const Int &c) const { return Int(add(a, -c.a), add(b, -c.b)); }
	inline Int operator * (const Int &c) const { return Int(mul(a, c.a), mul(b, c.b)); }
	inline Int operator / (const Int &c) const { return Int(mul(a, kpow(c.a, P - 2)), mul(b, kpow(c.b, P - 2))); }
	inline Int operator ! () const { return Int(a ^ se2, b ^ se3); }
	inline ull operator ~ () const { return ((ull)a << 32) + b;}
	inline bool operator == (const Int &c) const {return a == c.a && b == c.b;}
} _0 = Int(), _1 = Int(1, 1), ha[N];


void dfs1(int u, int fa) {
	f[u] = 1; ha[u] = se; unordered_map<ull, int> M;
	for (auto v : g[u]) if (v != fa) {
		dfs1(v, u);
		ha[u] = ha[u] * !ha[v];
		f[u] = mul(f[u], f[v]); 
		int t = ++M[~ha[v]];
		f[u] = mul(f[u], mul(jc[t-1], inv[t]));
	}
	f[u] = mul(f[u], jc[sz(g[u]) - (u != 1)]);
}

void dfs2(int u, int fa, int f1, Int ha1) {
	unordered_map<ull, int> M;
	for (auto v : g[u]) if (v != fa) M[~ha[v]]++;
	int t1 = f[u]; Int t2 = ha[u];
	if (u != 1) {
		int c = ++M[~ha1];
		t1 = mul(t1, mul(jc[c-1], inv[c]));
		t1 = mul(t1, f1);
		t2 = t2 * !ha1;
	}
	if (!S.count(~t2)) S.insert(~t2), ans = add(ans, mul(t1, mul(inv[sz(g[u]) - (u != 1)], jc[sz(g[u])])));//, dd(u), de(ans);
	for (auto v : g[u]) if (v != fa) {
		int c = M[~ha[v]] - 1, t3 = mul(mul(t1, kpow(f[v], P - 2)), mul(jc[c+1], inv[c]));
		if (u == 1) t3 = mul(t3, mul(inv[sz(g[u])], jc[sz(g[u]) - 1]));
		dfs2(v, u, t3, t2 / !ha[v]);
	}
}

int main() {
	FI(a);
	FO(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i-1], i);
	inv[N-1] = kpow(jc[N-1], P - 2); 
	per(i, 0, N-1) inv[i] = mul(inv[i+1], i+1);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n; ans = 0; S.clear();
		rep(i, 1, n+1) g[i].clear(); 
		rep(i, 1, n) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		} 
		dfs1(1, 0);
		dfs2(1, 0, 0, _0);
		cout << ans << endl; 
	}
	return 0;
}


