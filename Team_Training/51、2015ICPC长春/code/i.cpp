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
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

// [0,n) init!! 
// double need eps
const int inf = pw(30);  
const int N = 1e4 + 100;
int n, m, a, b, T, ss, tt, ans, bel[N];
string s[105];
bool vis[N], col[N];
vi g[N];


template<class T>
struct Dinic{
    const static int N = 20101 , M = N * 10;
    int s, t, n, h[N], cur[N], lv[N], q[N], e, ne[M], to[M];
    T cap[M], flow;
    void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
    void link(int u,int v,T w){ liu(u , v , w);liu(v , u , 0);}
    void ini(int _n = N) { fill(h , h + (n=_n) , -1);e = 0;}
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
    
    void dfs2(int u, int o) {
    	bel[u] = o;
		for (int k = h[u]; ~k; k = ne[k]) if (cap[k ^ o]) {
			int v = to[k];
			if (bel[v] == -1) dfs2(v, o);
		}
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
};

Dinic<int> G;

int id(int x, int y) {return x * m + y;}

void dfs(int u, int o) {
    vis[u] = 1; col[u] = o;
    for (auto v : g[u]) if (!vis[v]) dfs(v, o ^ 1);
}

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
    FI(a);
    ios::sync_with_stdio(0);
    cin.tie(0);
    //cout << setiosflags(ios::fixed);
    //cout << setprecision(2);
    cin >> T;
    rep(cas, 0, T) {
        cin >> n >> m >> a >> b;
		G.ini(n * m + 10); ss = G.n - 5; tt = ss + 1;
        rep(i, 0, n) cin >> s[i];
		int dx[] = {a, a, -a, -a}, dy[] = {b, -b, b, -b};
        ans = 0;
        rep(i, 0, n * m) g[i].clear(), vis[i] = col[i] = 0, bel[i] = -1;
        rep(i, 0, n) rep(j, 0, m) {
        	int u = id(i, j);
            rep(k, 0, 4) {
                int x = i + dx[k], y = j + dy[k];
                int v = id(x, y);
                if (check(x, y)) G.link(u, v, 1), g[u].pb(v), ans++;
            }
        }
        ans /= 2;
        rep(i, 0, n) rep(j, 0, m) {
        	int u = id(i, j);
            if (!vis[u]) dfs(u, 1);
            if (s[i][j] != '.') {                
                if (col[u] ^ (s[i][j] == 'B')) G.link(u, tt, inf);
            	else G.link(ss, id(i, j), inf);
            }
        }
        ans -= G.run(ss, tt);
        G.dfs2(ss, 0);
        G.dfs2(tt, 1);
        cout << ans << endl;
        int cnt = 0;
        rep(i, 0, n)
            rep(j, 0, m) if (s[i][j] == '.'){
            	int u = id(i, j);
                if (bel[u] == -1) G.dfs2(u, col[u] ^ 1);
                s[i][j] = (col[u] ^ bel[u]) ? 'B' : 'W';
            }
        rep(i, 0, n) cout << s[i] << endl;     
    }
    return 0;
}
