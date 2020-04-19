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

const int N = 55;

int n, m, k;
char s[N][N], t[N][N], tt[N][N];
char str[4][N * N], s2[N * N];
map<string, bool> vis;
vector<string> ans, tmp;

void gao() {
	rep(i, 0, n) rep(j, 0, n) tt[j][n - 1 - i] = t[i][j];
	rep(i, 0, n) rep(j, 0, n) t[i][j] = tt[i][j];
}

void solve() {
	cin >> n; m = n * n / 4;
	rep(i, 0, n) cin >> s[i];
	rep(i, 0, n) cin >> t[i];
	rep(o, 0, 4) {
		int ct = 0;
		rep(i, 0, n) rep(j, 0, n) if(t[i][j] == '*') str[o][ct++] = s[i][j];
		str[o][m] = '\0';
		gao();
	}
	cin >> k; vis.clear();
	rep(i, 0, k) { string s; cin >> s; vis[s] = 1; }
	ans.clear();
	rep(o, 0, 4) {
		rep(i, 0, 4) rep(j, 0, m) s2[i * m + j] = str[(o + i) % 4][j];
		s2[4 * m] = '\0';
		tmp.clear();
		for(char *p = strtok(s2, "."); p; p = strtok(NULL, ".")) tmp.pb(p);
		bool ok = 1;
		for(auto u : tmp) if(!vis.count(u)) { ok = 0; break; }
		if(ok) {
			if(!sz(ans) || ans > tmp) ans = tmp;
		}
	}
	if(sz(ans)) {
		rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
	} else {
		cout << "FAIL TO DECRYPT" << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
