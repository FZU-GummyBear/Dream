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

const int N = 85, INF = pw(30);
int c[N], k[N], col[N], u[N], v[N], w[N], sum, ans;
int T, n, m, tot, tot2;

struct GM {
	vi g[N];
	bool vis[N], exist[N];
	void dfs(int u) {
		vis[u] = 1;
		for(auto v : g[u]) if (!vis[v]) dfs(v);
	}
	bool test(vi &vec) {
		rep(i, 1, n+2) g[i].clear(), vis[i] = 0;
		memset(exist, 1, sizeof(exist));
		for(auto x : vec) exist[x] = 0;
		rep(i, 1, tot+1) if (exist[i]) {
			g[u[i]].pb(v[i]);
			g[v[i]].pb(u[i]);
		}
		dfs(1);
		rep(i, 1, n+2) if(!vis[i]) return 0;
		return 1;
	}
};

struct CM {
	int cnt[125];
	bool test(vi &vec) {
		memset(cnt, 0, sizeof(cnt));
		for(auto x : vec) cnt[col[x]]++;
		rep(i, 1, m+1) if(cnt[i] > c[i] - k[i]) return 0;
		return 1;
	}
};


template <class MT1, class MT2>
struct MI {
	int n, S, T;
	MI(int n) : n(n) {}
	int pre[N], d[N], cost[N];
	bool inq[N], has[N];
	vi g[N];
	queue<int> q;
	void clear() {
		rep(i, 1, n+3) {
			inq[i] = pre[i] = 0;
			d[i] = -INF;
			g[i].clear();
		}
		while(!q.empty()) q.pop();
	}
	
	vi getcur() {
		vi ret;
		rep(i, 1, n+1) if(has[i]) ret.pb(i);
		return ret;
	}

	pair<vi, ll> run() {
		ll ans = 0;
		MT1 mt1; MT2 mt2;
		memset(has, 0, sizeof(has));
		S = n + 1, T = n + 2, cost[S] = cost[T] = 0;
		while (1) {
			clear();
			rep(i, 1, n+1) {
				if(!has[i]) {
					cost[i] = w[i];
					has[i] ^= 1;
					vi tmp = getcur();
					if (mt1.test(tmp)) g[S].pb(i); // X1
					if (mt2.test(tmp)) g[i].pb(T); // X2
					has[i] ^= 1;
				} else cost[i] = -w[i];
			}
			rep(i, 1, n+1) if (has[i]) {
				has[i] ^= 1;
				vi tmp = getcur();
				rep(j, 1, n+1) if (!has[j] && i != j) {
					tmp.pb(j);
					if (mt1.test(tmp)) g[i].pb(j);
					if (mt2.test(tmp)) g[j].pb(i);
					tmp.pop_back();
				}  
				has[i] ^= 1;
			}
			d[S] = 0; q.push(S); inq[S] = 1;
			while(!q.empty()) {
				int u = q.front(); q.pop(); inq[u] = 0;
				for(auto v : g[u])
					if(d[v] < d[u] + cost[v]) {
						d[v] = d[u] + cost[v];
						pre[v] = u;
						if (!inq[v]) q.push(v), inq[v] = 1;
					}
			}
			if (!pre[T]) return mp(getcur(), ans);
			ans += d[T];
			int la = pre[T];
			while (la != S) has[la] ^= 1, la = pre[la];
		}
	}
};

//hdu 6636 Milk Candy

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		tot = ans = sum = 0;
		cin >> n >> m;
		rep(i, 1, m+1) {
			cin >> c[i] >> k[i];
			sum += c[i] - k[i];
			rep(j, 0, c[i]) {
				int l, r, cost;
				cin >> l >> r >> cost;
				col[++tot] = i;
				u[tot] = l, v[tot] = r + 1;
				w[tot] = cost;
				ans += cost;
			}
		}
		MI<GM, CM> mi(tot);
		auto res = mi.run();
		GM gm;
		if (sz(res.fi) != sum || !gm.test(res.fi)) cout << -1 << endl;
		else cout << ans - res.se << endl;
	}
	return 0;
}

