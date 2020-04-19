#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e5 + 7, inf = pw(30);
ll ans;
int T, n, k, a[N], vis[N];

void solve(int l, int r) {
	if (l == r) {
		ans += (a[l] - 1 <= k);
		return;
	}
	int mid = l + r >> 1, t = -inf, p = mid;
	per(i, l, mid+1) {
		t = max(t, a[i]); 
		if (vis[a[i]]) p = min(p, vis[a[i]] - 1);
		vis[a[i]] = i;
		while (p + 1 <= r && a[p+1] <= t && !vis[a[p+1]]) p++, vis[a[p]] = p;
		if (p > mid) ans += max(0, p - max(mid+1, t - k + i - 1) + 1);
	}
	rep(i, l, r+1) vis[a[i]] = 0;
	p = mid + 1, t = -inf;
	rep(i, mid+1, r+1) {
		t = max(t, a[i]);
		if (vis[a[i]]) p = max(p, vis[a[i]] + 1);
		vis[a[i]] = i;
		while (p - 1 >= l && a[p-1] < t && !vis[a[p-1]]) p--, vis[a[p]] = p;
		if (p <= mid) ans += max(0, min(mid, k - t + 1 + i) - p + 1);
	}
	rep(i, l, r+1) vis[a[i]] = 0;
	solve(l, mid);
	solve(mid+1, r);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k;
		rep(i, 1, n+1) cin >> a[i];
		ans = 0;
		solve(1, n);
		cout << ans << endl;
	}
	return 0;
}
