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

const int N = 22;

int n, w[N], ini[111][4], dp[N][1 << 18];
char g[N][N], con[N][N];

void upd(int &a, int b) {
	if(a > b) a = b;
}
bool check(int s) {
	rep(i, 0, n) rep(j, 0, n) if((s >> i & 1) && (s >> j & 1) && con[i + 1][j + 1] == '1') return 0;
	return 1;
}
void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> (g[i] + 1);//, de(g[i] + 1);
	rep(i, 1, n + 1) cin >> (con[i] + 1);//, de(con[i] + 1);
	rep(i, 1, n + 1) cin >> w[i];
	memset(dp, 0x3f, sizeof(dp));
	int inf = dp[0][0]; dp[0][0] = 0;
	rep(i, 0, n) rep(j, 0, pw(n)) if(dp[i][j] != inf) {
		int d = 0, arr[4] = {0};
		rep(k, 1, n + 1) if(g[i + 1][k] == '1') arr[d++] = k;
		rep(k, 0, pw(d)) if((j >> i & 1) || ((k & 1) && arr[0] == i + 1)) {
			if(k) {
				int nj = j | pw(i), cnt = 0;
				rep(c, 0, d) if(k >> c & 1) nj |= pw(arr[c] - 1), ++cnt;
				upd(dp[i + 1][nj], dp[i][j] + ini[w[i + 1]][d]);
			} else {
				int nj = j ^ pw(i);
				upd(dp[i + 1][nj], dp[i][j]);
			}
		}
	}
	int ans = inf;
	rep(i, 0, pw(n)) if(check(i)) {
		dd(i), de(dp[n][i]);
		upd(ans, dp[n][i]);
	}
	if(ans == inf) ans = -1;
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 1, 111) {
		ini[i][0] = 0;
		ini[i][1] = i;
		rep(j, 2, 4) ini[i][j] = ini[i][j - 1] * i;
	}
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
