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
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 20202;

int n, a[N], ans;
vi vec[N];
char s[303030];

struct Trie {
	static const int N = 3e5 + 5, M = 26;
	int ne[N][M], fail[N], fa[N], rt, L, dp[N], vis[N], tim;
	void init() {
		fill_n(ne[fail[0] = N - 1], M, 0);
		L = tim = 0; rt = newnode();
	}
	int newnode() {
		dp[L] = vis[L] = 0;
		fill_n(ne[L], M, 0); return L++;
	}
	void add(char *s) {
		++tim;
		int p = rt;
		for(int i = 0; s[i]; ++i) {
			int c = s[i] - 'a';
			if(!ne[p][c]) ne[p][c] = newnode();
			p = ne[p][c];
			vec[tim].pb(p);
		}
	}
	void solve() {
		rep(i, 1, n + 1) {
			++tim; int ma = 0;
			for(auto p : vec[i]) {
				int u = p;
				while(u != rt && vis[u] != tim) {
					ma = max(ma, dp[u]);
					vis[u] = tim; u = fail[u];
				}
			}
			int p = vec[i].back();
			dp[p] = max(dp[p], ma + a[i]);
			ans = max(ans, dp[p]);
		}
	}
	void build() {
		tim = 0;
		vi v; v.pb(rt);
		rep(i, 0, sz(v)) {
			int c = v[i];
			rep(i, 0, M) ne[c][i] ? 
			v.pb(ne[c][i]), fail[ne[c][i]] = ne[fail[c]][i] :
			ne[c][i] = ne[fail[c]][i];
		}
	}
}ac;

int solve() {
	cin >> n;
	ac.init(); ans = 0;
	rep(i, 1, n + 1) {
		cin >> s >> a[i];
		vec[i].clear();
		ac.add(s);
	}
	ac.build();
	ac.solve();
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; 
	rep(i, 1, T + 1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
