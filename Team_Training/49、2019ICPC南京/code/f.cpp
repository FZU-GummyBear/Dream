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
int ans[N];
int ct;

struct Node {
  int x, a, b, ty, o;
  Node() {}
  Node(int x, int a, int b, int ty = 0) : x(x), a(a), b(b), ty(ty) {}
}nd[N * 3], tmp[N * 3];

void dfs(int u) {
  st[u] = ++dfn;
  rep(i, 0, 26) if(ne[u][i]) dfs(ne[u][i]);
  ed[u] = dfn;
}
struct FW {
#define lb(x) (x & -x)
  int a[N];
  void upd(int p, int c) {
    if(!p) return ;
    for(; p <= n; p += lb(p)) a[p] += c;
  }
  int qry(int p) {
    int ans = 0;
    for(; p; p ^= lb(p)) ans += a[p];
    return ans;
  }
  void init(int p) {
    if(!p) return ;
    for(; p <= n; p += lb(p)) a[p] = 0;
  }
}fw;
void dfs(int l, int r) {
  if(l >= r) return ;
  int m = l + r >> 1;
  dfs(l, m); dfs(m + 1, r);
  rep(i, l, r + 1) nd[i].o = i > m;
  int p = l, q = m + 1, k = l;
  while(p <= m && q <= r) {
    if(nd[p].x <= nd[q].x) tmp[k++] = nd[p++];
    else tmp[k++] = nd[q++];
  }
  while(p <= m) tmp[k++] = nd[p++];
  while(q <= r) tmp[k++] = nd[q++];
  int ed = l - 1;
  per(i, l, r + 1) if(tmp[i].o && tmp[i].ty) {
    ed = i; break;
  }
  rep(i, l, r + 1) {
    nd[i] = tmp[i];
    if(nd[i].o == 0) {
      if(nd[i].ty == 0 && i <= ed) {
      	fw.upd(nd[i].a, 1);
      	fw.upd(nd[i].b, -1);
      }
    } else {
      if(nd[i].ty) {
      	int t = nd[i].ty;
      	ans[t] += fw.qry(nd[i].a);
      	ans[t] -= fw.qry(nd[i].b);
      }
    }
  }
  rep(i, l, ed + 1) if(nd[i].o == 0 && nd[i].ty == 0) fw.init(nd[i].a), fw.init(nd[i].b);
}

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
  int las = 0;
  rep(i, 1, n + 1) {
    int p = End[i];
    nd[++ct] = Node(st[p], i, 0);
  }
  memset(ans, -1, sizeof(ans));
  rep(i, 1, m + 1) {
    int o; cin >> o;
    if(o == 1) {
      int x, y; cin >> x >> y;
      int p = End[x], q = End[y];
      nd[++ct] = Node(st[p], y, x);
      nd[++ct] = Node(st[q], x, y);
      swap(End[x], End[y]);
    } else {
      string s; int k, l, r; cin >> s >> k >> l >> r;
      int p = rt;
      rep(t, 0, k) p = ne[p][s[t] - 'a'];
      ans[i] = 0;
      if(p) {
      	int L = st[p], R = ed[p];
      	--L, --l;
      	nd[++ct] = Node(R, r, l, i);
      	nd[++ct] = Node(L, l, r, i);
      	las = ct;
      }
    }
  }
  dfs(1, las);
  rep(i, 1, m + 1) if(~ans[i]) cout << ans[i] << endl;
  return 0;
}
