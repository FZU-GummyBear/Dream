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

struct Node {
	int n; vi vec;
	int ma, mi;
	bool ok;
	void read() {
		ma = -1, mi = 1e9;
		ok = 0;
		cin >> n;
		rep(i, 0, n) {
			int x; cin >> x;
			if(x > mi) ok = 1;
			ma = max(ma, x);
			mi = min(mi, x);
			vec.pb(x);
		}
	}
	bool operator < (const Node &c) const { return ma < c.ma; }
};

const int N = 101010;

int n, pre[N], a[N];
Node nd[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) nd[i].read();
	sort(nd + 1, nd + 1 + n);
	ll ans = 0;
	rep(i, 1, n + 1) {
		pre[i] = pre[i - 1] + nd[i].ok;
		a[i] = nd[i].ma;
	}
	rep(i, 1, n + 1) {
		if(nd[i].ok) {
			ans += n;
		} else {
			int p = upper_bound(a + 1, a + 1 + n, nd[i].mi) - a;
			ans += n - p + 1 + pre[p - 1];
		}
	}
	cout << ans << endl;
	return 0;
}
