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

const int N = 4e5 + 7;
const int B = 200000;
int n, u, v, col[N], w[N], now[N];
vector<pii> g[N];

void dfs(int u, int c) {
	for (int &i = now[u]; i < sz(g[u]); i++) if (!col[g[u][i].se]){
		w[u] += c * -1;
		w[g[u][i].fi] += c * -1;
		col[g[u][i].se] = c * -1;
		dfs(g[u][i].fi, c * -1);
		break;
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> u >> v;
		g[u].pb(mp(v + B, i));
		g[v + B].pb(mp(u, i));
	}
	rep(i, 1, B+1) {
		while (now[i] < sz(g[i])) {
			dfs(i, w[i] <= 0 ? -1 : 1);
		}
 	}
	rep(i, 1, n+1) if (col[i] > 0) cout << "b"; else cout << "r";
	return 0;
}


