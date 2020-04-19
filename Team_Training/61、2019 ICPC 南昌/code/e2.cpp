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

const int N = 505050;

int n, m, k, pre[N];
bool vis[N];
pair<int, pii> e[N];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
void join(int x, int y) { pre[find(x)] = find(y); }

ll solve() {
	scanf("%d%d%d", &n, &m, &k);
	ll ans = 0;
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, m + 1) vis[i] = 0;
	int ct = 0;
	rep(i, 1, m + 1) {
		int u, v, w, c; 
		scanf("%d%d%d%d", &u, &v, &w, &c);
		if(c) {
			e[++ct] = mp(w, mp(u, v));
		} else {
			ans += w;
			join(u, v);
		}
	}
	sort(e + 1, e + 1 + ct);
	reverse(e + 1, e + 1 + ct);
	rep(i, 1, ct + 1) {
		int u = e[i].se.fi, v = e[i].se.se;
		if(find(u) != find(v)) {
			if(!k) return -1;
			--k; join(u, v); ans += e[i].fi; vis[i] = 1;
		}
	}
	int t = find(1);
	rep(i, 2, n + 1) if(find(i) != t) return -1;
	rep(i, 1, ct + 1) if(!vis[i] && k) {
		--k; ans += e[i].fi;
	}
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) printf("%lld\n", solve());
	return 0;
}
