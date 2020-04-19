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
typedef __int128 ill;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 111, P = 1e9 + 7;

int n, pre[N];
struct Node {
	int lx, rx, ly, ry, w;
	void read() { cin >> lx >> ly >> rx >> ry >> w; }
	bool operator < (const Node &c) const { return w > c.w; }
	void print() { dd(lx), dd(ly), dd(rx), de(ry); }
}nd[N];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}

int top, vec[N << 1], ct;
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 3;
	ill tot[N];
	int cnt[N];
	void up(int rt, int l, int r) {
		if(cnt[rt]) {
			tot[rt] = ::vec[r + 1] - ::vec[l];
		} else if(l == r) {
			tot[rt] = 0;
		} else {
			tot[rt] = tot[ls] + tot[rs];
		}
	}
	void init() {
		memset(tot, 0, sizeof(tot));
		memset(cnt, 0, sizeof(cnt));
	}
	void upd(int L, int R, int c, int l = 1, int r = top, int rt = 1) {
		if(L <= l && r <= R) {
			cnt[rt] += c;
			up(rt, l, r);
		} else {
			int mid = l + r >> 1;
			if(L <= mid) upd(L, R, c, l, mid, ls);
			if(R > mid) upd(L, R, c, mid + 1, r, rs);
			up(rt, l, r);
		}
	}
}seg;
struct Stru {
	int x, l, r, o;
	Stru() {}
	Stru(int x, int l, int r, int o) : x(x), l(l), r(r), o(o) {}
	bool operator < (const Stru &c) const {
		if(x != c.x) return x < c.x;
		return o > c.o;
	}
}stru[N << 1];
ill calc(int n) {
	top = 0;
	rep(i, 1, n + 1) {
		vec[++top] = nd[i].ly;
		vec[++top] = nd[i].ry + 1;
	}
	sort(vec + 1, vec + 1 + top);
	top = unique(vec + 1, vec + 1 + top) - vec - 1;
	ct = 0;
	rep(i, 1, n + 1) {
		int l = lower_bound(vec + 1, vec + 1 + top, nd[i].ly) - vec;
		int r = lower_bound(vec + 1, vec + 1 + top, nd[i].ry + 1) - vec - 1;
		stru[++ct] = Stru(nd[i].lx, l, r, 1);
		stru[++ct] = Stru(nd[i].rx + 1, l, r, -1);
	}
	sort(stru + 1, stru + 1 + ct);
	int pre = stru[1].x;
	ill ans = 0;
	seg.init();
	rep(i, 1, ct + 1) {
		if(i == 1 || stru[i].x != stru[i - 1].x) {
			ans += (ill)seg.tot[1] * (stru[i].x - pre);
			pre = stru[i].x;
		}
		seg.upd(stru[i].l, stru[i].r, stru[i].o);
	}
	return ans;
}
bool check(int i, int j) {
	int lx = max(nd[i].lx, nd[j].lx);
	int ly = max(nd[i].ly, nd[j].ly);
	int rx = min(nd[i].rx, nd[j].rx);
	int ry = min(nd[i].ry, nd[j].ry);
	return lx <= rx && ly <= ry;
}
void solve(int n) {
	int ans = 0, con = 0;
	ill e = 0;
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, n + 1) {
		++con;
		rep(j, 1, i) if(check(i, j)) {
			int x = find(i), y = find(j);
			if(x != y) --con, pre[x] = y;
		}
		ill vex = calc(i);
		ill ne = vex - con;
		if((ans += (ne - e) % P * nd[i].w % P) >= P) ans -= P;
		e = ne;
	}
	cout << ans << endl;
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) {
		nd[i].read();
		sort(nd + 1, nd + 1 + i);
		solve(i);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
