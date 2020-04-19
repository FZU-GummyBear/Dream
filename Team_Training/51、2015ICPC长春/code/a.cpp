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

int p, cnt[22], n = 10;
int w[] = {0, 1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
ll sum[22];
int ans;

void dfs(int d, int n, int tot) {
	if(d == 1) {
		if(n <= cnt[1]) {
			ans = max(ans, tot + n);
		}
		return ;
	}
	ll fz = n - sum[d - 1];
	ll x = fz < 0 ? 0 : (fz + w[d] - 1) / w[d];
	if(x <= cnt[d] && x * w[d] <= n) dfs(d - 1, n - x * w[d], tot + x);
	++x;
	if(x <= cnt[d] && x * w[d] <= n) dfs(d - 1, n - x * w[d], tot + x);
}

int solve() {
	cin >> p; 
	ans = -1;
	rep(i, 1, n + 1) {
		cin >> cnt[i];
		sum[i] = sum[i - 1] + cnt[i] * w[i];
	}
	dfs(10, p, 0);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << solve() << endl;
	return 0;
}
