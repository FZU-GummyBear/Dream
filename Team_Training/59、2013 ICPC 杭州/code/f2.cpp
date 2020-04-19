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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10101;

int n, pre[N], cnt[N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
pii a[N];
map<pii, int> id;

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
void gao(int x, int c) { cnt[find(x)] += c; }
void join(int x, int y) { 
	x = find(x), y = find(y);
	if(x == y) return ;
	cnt[y] += cnt[x];
	pre[x] = y;
}
void del(int s) {
	vi que; que.pb(s);
	id.erase(a[s]);
	rep(i, 0, sz(que)) {
		int s = que[i], x = a[s].fi, y = a[s].se;
		rep(d, 0, 4) {
			int nx = x + dx[d], ny = y + dy[d];
			if(nx < 1 || ny < 1 || !id.count(mp(nx, ny))) continue;
			int t = id[mp(nx, ny)];
			if((s & 1) == (t & 1)) {
				que.pb(t);
				id.erase(a[t]);
			} else {
				gao(t, 1);
			}
		}
	}
}
void solve() {
	cin >> n;
	id.clear();
	rep(i, 1, n + 1) pre[i] = i, cnt[i] = 0;
	rep(i, 1, n + 1) {
		int x, y; 
		cin >> x >> y; 
		a[i] = mp(x, y); id[a[i]] = i;
		int cnt = 0;
		rep(d, 0, 4) {
			int nx = x + dx[d], ny = y + dy[d];
			if(nx < 1 || ny < 1) continue;
			if(id.count(mp(nx, ny))) {
				int j = id[mp(nx, ny)];
				if((i & 1) == (j & 1)) join(i, j), --cnt;
				else gao(j, -1);
			} else ++cnt;
		}
		if(cnt) gao(i, cnt);
		bool ok = 0;
		rep(d, 0, 4) {
			int nx = x + dx[d], ny = y + dy[d];
			if(nx < 1 || ny < 1) continue;
			if(id.count(mp(nx, ny))) {
				int j = id[mp(nx, ny)];
				if((i & 1) != (j & 1) && !::cnt[find(j)]) {
					ok = 1;
					del(j);
				}
			}
		}
		if(!ok && !::cnt[find(i)]) del(i);
	}
	int ans[2] = {0};
	for(auto u : id) ans[u.se & 1]++;
	cout << ans[1] << " " << ans[0] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
