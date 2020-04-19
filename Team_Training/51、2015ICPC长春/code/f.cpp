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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

int n, a[N], dp[N];

bool check() {
	memset(dp, 0x3f, sizeof(dp[0]) * (n + 5));
	int inf = dp[0];
	rep(i, 1, n + 1) {
		int p = upper_bound(dp + 1, dp + 1 + n, a[i]) - dp;
		dp[p] = a[i];
	}
	return lower_bound(dp + 1, dp + 1 + n, inf) - dp - 1 >= n - 1;
}

bool solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	if(check()) return 1;
	rep(i, 1, n + 1) a[i] = 1e5 + 1 - a[i];
	return check();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		cout << (solve() ? "YES" : "NO") << endl;
	}
	return 0;
}
