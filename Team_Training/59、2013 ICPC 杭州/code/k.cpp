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
//---

// [0,n) , init!! , inf modify
const int inf = pw(30);
template<class U,class V>
struct MCMF{
    static const int N = 6000, M = 201010;
    int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n;
    U cap[M]; V dis[N], cost[M];
    void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
    bool spfa(){
        queue<int> Q;
        fill(dis, dis+n, inf);
        Q.push(s), ing[s] = 1, dis[s] = 0;
        while(!Q.empty()){
            int c = Q.front(); Q.pop(); ing[c] = 0;
            for(int k = h[c]; ~k; k = ne[k]) if (cap[k] > 0) {
                int v = to[k];
                if(dis[c] + cost[k] < dis[v]){
                    dis[v] = dis[c] + cost[k];
                    pre[v] = k;
                    if(!ing[v]) Q.push(v) , ing[v] = 1;
                }
            }
        }
        return dis[t] != inf;
    }
    U flow; V mincost;
    pair<U, V> run(int _s,int _t){
        s = _s , t = _t;
        flow = mincost = 0;
        while(spfa()){
            U pl = inf; int p, k;
            for(p = t;p != s;p = to[k^1]) pl = min(pl, cap[k = pre[p]]);
            for(p = t;p != s;p = to[k^1]) cap[k = pre[p]] -= pl, cap[k^1] += pl;
			mincost += pl * dis[t];
            flow += pl;
        }
        return mp(flow, mincost);
    }
};


const int N = 105;
MCMF<int, int> G;
int n, m, k, l[N], r[N], s, t, a[N][N], x;
int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n >> m >> k) {
		if (n == 0 && m == 0 && k == 0) break;
		rep(i, 1, n+1) cin >> l[i] >> r[i];
		G.ini(n + n + m + 10);
		s = G.n - 5; t = s + 1;
		rep(i, 1, n+1) {
			rep(j, 1, m+1) {
				cin >> a[i][j];
			}
		}
		rep(i, 1, n+1) {
			rep(j, 1, m+1) {
				cin >> x;
				if (a[i][j] < r[i]) G.link(j, i + n + m, 1, max(0, a[i][j] - l[i]) * k + x);
			}
		}
		rep(i, 1, m+1) G.link(s, i, 1, 0);
		rep(i, 1, n+1) G.link(s, i + m, 1, 0), G.link(i + n + m, t, 1, 0);
		rep(i, 1, n+1) rep(j, 1, n+1) {
			cin >> a[i][j];
		}
		rep(i, 1, n+1) rep(j, 1, n+1) {
			cin>> x;
			if (i != j && a[i][j] + r[i] < r[j]) {
				G.link(i + m, j + n + m, 1, max(0, a[i][j] + r[i] - l[j]) * k + x);
			}
		}
		auto ans = G.run(s, t);
		if (ans.fi != n) {
			cout << -1 << endl;
		}else cout << ans.se << endl;
	}
	return 0;
}


