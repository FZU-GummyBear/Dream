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
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 202020;

int n, w[N], a[N], par[N], id[N], who[N];
ll sum[N];
vi g[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
  static const int N = ::N << 2;
  ll sum[N], la[N];
  void build(int n) {
    fill_n(sum, n << 2 | 1, 0);
    fill_n(la, n << 2 | 1, 0);
  }
  void gao(int l, int r, int rt, ll c = 1) {
    sum[rt] += (::sum[r] - ::sum[l - 1]) * c;
    la[rt] += c;
  }
  void down(int l, int r, int rt, int mid) {
    if(!la[rt]) return ;
    gao(l, mid, ls, la[rt]);
    gao(mid + 1, r, rs, la[rt]);
    la[rt] = 0;
  }
  void up(int rt) {
    sum[rt] = sum[ls] + sum[rs];
  }
  void upd(int L, int R, int l = 1, int r = n, int rt = 1) {
    if(L <= l && r <= R) return gao(l, r, rt), void();
    int mid = l + r >> 1;
    down(l, r, rt, mid);
    if(L <= mid) upd(L, R, l, mid, ls);
    if(R > mid) upd(L, R, mid + 1, r, rs);
    up(rt);
  }
  ll qry(int L, int R, int l = 1, int r = n, int rt = 1) {
    if(L <= l && r <= R) return sum[rt];
    int mid = l + r >> 1;
    down(l, r, rt, mid);
    ll ans = 0;
    if(L <= mid) ans += qry(L, R, l, mid, ls);
    if(R > mid) ans += qry(L, R, mid + 1, r, rs);
    return ans;
  }
}seg;

struct HC {
  static const int N = ::N;
  int sz[N], wson[N], top[N], dep[N], _, par[N];
  void dfs(int c, int fa, vi g[]) {
    sz[c] = 1;
    par[c] = fa;
    dep[c] = dep[fa] + 1;
    int &s = wson[c] = top[c] = 0;
    for(auto t : g[c]) if(t != fa) {
      dfs(t, c, g);
      sz[c] += sz[t];
      if(sz[t] >= sz[s]) s = t;
    }
  }
  void dfs2(int c, int fa, vi g[]) {
    id[c] = ++_;
    who[_] = c;
    int s = wson[c];
    if(!top[c]) top[c] = c;
    if(s) top[s] = top[c], dfs2(s, c, g);
    for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
  }
  void build(vi g[]) {
    dfs(1, 0, g);
    _ = 0;
    dfs2(1, 0, g);
  }
  void solve() {
    seg.build(n);
    rep(i, 1, n) {
      int u = i;
      while(u) {
      	seg.upd(id[top[u]], id[u]);
      	u = par[top[u]];
      }
      u = i + 1; ll ans = 0;
      while(u) {
      	ans += seg.qry(id[top[u]], id[u]);
      	u = par[top[u]];
      }
      cout << ans << endl;
    }
  }
}hc;

void solve() {
  rep(i, 1, n + 1) cin >> w[i], g[i].clear();
  a[1] = w[1];
  rep(v, 2, n + 1) {
    int u; cin >> u;
    g[u].pb(v);
    par[v] = u;
    a[v] = w[v] - w[u];
  }
  hc.build(g);
  rep(i, 1, n + 1) sum[i] = sum[i - 1] + a[who[i]];
  hc.solve();
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  while(cin >> n) solve();
  return 0;
}
