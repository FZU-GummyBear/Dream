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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 505;
db p[N][N], ans, dp[2][N];
int n, m, o, x;

void upd(db &x, db y) {x = max(x, y); }

int main() {
	while (~scanf("%d", &m)) {
		m = (m * (m - 1) * (m - 2) / 6);
		rep(i, 0, m) rep(j, 0, m) scanf("%lf", &p[i][j]);
		scanf("%d", &n);
		rep(i, 0, m) dp[0][i] = 1, dp[1][i] = 0;
		o = 0;
		rep(j, 0, n) {
			scanf("%d", &x);
			rep(i, 0, m) {
				upd(dp[o ^ 1][i], dp[o][i] * p[i][x]);
				upd(dp[o ^ 1][x], dp[o][i] * p[i][x]);
			}
			rep(i, 0, m) dp[o][i] = 0;
			o ^= 1;
		}
		ans = 0;
		rep(i, 0, m) ans = max(ans, dp[o][i]);
		printf("%.10f\n", ans);
	}	
	return 0;
}
