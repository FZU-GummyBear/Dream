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

const int N = 2e5 + 7;
int now[N], n, m, u, v, k, R, du[N], col[N];
vi V;
vector<pii> g[N];
set<int> S[N];

void dfs(int u, int fa) {
	now[u] = 1;
	for (auto v : g[u]) if (v.fi != fa) {
		if (du[u] > R) {
			col[v.se] = now[u];
		} else {
			while (S[u].count(now[u])) now[u]++;
			col[v.se] = now[u]; 
		}
		S[v.fi].insert(col[v.se]);
		S[u].insert(col[v.se]);
		dfs(v.fi, u);
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	rep(i, 1, n) {
		cin >> u >> v;
		du[u]++;du[v]++;
		g[u].pb(mp(v, i));
		g[v].pb(mp(u, i));
	}
	rep(i, 1, n+1) V.pb(du[i]);
	sort(all(V));
	R = V[sz(V) - k - 1];
	dfs(1, 0);
	cout << R << endl;
	rep(i, 1, n) cout << col[i] << " \n"[i == n - 1];
	return 0;
}


