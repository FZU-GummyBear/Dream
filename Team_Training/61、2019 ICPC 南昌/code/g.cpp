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

const int N = 101010, P = 998857459;

int n, m, a[N], jc[N], pre[N], dp[N];
int top, sta[N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	jc[0] = 1;
	rep(i, 1, N) {
		jc[i] = jc[i - 1] * 1ll * i % P;
	}
	cin >> n >> m;
	rep(i, 1, n + 1) {
		cin >> a[i]; a[i] = jc[a[i]];
		pre[i] = add(pre[i - 1], a[i]);
		if(a[i]) sta[++top] = i;
	}
	rep(i, 1, top + 1) rep(j, i, top + 1) {
		int l = sta[i], r = sta[j];
		int len = r - l + 1;
		dp[len] = max(dp[len], (pre[r] - pre[l - 1] + P) % P);
	}
	rep(i, 2, n + 1) dp[i] = max(dp[i], dp[i - 1]);
	while(m--) {
		int k; cin >> k;
		if(dp[n] < k) {
			cout << -1 << endl;
		} else {
			cout << lower_bound(dp + 1, dp + 1 + n, k) - dp << endl;
		}
	}
	return 0;
}
