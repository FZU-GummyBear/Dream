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

const int N = 101010;

int n, a[N], b[N], ty[N];

struct Que {
	int o;
	priority_queue<pii> que;
	void init() {
		while(!que.empty()) que.pop();
	}
	int Sz() {
		while(!que.empty()) {
			auto &u = que.top();
			if(o != ty[u.se]) que.pop();
			else break;
		}
		return sz(que);
	}
	// Sz()
	int Top() {
		return que.top().fi;
	}
	int ind() {
		return que.top().se;
	}
	void ins(const pii &x) {
		que.push(x);
	}
}que[3][2];

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i] >> b[i], ty[i] = 0;
	rep(o, 0, 3) rep(i, 0, 2) que[o][i].init();
	rep(i, 1, n + 1) {
		que[0][0].ins(pii(a[i], i));
		que[0][1].ins(pii(a[i] + b[i], i));
	}
	ll ans = 0;
	int tn = n << 1;
	rep(i, 1, tn + 1) {
		int res[4] = {0};
		if(que[1][1].Sz()) res[0] = que[1][1].Top();
		if(que[0][0].Sz()) res[1] = que[0][0].Top();
		if(que[0][1].Sz()) {
			int k = que[0][1].Top();
			if(que[2][0].Sz()) res[2] = k + que[2][0].Top();
			if(que[1][0].Sz()) res[3] = k + que[1][0].Top();
		}
		int ma = 0; rep(i, 0, 4) ma = max(ma, res[i]);
		if(res[0] == ma) {
			int t = que[1][1].ind(); ty[t] = 2;
			que[2][0].ins(pii(-b[t], t));
		} else if(res[1] == ma) {
			int t = que[0][0].ind(); ty[t] = 1;
			que[1][0].ins(pii(-a[t], t));
			que[1][1].ins(pii(b[t], t));
		} else if(res[2] == ma) {
			int t = que[0][1].ind(); ty[t] = 2;
			que[2][0].ins(pii(-b[t], t));
			t = que[2][0].ind(); ty[t] = 1;
			que[1][0].ins(pii(-a[t], t));
			que[1][1].ins(pii(b[t], t));
		} else {
			int t = que[0][1].ind(); ty[t] = 2;
			que[2][0].ins(pii(-b[t], t));
			t = que[1][0].ind(); ty[t] = 0;
			que[0][0].ins(pii(a[t], t));
			que[0][1].ins(pii(a[t] + b[t], t));
		}
		ans += ma;
		cout << ans << " \n"[i == tn];
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(o, 0, 3) rep(i, 0, 2) que[o][i].o = o;
	while(T--) solve();
	return 0;
}
