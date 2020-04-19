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

const int N = 303030, P = 998244353;

int n, a[N], dp[N], sum[N], pre[N], f[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	dp[0] = sum[0] = 1;
	rep(i, 1, n + 1) {
		int t = pre[a[i]];
		pre[a[i]] = i;
		t = max(t, f[i - 1]);
		f[i] = t;
		dp[i] = sum[i - 1];
		if(t) {
			if((dp[i] -= sum[t - 1]) < 0) dp[i] += P;
		}
		sum[i] = (sum[i - 1] + dp[i]) % P;
	}
	cout << dp[n] << endl;
	return 0;
}
