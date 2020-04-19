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

const int N = 101010, P = 1e9 + 7;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int n, f[N], h[N], s[N], pre[N], suf[N], pre2[N], suf2[N], w[N];
vi g[N];

void dfs(int u, int fa) {
	bool has = 0;
	rep(i, 0, sz(g[u])) if(g[u][i] == fa) { swap(g[u][i], g[u][0]); break; }
	for(auto v : g[u]) if(v != fa) dfs(v, u);
	pre[0] = suf[sz(g[u])] = 1; h[u] = 1;
	pre2[0] = suf2[sz(g[u])] = 1;
	rep(i, 1, sz(g[u])) {
		int v = g[u][i];
		pre[i] = mul(pre[i - 1], s[v]);
		pre2[i] = mul(pre2[i - 1], f[v]);
		h[u] = mul(h[u], f[v]);
		has = 1;
	}
	if(!has) { f[u] = w[u] = 0; h[u] = s[u] = 1; return ; }
	w[u] = 0;
	per(i, 1, sz(g[u])) {
		int v = g[u][i];
		suf[i] = mul(suf[i + 1], s[v]);
		suf2[i] = mul(suf2[i + 1], f[v]);
		h[u] = add(h[u], mul(pre2[i - 1], mul(add(h[v], w[v]), suf2[i + 1])));
		int res = mul(pre[i - 1], suf[i + 1]);
		res = add(res, -mul(pre2[i - 1], suf2[i + 1]));
		w[u] = add(w[u], mul(res, add(h[v], w[v])));
	}

	int cnt0 = 0;
	vi ind;
	for(auto v : g[u]) if(v != fa) {
		cnt0 += (s[v] == 0);
		if(s[v] == 0) ind.pb(v);
	}

	if(cnt0 >= 3) {
		f[u] = 0;
	} else if(cnt0 == 2) {
		f[u] = 1;
		for(auto v : g[u]) if(v != fa) {
			if(v == ind[0] || v == ind[1]) {
				f[u] = mul(f[u], add(h[v], w[v]));
			} else {
				f[u] = mul(f[u], s[v]);
			}
		}
	} else if(cnt0 == 1) {
		int tn = sz(g[u]) - 1;
		rep(i, 1, tn + 1) if(g[u][i] == ind[0]) { swap(g[u][i], g[u][tn]); break; }
		--tn;
		pre[0] = suf[tn + 1] = 1;
		rep(i, 1, tn + 1) {
			int v = g[u][i];
			pre[i] = mul(pre[i - 1], s[v]);
		}
		per(i, 1, tn + 1) {
			int v = g[u][i];
			suf[i] = mul(suf[i + 1], s[v]);
		}
		int tval = add(h[ind[0]], w[ind[0]]);
		f[u] = 0;
		rep(i, 1, tn + 1) {
			int v = g[u][i];
			int res = tval;
			res = mul(res, add(h[v], w[v]));
			res = mul(res, mul(pre[i - 1], suf[i + 1]));
			f[u] = add(f[u], res);
		}
	} else {
		int t = 0; f[u] = 0;
		for(auto v : g[u]) if(v != fa) {
			int k = mul(add(h[v], w[v]), kpow(s[v], P - 2));
			assert(s[v]);
			f[u] = add(f[u], mul(k, t));
			t = add(t, k);
		}
		for(auto v : g[u]) if(v != fa) f[u] = mul(f[u], s[v]);
	}

	s[u] = add(f[u], h[u]);
	//	dd(u), dd(f[u]), dd(h[u]), dd(w[u]), de(s[u]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	int rt = 0;
	rep(i, 1, n + 1) if(sz(g[i]) == 1) { rt = i; break; }
	g[rt].pb(0);
	dfs(rt, 0);
	cout << add(f[rt], h[rt]) << endl;
	return 0;
}
