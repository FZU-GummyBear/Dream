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


const int N = 1e5 + 7, M = 2e6 + 7;
int ans, use[N], col[N], lab[N], vis[N], a[N], e, m, ne[M], h[N], to[M], u, v, n, ma;
vi g[N];

void ins(int p, int v) {
	++e; to[e] = v; ne[e] = h[p]; h[p] = e;
}

void del(int p) {
	h[p] = ne[h[p]];
	while (!h[ma]) ma--;
}

int main(){
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
    cin >> n >> m;
    rep(i, 0, m) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
    e = ma = 0;
    rep(i, 1, n+1) ins(0, i);
    per(i, 1, n+1) {
        while (1) {
            u = to[h[ma]]; del(ma);
            if (!vis[u]) break;
		}
        a[i] = u, vis[u] = 1;
        for (auto v : g[u]) {
            ins(++lab[v], v);
            ma = max(lab[v], ma);
        }
    }
    per(i, 1, n+1) {
        for (auto v : g[a[i]]) use[col[v]] = i;
        rep(j, 1, n+1) if (use[j] != i) {
            col[a[i]] = j;
            ans = max(ans, col[a[i]]);
            break;
        }
    }
    cout << ans << endl;
    return 0;

}
