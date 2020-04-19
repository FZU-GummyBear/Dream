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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 33;

int n, a[N][N], b[N][N], tmp[N][N];

int solve() {
	int ans = 0;
	rep(i, 1, n + 1) rep(j, 1, n + 1) ans += a[i][j] == b[i][j];
	return ans;
}
void gao() {
	rep(i, 1, n + 1) rep(j, 1, n + 1) tmp[j][n + 1 - i] = b[i][j];
	rep(i, 1, n + 1) rep(j, 1, n + 1) b[i][j] = tmp[i][j];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		if(!n) break;
		rep(i, 1, n + 1) rep(j, 1, n + 1) cin >> a[i][j];
		rep(i, 1, n + 1) rep(j, 1, n + 1) cin >> b[i][j];
		int ans = 0;
		ans = max(ans, solve());
		gao();
		ans = max(ans, solve());
		gao();
		ans = max(ans, solve());
		gao();
		ans = max(ans, solve());
		cout << ans << endl;
	}
	return 0;
}
