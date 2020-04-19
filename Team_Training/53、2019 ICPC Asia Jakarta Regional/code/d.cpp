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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 505;

int n, m, k, ans[202020];
char s[N][N], tmp[202020];

/*
 * [0,L) , N-1 is virtual , 0 is rt
 * init!!
 * addition: end[] end[c] |= end[fail[c]]
 */
struct Trie{
	static const int N = 202020, M = 26;
	int ne[N][M] , fail[N] , fa[N] , rt , L;
	vi ed[N], g[N]; int cnt[N];
	void ini(){ fill_n(ne[fail[0] = N-1],M,0);L = 0;rt = newnode();}
	int newnode(){ fill_n(ne[L],M,0); ed[L].clear(); g[L].clear(); cnt[L] = 0; return L++; }
	void add(char *s, int ind){
		int p = rt;
		for(int i=0;s[i];++i){
			int c = s[i] - 'A';// modify
			if(!ne[p][c]) ne[p][c] = newnode() , fa[L-1] = p;
			p = ne[p][c];
		}
		ed[p].pb(ind);
	}
	void solve() {
		// guai
		rep(i, 0, n) rep(j, 0, m) {
			int p = rt;
			rep(k, 0, j + 1) p = ne[p][s[i][k] - 'A'];
			rep(k, i + 1, n) {
				p = ne[p][s[k][j] - 'A'];
				++cnt[p];
			}
		}
		// heng
		rep(i, 0, n) {
			int p = rt;
			rep(j, 0, m) p = ne[p][s[i][j] - 'A'], ++cnt[p];
		}
		// shu
		rep(j, 0, m) {
			int p = rt;
			rep(i, 0, n) p = ne[p][s[i][j] - 'A'], ++cnt[p];
		}
		// qu chong
		rep(i, 0, n) rep(j, 0, m) {
			int p = rt;
			rep(k, i, n) p = ne[p][s[k][j] - 'A'], --cnt[p];
		}
		dfs(rt);
	}
	void dfs(int u) {
		for(auto v : g[u]) {
			dfs(v); cnt[u] += cnt[v];
		}
		for(auto v : ed[u]) ans[v] = cnt[u];
	}
	void Build(){
		vi v;v.pb(rt);
		rep(i,0,sz(v)){
			int c = v[i];
			rep(i,0,M) ne[c][i] ?
				v.pb(ne[c][i]) , fail[ne[c][i]] = ne[fail[c]][i] :
				ne[c][i] = ne[fail[c]][i];
		}
		rep(i, 1, L) g[fail[i]].pb(i);
	}
}ac;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	rep(i, 0, n) cin >> s[i];
	ac.ini();
	rep(i, 1, k + 1) {
		cin >> tmp;
		ac.add(tmp, i);
	}
	ac.Build();
	ac.solve();
	rep(i, 1, k + 1) cout << ans[i] << endl;
	return 0;
}
