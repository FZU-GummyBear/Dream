#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, m;
int ma[N], cnt[N];

struct Node {
	int x, y, z, o;
	ll cnt;
	bool ans;
	Node() {}
	Node(int x, int y, int z, ll cnt) : x(x), y(y), z(z), cnt(cnt) {}
	bool operator < (const Node & c) const {
		if(x != c.x) return x < c.x;
		if(y != c.y) return y < c.y;
		return z < c.z;
	}
	bool operator == (const Node &c) const {
		return x == c.x && y == c.y && z == c.z;
	}
	bool operator != (const Node &c) const {
		return !(*this == c);
	}
}nd[N], tmp[N];

struct FW {
#define lb(x) (x & -x)
	int n = 1e3;
	bool a[N];
	void upd(int p) {
		for( ; p <= n; p += lb(p)) a[p] = 1;
	}
	bool qry(int p) {
		bool ans = 0;
		for( ; p; p ^= lb(p)) ans |= a[p];
		return ans;
	}
	void init(int p) {
		for( ; p <= n; p += lb(p)) {
			if(a[p]) a[p] = 0;
			else break;
		}
	}
}fw;

void dfs(int l, int r) {
	if(l >= r) return ;
	int m = l + r >> 1;
	dfs(l, m); dfs(m + 1, r);
	rep(i, l, r + 1) nd[i].o = i > m;
	int p = l, q = m + 1, k = l;
	while(p <= m && q <= r) {
		if(nd[p].y <= nd[q].y) tmp[k++] = nd[p++];
		else tmp[k++] = nd[q++];
	}
	while(p <= m) tmp[k++] = nd[p++];
	while(q <= r) tmp[k++] = nd[q++];
	rep(i, l, r + 1) {
		nd[i] = tmp[i];
		if(nd[i].o == 0) {
			fw.upd(nd[i].z);
		} else {
			nd[i].ans |= fw.qry(nd[i].z);
		}
	}
	rep(i, l, r + 1) if(nd[i].o == 0) fw.init(nd[i].z);
}

int solve() {
	cin >> n >> m;
	memset(ma, 0, sizeof(ma));
	memset(cnt, 0, sizeof(cnt));
	rep(i, 0, N) nd[i].ans = 0;
	rep(i, 1, n + 1) {
		int a, b; cin >> a >> b;
		if(a > ma[b]) {
			ma[b] = a; cnt[b] = 1;
		} else if(a == ma[b]) {
			cnt[b]++;
		}
	}
	int tm = 0;
	rep(i, 1, m + 1) {
		int c, d, e; cin >> c >> d >> e;
		if(!ma[e]) continue;
		nd[++tm] = Node(ma[e], c, d, cnt[e]);
	}
	sort(nd + 1, nd + 1 + tm);
	int ct = 0;
	rep(i, 1, tm + 1) {
		if(i == 1 || nd[i] != nd[i - 1]) {
			nd[++ct] = nd[i];
		} else {
			nd[ct].cnt += nd[i].cnt;
		}
	}
	rep(i, 1, ct + 1) {
		nd[i].x = 1e5 + 1 - nd[i].x;
		nd[i].y = 1e3 + 1 - nd[i].y;
		nd[i].z = 1e3 + 1 - nd[i].z;
	}
	sort(nd + 1, nd + 1 + ct);
	dfs(1, ct);
	ll ans = 0;
	rep(i, 1, ct + 1) if(!nd[i].ans) ans += nd[i].cnt;
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		cout << "Case #" << ca << ": " << solve() << endl;
	}
	return 0;
}
