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

int n, k, a[N];
ll pre[N], suf[N];

ll solve() {
	int cnt = 0;
	per(i, 1, n + 1) {
		int t = cnt; 
		if(a[i] <= k) {
			++cnt;
			t = 0;
		}
		suf[i] = suf[i + 1] + t;
	}
	cnt = 0;
	rep(i, 1, n + 1) {
		int t = cnt;
		if(a[i] <= k) {
			++cnt;
			t = 0;
		}
		pre[i] = pre[i - 1] + t;
	}
	ll ans = n * 1ll * n;
	rep(i, 1, n + 2) ans = min(ans, pre[i - 1] + suf[i]);
	return ans;
}

struct FW {
#define lb(x) (x & -x)
	int a[N];
	void upd(int p) {
		for(; p <= n; p += lb(p)) a[p]++;
	}
	int qry(int p) {
		int ans = 0;
		for(; p; p ^= lb(p)) ans += a[p];
		return ans;
	}
}fw;
ll calc() {
	ll ans = 0;
	per(i, 1, n + 1) if(a[i] <= k) {
		ans += fw.qry(a[i] - 1);
		fw.upd(a[i]);
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n + 1) cin >> a[i];
	ll ans = solve() + calc();
	cout << ans << endl;
	return 0;
}
