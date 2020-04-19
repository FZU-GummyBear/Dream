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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e3 + 10;
int n, u, v, w, du[N];
vector<pair<pii, int> > ans;
pair<pii, int> edge[N];
vector<pii> g[N];

int dfs(int u, int fa) {
	for (auto v : g[u]) if (v.fi != fa) return dfs(v.fi, u);
	return u; 
}

pii get(int u, int v) {
	vi tmp;
	int cnt = 0;
	if (sz(g[u]) == 1) return mp(u, u);
	for(auto t : g[u]) if (t.fi != v) {
		tmp.pb(dfs(t.fi, u));
		cnt++;
		if (cnt == 2) break;
	}
	return mp(tmp[0], tmp[1]);
}

void print(int u, int v, int w) {
	if (u != v) ans.pb(mp(mp(u, v), w));
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v >> w;
		edge[i] = mp(mp(u, v), w);
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
		du[u]++; du[v]++; 
	}
	rep(i, 1, n+1) if (du[i] == 2) {
		cout << "NO" << endl;
		return 0;
	}
	rep(i, 1, n) {
		u = edge[i].fi.fi, v = edge[i].fi.se, w = edge[i].se;
		pii t1 = get(u, v), t2 = get(v, u);
		print(t1.fi, t2.fi, w / 2);
		print(t1.se, t2.se, w / 2);
		print(t1.fi, t1.se, -w / 2);
		print(t2.fi, t2.se, -w / 2);
	}
	cout << "YES" << endl;
	cout << sz(ans) << endl;
	for (auto u : ans) cout << u.fi.fi << " " << u.fi.se << " " << u.se << endl;
	return 0;
}


