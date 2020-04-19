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

const int N = 202020;

int n, p, k, a[N], dp[N];

void solve() {
	cin >> n >> p >> k;
	rep(i, 1, n + 1) cin >> a[i];
	sort(a + 1, a + 1 + n);
	rep(i, 1, n + 1) {
		dp[i] = dp[i - 1] + a[i];
		if(i - k >= 0) dp[i] = min(dp[i], dp[i - k] + a[i]);
	}
	per(i, 0, n + 1) if(dp[i] <= p) {
		cout << i << endl;
		return ;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
