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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 505;
int n, k;
string s;
vi g[N];
bool vis[N];
vi dfs(int u) {
	vi res; res.pb(u);
	vis[u] = 1;
	for (auto v : g[u]) if (!vis[v]) {
		vi tmp = dfs(v);
		//reverse(all(tmp));
		for (auto t : tmp) res.pb(t);
	}
	reverse(all(res));
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> s;
		rep(j, 1, n+1) if (s[j-1] == '1') g[i].pb(j), g[j].pb(i);
	}
	vi ans = dfs(1);
	rep(i, 0, n) cout << ans[i] << " \n"[i == n - 1];
	return 0;
}
