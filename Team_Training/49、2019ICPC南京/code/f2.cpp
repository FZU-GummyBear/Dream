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

int n, m;
int ne[N][26], L, rt;
int End[N];
int st[N], ed[N], dfn;
int root[N];
vi vec[N], add, sub;

void dfs(int u) {
  st[u] = ++dfn;
  rep(i, 0, 26) if(ne[u][i]) dfs(ne[u][i]);
  ed[u] = dfn;
}

struct Seg {
  static const int N = 4e7;
  int ls[N], rs[N], cnt[N], cntn;
  void upd(int &now, int pre, int p, int c, int l = 1, int r = n) {
    now = ++cntn;
    ls[now] = ls[pre];
    rs[now] = rs[pre];
    cnt[now] = cnt[pre] + c;
    if(l == r) return ;
    int mid = l + r >> 1;
    if(p <= mid) upd(ls[now], ls[pre], p, c, l, mid);
    else upd(rs[now], rs[pre], p, c, mid + 1, r);
  }
  int qry(int L, int R, int l = 1, int r = n) {
    if(L <= l && r <= R) {
      int ans = 0;
      for(auto rt : add) ans += cnt[rt];
      for(auto rt : sub) ans -= cnt[rt];
      return ans;
    }
    int mid = l + r >> 1, ans = 0;
    vi tadd = add, tsub = sub;
    if(L <= mid) {
      for(auto &rt : add) rt = ls[rt];
      for(auto &rt : sub) rt = ls[rt];
      ans += qry(L, R, l, mid);
    }
    if(R > mid) {
      add = tadd, sub = tsub;
      for(auto &rt : add) rt = rs[rt];
      for(auto &rt : sub) rt = rs[rt];
      ans += qry(L, R, mid + 1, r);
    }
    return ans;
  }
}seg;

struct FW {
#define lb(x) (x & -x)
  int rt[N];
  void upd(int P, int p, int c) {
    for( ; P <= L; P += lb(P)) seg.upd(rt[P], rt[P], p, c);
  }
  int qry(int L, int R, int l, int r) {
    add.clear(); sub.clear();
    add.pb(root[R]);
    for( ; R; R ^= lb(R)) add.pb(rt[R]);
    L--;
    if(L) {
      sub.pb(root[L]);
      for( ; L; L ^= lb(L)) sub.pb(rt[L]);
    }
    return seg.qry(l, r);
  }
}fw;

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> m;
  rt = ++L;
  rep(i, 1, n + 1) {
    string s; cin >> s;
    int p = rt;
    for(auto u : s) {
      int c = u - 'a';
      if(!ne[p][c]) ne[p][c] = ++L;
      p = ne[p][c];
    }
    End[i] = p;
  }
  dfs(1);
  rep(i, 1, n + 1) {
    int p = End[i];
    vec[st[p]].pb(i);
  }
  rep(i, 1, L + 1) {
    root[i] = root[i - 1];
    for(auto u : vec[i]) seg.upd(root[i], root[i], u, 1);
  }
  while(m--) {
    int o; cin >> o;
    if(o == 1) {
      int x, y; cin >> x >> y;
      int p = End[x], q = End[y];
      fw.upd(st[p], x, -1);
      fw.upd(st[p], y, 1);
      fw.upd(st[q], y, -1);
      fw.upd(st[q], x, 1);
      swap(End[x], End[y]);
    } else {
      string s; int k, l, r; cin >> s >> k >> l >> r;
      int p = rt;
      rep(i, 0, k) p = ne[p][s[i] - 'a'];
      if(p) {
      	cout << fw.qry(st[p], ed[p], l, r) << endl;
      } else {
      	cout << 0 << endl;
      }
    }
  }
  return 0;
}
