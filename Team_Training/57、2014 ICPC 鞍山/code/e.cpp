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

const int N = 111;
const ll inf = 1e18;

int n, m, b[N];
ll f[N][N], a[N][N];

void upd(ll &a, ll b) {
	a = max(a, b);
}
void solve() {
	cin >> n >> m;
	rep(i, 1, m + 1) rep(j, 1, m + 1) cin >> a[i][j];
	rep(i, 1, n + 1) cin >> b[i];
	rep(i, 1, n + 1) rep(j, 1, m + 1) f[i][j] = -inf;
	if(~b[1]) f[1][b[1]] = 0;
	else rep(i, 1, m + 1) f[1][i] = 0;
	rep(i, 2, n + 1) {
		if(~b[i]) {
			rep(k, 1, m + 1) upd(f[i][b[i]], f[i - 1][k] + a[k][b[i]]);
		} else {
			rep(j, 1, m + 1) rep(k, 1, m + 1) {
				upd(f[i][j], f[i - 1][k] + a[k][j]);
			}
		}
	}
	ll ans = 0;
	rep(i, 1, m + 1) ans = max(ans, f[n][i]);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
