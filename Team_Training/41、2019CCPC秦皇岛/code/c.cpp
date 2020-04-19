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

const int P = 998244353;
const int N = 5005;
int n, m, a[N], b[N], f[N][N], g[N][N], C[N][N], ans;

int add(int a, int b)  {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n+1) cin >> a[i];
	rep(i, 1, m+1) cin >> b[i];
	f[0][0] = 1;
	int nn = max(n, m);
	rep(i, 0, nn+1) {
		C[i][0] = 1;
		rep(j, 1, i+1) C[i][j] = add(C[i-1][j], C[i-1][j-1]);
	}
	rep(i, 1, n+1) rep(j, 1, m+1) {
		f[i][j] = add(f[i-1][j], f[i][j-1]);
		if (a[i] != b[j]) f[i][j] = add(f[i][j], -f[i-1][j-1]);
	}
	g[n+1][m+1] = 1;
	per(i, 1, n+1) per(j, 1, m+1) g[i][j] = add(g[i+1][j], g[i][j+1]);
	rep(i, 1, n+1) rep(j, 1, m+1) if (a[i] > b[j]) ans = add(ans, mul(f[i-1][j-1], g[i+1][j+1]));
	de(ans);

	rep(i, 1, n+1) rep(j, 1, m+1) {
		if (j >= i) break;
		ans = add(ans, mul(C[n][i], C[m][j]));
	}
	cout << ans << endl;
	return 0;
}
