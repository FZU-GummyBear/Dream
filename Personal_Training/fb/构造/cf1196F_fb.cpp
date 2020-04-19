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
vector<pii> g[N]; // (边权, 终点) 需要排序 
int n, m, k, u, v, w;

struct data { // 距离 起点 当前点 当前扩展过的边编号 
    ll w; int st, last, id;
    data(ll W, int S, int L, int I) {
        w = W; st = S; last = L; id = I;
    }
    bool operator < (const data &c) const {
        return w > c.w;
    }
};

// 连通图的话 k <= n * (n - 1) 
// 复杂度最坏应该是O( min(nmlogn, k^2logk) ) 正常应该是O(klogk + nlogn) 
ll solve(int n, vector<pii> g[], int k) { 
	priority_queue<data> pq; 
    set<pii> vis;
    rep(i, 1, n+1) {
        if (sz(g[i])) pq.push(data(g[i][0].fi, i, i, 0));
        vis.insert(mp(i, i));
    }
    while (!pq.empty()) {
        data u = pq.top(); pq.pop();
        int v = g[u.last][u.id].se;
        if (!vis.count(mp(u.st, v))) {
            vis.insert(mp(u.st, v));
        	k--; if (k == 0) return u.w;
            if (sz(g[v])) pq.push(data(u.w + g[v][0].fi, u.st, v, 0));
        }
        if (u.id + 1 < sz(g[u.last])) 
            pq.push(data(u.w - g[u.last][u.id].fi + g[u.last][u.id + 1].fi, u.st, u.last, u.id + 1));
	}
} 

int main() {
    ios :: sync_with_stdio(0); 
	cin.tie(0);
    cin >> n >> m >> k;
    rep(i, 0, m) {
        cin >> u >> v >> w;
        g[u].pb(mp(w, v));
        g[v].pb(mp(w, u));
    }
	rep(i, 1, n+1) sort(all(g[i]));
    cout << solve(n, g, k * 2) << endl;
    return 0;
}
