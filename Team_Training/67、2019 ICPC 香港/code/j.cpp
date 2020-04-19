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
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int P = 1e9 + 7, N = 5e3 + 10;
int T, n, m, len, ans, a[N], dp[2][N][61][61], vis[N], po[N];
string sl, sr;

void upd(int &x, int y) {
	x = (x + y) % P;
	if (x < 0) x += P;
}

void dfs(int pos, bool lim) {
	if (pos == 0) return;
	if (!lim && vis[pos]) return;
	if (!lim) vis[pos] = 1;
	int up = lim ? a[pos] : 9;
	memset(dp[lim][pos], 0, sizeof(dp[lim][pos]));
	rep(i, 0, up+1) {
		//dd(pos), de(i);
		dfs(pos-1, lim & (i == up));
		rep(j, 0, m) rep(k, 0, m) upd(dp[lim][pos][(j + i) % m][((k + (po[pos-1] - j) * i) % m + m) % m], dp[lim & (i == up)][pos - 1][j][k]);
	}
	return;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> sl >> sr >> m;
		reverse(all(sl));
		reverse(all(sr));
		len = sz(sr);
		po[0] = 1; rep(i, 1, len+1) po[i] = po[i-1] * 10 % m;	
		rep(i, 0, 2) rep(j, 0, len+1) rep(k, 0, m) rep(l, 0, m) dp[i][j][k][l] = 0;
		rep(i, 0, len+1) vis[i] = 0;
		dp[0][0][0][0] = dp[1][0][0][0] = 1;
		ans = 0;
		rep(i, 1, sz(sr)+1) a[i] = sr[i-1] - '0';
		//rep(i, 1, len+1) dd(a[i]); cout << endl;
		dfs(len, 1);
		//rep(i, 0, 2) rep(j, 0, len+1) rep(k, 0, m) rep(l, 0, m) de(dp[i][j][k][l]);
		rep(i, 0, m) upd(ans, dp[1][len][i][0]);
		//de(ans);
		len = sz(sl);
		rep(i, 1, sz(sl)+1) a[i] = sl[i-1] - '0';
		a[1]--;
		rep(i, 1, len+1) if (a[i] < 0) a[i] += 10, a[i+1] --; else break;
		while (a[len] == 0) len--;
		dfs(len, 1);
		rep(i, 0, m) upd(ans, -dp[1][len][i][0]);
		cout << ans << endl;
	}
	return 0;
}
