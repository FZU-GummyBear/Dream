//#pragma GCC optimize(3)
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse2")
#include<iostream>
#include<algorithm>
#include<vector>
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

const int N = 255;
int n, m, u, v, wl[N][N], wr[N][N], T, s, t, x, y, q, stx, sty, edx, edy, ma, mi, w, pos[N][N], la;
string op;
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
		la 有源汇额外增加的 t->s 的边编号 
	*/
	int run(int o) { 
		build();
		T flow = run(ss, tt); 
		if (flow != need) return -1;
		if (o != 0) {
			flow = cap[::la ^ 1];
			cap[::la] = cap[::la ^ 1] = 0;
			if (o == 1) flow += run(:: s, :: t);
			else flow -= run(::t, ::s);
		}	
		rep(i, 1, m+1) use[i] += cap[id[i]];
		return flow;
	}
};

Dinic<int> G;

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		G.ini(n + m + 10);
		s = G.n - 5; t = s + 1;
		rep(i, 1, n+1) cin >> x, G.link(s, i, x, x);
		rep(i, 1, m+1) cin >> x, G.link(i + n, t, x, x);
		cin >> q;
		rep(i, 1, n+1) rep(j, 1, m+1) wr[i][j] = pw(23), wl[i][j] = 0;
		rep(tim, 1, q+1) {
			cin >> x >> y >> op >> w;
			if (x == 0) stx = 1, edx = n; else stx = edx = x;
			if (y == 0) sty = 1, edy = m; else sty = edy = y;
			if (op == "=") mi = ma = w;
			else if (op == "<") ma = w - 1, mi = 0;
			else mi = w + 1, ma = pw(23);
			rep(i, stx, edx+1)
				rep(j, sty, edy+1) wl[i][j] = max(wl[i][j], mi), wr[i][j] = min(wr[i][j], ma);
		}
		bool ok = 1;
		rep(i, 1, n+1) rep(j, 1, m+1) {
			if (wl[i][j] > wr[i][j]) ok = 0;
			G.link(i, j + n, wl[i][j], wr[i][j]);
			//dd(wl[i][j]), de(wr[i][j]);
			pos[i][j] = G.m;
		}
		if (!ok) {
			cout << "IMPOSSIBLE" << endl << endl;
			continue;
		}
		la = G.e; G.link(t, s, 0, pw(23)); 
		if (G.run(1) == -1) {
			cout << "IMPOSSIBLE" << endl << endl;
		}else  {
			rep(i, 1, n+1) rep(j, 1, m+1) cout << G.use[pos[i][j]] << " \n"[j == m];
			cout << endl;
		}
	}
	return 0;
}


