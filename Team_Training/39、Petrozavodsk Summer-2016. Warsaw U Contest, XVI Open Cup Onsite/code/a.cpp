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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2e6 + 5;
const ll inf = 9e18;

int n, m, a[N]; 
ll ans[N];
bool vis[N];
string str;
vi sta[N];

int b[N], cntb, pre[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int mi[N];
	void up(int rt) {
		mi[rt] = min(mi[ls], mi[rs]);
	}
	void build(int l = 1, int r = cntb, int rt = 1) {
		if(l == r) {
			mi[rt] = pre[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	// left first < c
	int qry(int L, int R, int c, int l = 1, int r = cntb, int rt = 1) {
		if(L <= l && r <= R && (l == r || mi[rt] >= c)) {
			if(mi[rt] >= c) return 0;
			return l;
		}
		int mid = l + r >> 1;
		if(L <= mid) {
			int t = qry(L, R, c, l, mid, ls);
			if(t) return t;
		}
		if(R > mid) {
			int t = qry(L, R, c, mid + 1, r, rs);
			if(t) return t;
		}
		return 0;
	}
	int qry2(int L, int R, int l = 1, int r = cntb, int rt = 1) {
		if(L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1, mi = 1e9;
		if(L <= mid) mi = min(mi, qry2(L, R, l, mid, ls));
		if(R > mid) mi = min(mi, qry2(L, R, mid + 1, r, rs));
		return mi;
	}
}seg;

void solve(int s) {
	cntb = 0;
	for(int i = s; !vis[i]; i = (i + n) % m) {
		vis[i] = 1;
		b[++cntb] = i;
	}
	rep(i, 1, cntb + 1) b[i + cntb] = b[i]; 
	int to = cntb; cntb <<= 1;
	rep(i, 1, cntb + 1) {
		pre[i] = pre[i - 1];
		if(str[b[i]] == 'W') ++pre[i];
		else --pre[i];
	}
	seg.build();
	rep(l, 1, to + 1) {
		int r = l + to - 1;
		int mi = seg.qry2(l, r) - pre[l - 1];
		int det = pre[r] - pre[l - 1];
		for(auto i : sta[b[l]]) {
			if(mi >= 0) {
				ans[i] = inf;
			} else {
				if(a[i] + mi <= 0) {
					int t = seg.qry(l, r, pre[l - 1] - a[i] + 1);
					assert(t);
					ans[i] = (t - l) * 1ll * n + i;
				} else {
					if(det >= 0) {
						ans[i] = inf;
					} else {
						int k = (a[i] + mi) / (-det) + 1;
						if((a[i] + mi) % (-det) == 0) --k;
						assert(k >= 1);
						ll aa = a[i] + k * 1ll * det;
						int t = seg.qry(l, r, pre[l - 1] - aa + 1);
						assert(t);
						ans[i] = (t - l + k * 1ll * to) * n + i;
					}
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n; rep(i, 1, n + 1) cin >> a[i];
	cin >> m >> str;
	rep(i, 1, n + 1) sta[(i - 1) % m].pb(i);
	rep(i, 0, m) if(!vis[i]) solve(i);
	ll res = inf;
	rep(i, 1, n + 1) res = min(res, ans[i]);
	if(res == inf) res = -1;
	cout << res << endl;
	return 0;
}
