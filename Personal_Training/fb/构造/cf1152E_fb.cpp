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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 3e5 + 7;
unordered_map<int, int> M;
int tim, u, v, a[N], b[N], n, val[N], du[N];

int id(int x) {
	if (M.count(x)) return M[x];
	val[tim+1] =  x;
	return M[x] = ++tim;
}

vi ans; bool vis[N]; int p[N];
vector<pii> g[N];
void dfs(int u) {
	
	for( ; p[u] < sz(g[u]); ++p[u]) {
		auto v = g[u][p[u]];
		if(!vis[abs(v.se)]) {
			vis[abs(v.se)] = 1;
			dfs(v.fi);
			ans.pb(v.fi);
			//ans.pb(u);
			//ans.pb(-v.se);
		}
	}
}


int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rep(i, 1, n) {
		if (a[i] > b[i]) {
			cout << -1 << endl;
			return 0;
		}
		u = id(a[i]); v = id(b[i]);
		g[u].pb(mp(v, i));
		g[v].pb(mp(u, i));
		du[u]++;
		du[v]++;
	}
	int o = 0, p = 1;
	rep(i, 1, tim+1) if (du[i] & 1) {
		o++;
		p = i;
	}
	if(o == 0 || o == 2) {
		dfs(p);
		ans.pb(p);
		if (sz(ans) != n) cout << -1 << endl;
		else {
			rep(i, 0, sz(ans)) cout << val[ans[i]] << " \n"[i == sz(ans) - 1];
		}
		
		
	}else cout << -1 << endl;
	return 0; 
}


