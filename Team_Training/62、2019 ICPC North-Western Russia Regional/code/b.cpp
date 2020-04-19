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

const int N = 4e7;

int n;
pair<db, int> a[101010];
int dp[101010], pre[101010];

struct FW {
#define lb(x) (x & -x)
	int ma[N], id[N];
	void upd(int p, int c, int ind) {
		for( ; p <= N; p += lb(p)) if(ma[p] <  c) {
			ma[p] = c, id[p] = ind;
		}
	}
	int qry(int p) {
		int ans = 0, val = 0;
		for( ; p; p ^= lb(p)) if(val < ma[p]) val = ma[p], ans = id[p];
		return ans;
	}
}fw;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int st = 51819;
	while(st < N - 10) a[++n] = mp(-sin(st), st), st += 710;
	sort(a + 1, a + 1 + n);
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	rep(i, 1, n + 1) {
		int x = a[i].se;
		int j = fw.qry(x);
		pre[i] = j;
		dp[i] = dp[j] + 1;
		fw.upd(x, dp[i], i);
	}
	int now = fw.qry(N - 1);
	vi ans;
	while(now) {
		ans.pb(now);
		now = pre[now];
	}
	reverse(all(ans));
	vi res;
	for(auto u : ans) {
		int x = a[u].se;
		res.pb(x);
	}
	int tn; cin >> tn;
	db pre = 1;
	rep(i, 0, tn) {
		db x = sin(res[i]);
		assert(pre > x); pre = x;
		cout << res[i] << endl;
	}
	return 0;
}
