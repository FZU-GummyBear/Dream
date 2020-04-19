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
#define pw(x) (1ll << (x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n;
ll a[N], L, R, K, det[N];
int top, sta[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll mi[N], la[N], sum[N];
	void up(int rt) { 
		sum[rt] = sum[ls] + sum[rs];
		mi[rt] = max(mi[ls], mi[rs]); }
	void gao(int rt, ll c, int l, int r) { mi[rt] += c; la[rt] += c; sum[rt] += (r - l + 1) * c; }
	void down(int rt, int l, int r, int mid) {
		if(la[rt]) {
			gao(ls, la[rt], l, mid);
			gao(rs, la[rt], mid + 1, r);
			la[rt] = 0;
		}
	}
	void upd(int L, int R, ll c, int l = 1, int r = n, int rt = 1) {
	//	if(rt == 1) dd(L), de(c);
		if(L > R) return ;
		if(L <= l && r <= R) return gao(rt, c, l, r), void();
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	ll qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L > R) return 0;
		if(L <= l && r <= R) return sum[rt];
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		ll ans = 0;
		if(L <= mid) ans += qry(L, R, l, mid, ls);
		if(R > mid) ans += qry(L, R, mid + 1, r, rs);
		return ans;
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> L >> R >> K;
	int up = R - L;
	rep(i, 1, n + 1) cin >> a[i];
	if(up) sta[++top] = 1;
	bool ok = 1;
	rep(i, 2, n + 1) {
		if(a[i] > a[i - 1]) {
			det[i] = 1; seg.upd(i, n, 1);
			if(seg.mi[1] > up) { ok = 0; break; }
			if(K > 1) sta[++top] = i;
		} else if(a[i] < a[i - 1]) {
			ll val = seg.qry(i - 1, i - 1);
			if(val) {
				det[i] = max(-K, -val);
				seg.upd(i, n, det[i]);
				if(det[i] < -1) sta[++top] = i;
			} else {
				bool tok = 0;
				while(top) {
					int j = sta[top];
					if(j == 1) {
						++det[j]; seg.upd(j, n, 1); tok = 1;
						if(det[j] == up) --top;
						break;
					} else if(det[j] > 0) {
						++det[j]; seg.upd(j, n, 1); tok = 1;
						if(det[j] == K) --top;
						break;
					} else {
						++det[j]; seg.upd(j, n, 1); tok = 1;
						if(det[j] == -1) --top;
						break;
					}
				}
				if(!tok) { ok = 0; break; }
				if(seg.mi[1] > up) { ok = 0; break; }
				det[i] = -1; seg.upd(i, n, -1);
			}
		} 
	}
	if(!ok) {
		cout << -1 << endl;
	} else {
		a[0] = L;
		rep(i, 1, n + 1) {
			a[i] = a[i - 1] + det[i], cout << a[i] << " \n"[i == n];
			assert(L <= a[i]);
			assert(a[i] <= R);
			if(i > 1) assert(abs(a[i - 1] - a[i]) <= K);
		}
	}
	return 0;
}
