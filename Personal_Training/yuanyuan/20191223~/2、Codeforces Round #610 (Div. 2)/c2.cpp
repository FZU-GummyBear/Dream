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

int n, T, a, b, ty[N];

struct Node {
	int t, v;
	bool operator < (const Node &c) const {
		if(t != c.t) return t < c.t;
		return v < c.v;
	}
};

Node nd[N];

void solve() {
	cin >> n >> T >> a >> b;
	int mx = 0, my = 0;
	rep(i, 1, n + 1) {
		cin >> ty[i];
		nd[i].v = (ty[i] ? b : a);
		(ty[i] ? ++my : ++mx);
	}
	rep(i, 1, n + 1) cin >> nd[i].t;
	sort(nd + 1, nd + 1 + n);
	int x = 0, y = 0, ans = 0;
	rep(i, 1, n + 1) {
		(nd[i].v == b) ? ++y : ++x;
		if(i == n || nd[i].t != nd[i + 1].t) {
			int k = (i == n ? T : nd[i + 1].t - 1);
			if(x * 1ll * a + y * 1ll * b <= k) {
				int tx = x, ty = y;
				tx = min(mx, (k - ty * b) / a);
				ty = min(my, (k - tx * a) / b);
				ans = max(ans, tx + ty);
			}
		}
	}
	int k = max(0, nd[1].t - 1);
	x = min(mx, k / a);
	y = min(my, (k - x * a) / b);
	ans = max(ans, x + y);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; 
	while(T--) solve();
	return 0;
}
