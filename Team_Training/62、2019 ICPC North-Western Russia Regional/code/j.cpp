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

int n, dp[N][N], g[N][N];
char s[N][N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	rep(i, 1, n + 1) rep(j, 1, n + 1) dp[i][j] = s[i][j] - '0';
	per(i, 1, n + 1) per(j, i + 1, n + 1) {
		g[i][j] = dp[i][j];
		rep(k, i + 1, j) g[i][j] -= dp[i][k] * g[k][j];
		g[i][j] = (g[i][j] % 10 + 10) % 10;
	}
	rep(i, 1, n + 1) {
		rep(j, 1, n + 1) cout << g[i][j];
		cout << endl;
	}
	return 0;
}
