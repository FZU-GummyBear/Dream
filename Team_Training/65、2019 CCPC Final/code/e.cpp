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

const int N = 101010, INF = pw(18) - 1, M = 1e7 + 5;

int n, s, p, cur[N];
int pw[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
struct Node {
	int x, y, val;
	void print() { dd(x), dd(y), de(val); }
}nd[N];
vi ans;
int rdx[M], rdy[M];
bool del[N];
ll s2;

int read(int x) {
	char s[11]; scanf("%s", s);
	int len = strlen(s);
	if(s[0] == '1') return pw[x];
	int ans = 0;
	rep(i, 2, 2 + x) {
		if(i >= len) ans = ans * 10;
		else ans = ans * 10 + s[i] - '0';
	}
//	de(ans);
	return ans;
}
bool cmp(int i, int j) { return nd[i].val > nd[j].val; }

bool check(int i, int j) {
	int lx = max(nd[i].x, nd[j].x);
	int rx = min(nd[i].x + s, nd[j].x + s);
	int ly = max(nd[i].y, nd[j].y);
	int ry = min(nd[i].y + s, nd[j].y + s);
	if(lx > rx || ly > ry) return 0;
	ll A = (rx - lx) * 1ll * (ry - ly);
	//de(A);
	if(A * 1000 > p * (s2 - A)) del[j] = 1;
	else return 0;
	return 1;
}

struct HM {
	int hd[INF + 1], ne[N], s[N], L;
	void init() {
		memset(hd, -1, sizeof(hd));
		L = 0;
	}
	void upd(int u) {
		int p = rdx[nd[u].x / ::s] ^ rdy[nd[u].y / ::s];
		s[L] = u; ne[L] = hd[p]; hd[p] = L++;
	}
	void Del(int x, int y, int u) {
		int p = rdx[x] ^ rdy[y];
		int pre = -1;
		for(int i = hd[p]; ~i; i = ne[i]) {
			int v = s[i];
			if(!check(u, v)) {
				if(~pre) {
					ne[pre] = i;
				} else {
					hd[p] = i;
				}
				pre = i;
			}
		}
		if(~pre) ne[pre] = -1;
		else hd[p] = -1;
	}
}hm;
void add(int u) {
	ans.pb(u);
	int x = nd[u].x / s, y = nd[u].y / s;
	rep(dx, -1, 2) if(x + dx >= 0) rep(dy, -1, 2) if(y + dy >= 0) hm.Del(x + dx, y + dy, u);
}
void solve() {
	hm.init();
	ans.clear();
	scanf("%d%d", &n, &s); s2 = 2ll * s * s;
	p = read(3);
	rep(i, 1, n + 1) scanf("%d%d", &nd[i].x, &nd[i].y), nd[i].val = read(6), del[i] = 0;
	rep(i, 1, n + 1) cur[i] = i;
	sort(cur + 1, cur + 1 + n, cmp);
	rep(i, 1, n + 1) hm.upd(i);
	rep(i, 1, n + 1) {
		if(!del[cur[i]]) add(cur[i]);
	}
	sort(all(ans));
	cout << sz(ans) << endl;
	rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
}

int main() {
	srand(time(0));
	rep(i, 0, M) rdx[i] = rand() & INF, rdy[i] = rand() & INF;
	int T; scanf("%d", &T);
	rep(i, 1, T + 1) {
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
