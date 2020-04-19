#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
const int N = 105;
int n, m, a, b;
char s[N][N];
int cnt;
template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 10;
    int s , t , n , h[N] , cur[N] , lv[N] , q[N] , e , ne[M] , to[M], pre[N];
    T cap[M] , flow;
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
                    lv[q[R++] = to[k]] = lv[c] + 1, pre[to[k]] = c;
        }
        if (~lv[t]) {
        	int now = t; lv[now] = 500000;
			while (now != s) lv[pre[now]] = lv[now] - 1, now = pre[now];
			return 1;
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
        	cnt++;
        	assert(cnt <= 105);
            copy(h , h + n , cur);
            flow += dfs(s, ~0U>>1);
        }
        return flow;
    }
};
 
Dinic<int> G;
 
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
 
int x, y;
 
int id(int i, int j) {
	return (i-1) * m + j - 1;
} 
 
bool solve() {
	cnt = 0;
	cin >> n >> m >> a >> b;
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	G.ini(n * m + 10);
	int S = G.n - 5, T = S + 1;
	rep(i, 1, n+1) rep(j, 1, m+1) if (s[i][j] == '0'){
		rep(k, 0, 4) {
			x = i + dx[k];
			y = j + dy[k];
			if (x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] == '0') {
				G.link(id(i, j), id(x, y), 1);
			}
		}
	}
	rep(i, 1, a+1) {
		cin >> x;
		if (s[1][x] == '0') G.link(S, id(1, x), 1);
	}
	rep(i, 1, b+1) {
		cin >> x;
		G.link(id(n, x), T, 1);
	}
	return G.run(S, T) == a;
}
 
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "Yes" : "No") << endl;
	return 0;
}
