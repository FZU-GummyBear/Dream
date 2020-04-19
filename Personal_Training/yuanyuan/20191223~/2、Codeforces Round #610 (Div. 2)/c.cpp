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
	ll sum = 0;
	rep(i, 1, n + 1) {
		cin >> ty[i];
		nd[i].v = (ty[i] ? b : a);
		sum += nd[i].v;
	}
	rep(i, 1, n + 1) cin >> nd[i].t;
	sort(nd + 1, nd + 1 + n);
	int ans = 0;
	ll now = 0;
	rep(i, 1, n + 1) {
		if(now < nd[i].t) ans = max(ans, i - 1);
		now += nd[i].v;
		if(now > T) break;
	}
	if(sum <= T) ans = n;
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; 
	while(T--) solve();
	return 0;
}
