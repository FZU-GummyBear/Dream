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

const int N = 1e5 + 7;
ll n, m, u, v, wl, wr;

// [0,n) init!! 
// double need eps  
template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 50;
    int s, t, n, h[N], cur[N], lv[N], q[N], e, ne[M], to[M], m, ss, tt, id[M];
    T cap[M], flow, use[M], need, a[N];
    void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
    void link(int u,int v,T w){ liu(u, v, w);liu(v, u, 0);}
    void ini(int _n = N) { fill(h, h + (n=_n), -1); fill(a, a + n, 0); e = m = need = 0;}
    bool bfs(){
        int L = 0 , R = 0;
        fill(lv , lv + n , -1);
        lv[q[R++] = s] = 0;
        while(L < R && !~lv[t]){
            int c = q[L++];
            for(int k = h[c]; ~k ; k = ne[k])
                if(cap[k] > 0 && !~lv[to[k]]) 
                    lv[q[R++] = to[k]] = lv[c] + 1;
        }
        return ~lv[t];
    }
    T dfs(int c,T mx){
        if(c == t) return mx;
        T ret = 0;
        for(int &k = cur[c]; ~k; k = ne[k]){
            if(lv[to[k]] == lv[c] + 1 && cap[k] > 0){
                T flow = dfs(to[k] , min(mx , cap[k]));
                ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
                if(!mx) return ret;
            }
        }
        lv[c] = -1;
        return ret;
    }
    T run(int _s,int _t){
        s = _s , t = _t;
        flow = 0;
        while(bfs()){
            copy(h , h + n , cur);
            flow += dfs(s, ~0U>>1);
        }
        return flow;
    }
    
    void link(int u, int v, T wl, T wr) { // wl <= wr
		a[u] -= wl; a[v] += wl;
		use[++m] = wl; id[m] = e + 1;
		link(u, v, wr - wl);
	}
	void build() {
		ss = n - 2; tt = ss + 1;
		rep(i, 0, n) if (a[i] < 0) link(i, tt, -a[i]); else link(ss, i, a[i]), need += a[i]; 
	} 
	/*  o = 0 无源汇可行流  	
		o = 1 有源汇最大流
		o = -1 有源汇最小流 
	*/
	int run(int o) { 
		build();
		T flow = run(ss, tt); 
		if (flow != need) return -1;
		rep(i, 1, m+1) use[i] += cap[id[i]];
		return 1;
	}
};

Dinic<int> G;

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	G.ini(n + 10);
	rep(i, 1, m+1) {
		cin >> u >> v >> wl >> wr;
		G.link(u, v, wl, wr);
	}
	if (G.run(0) == -1) cout << "NO" << endl;
	else {
		cout << "YES" << endl;
		rep(i, 1, G.m+1) cout << G.use[i] << endl;
	}
	return 0;
}


