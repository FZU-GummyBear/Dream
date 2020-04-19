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
typedef long double db;
typedef vector<int> vi;

const int N = 1010;
const db eps = 1e-8;

int sign(db x) {
  return (x > eps) - (x < -eps);
}

struct P {
  db x, y; 
  int a, b, id;
  P() {}
  P(db x, db y) : x(x), y(y) {}
  P(db x, db y, int a, int b) : x(x), y(y), a(a), b(b) {}
  void read() {
    int a, b; cin >> a >> b;
    x = a, y = b;
  }
  P operator + (const P &c) const { return P(x + c.x, y + c.y); }
  P operator - (const P &c) const { return P(x - c.x, y - c.y); }
  P operator * (const db &c) const { return P(x * c, y * c); }
  P operator / (const db &c) const { return P(x / c, y / c); }
  bool operator < (const P &c) const {
    if(sign(x - c.x)) return x < c.x;
    return y < c.y;
  }
};
struct L {
  P a, b;
  void read() { a.read(); b.read(); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }

int n, cntp, col[N * N], ans[N][N];
vi vec[N];
vector<L> ls;
P p[N * N];
vi g[N * N];

bool cmp(int i, int j) {
  return p[i] < p[j];
}

bool isLL(L l1, L l2, P &p) {
  db s1 = det(l2.b - l2.a, l1.a - l2.a);
  db s2 = -det(l2.b - l2.a, l1.b - l2.a);
  if(!(sign(s1 + s2))) return 0;
  p = (l1.a * s2 + l1.b * s1) / (s1 + s2);
  return 1;
}
void add(int u, int v) {
  g[u].pb(v);
  g[v].pb(u);
}
bool o2;
void dfs(int u) {
  for(auto v : g[u]) {
    if(col[v]) {
      if(col[v] == col[u]) o2 = 0;
    } else {
      col[v] = 3 - col[u];
      dfs(v);
    }
  }
}
int solve() {
  cin >> n; ls = vector<L>(n);
  rep(i, 0, n) ls[i].read(), vec[i].clear();
  cntp = 0;
  rep(i, 0, n) rep(j, i + 1, n) {
    P t; ans[i][j] = -1;
    if(isLL(ls[i], ls[j], t)) {
      p[++cntp] = P(t.x, t.y, i, j);
      vec[i].pb(cntp);
      vec[j].pb(cntp);
      g[cntp].clear();
      ans[i][j] = 1;
      col[cntp] = 0;
    }
  }
  bool ok = 0;
  rep(i, 0, n) {
    sort(all(vec[i]), cmp);
    rep(j, 1, sz(vec[i])) {
      add(vec[i][j], vec[i][j - 1]);
      ok = 1;
    }
  }
  if(!ok) return 1;
  o2 = 1;
  rep(i, 1, cntp + 1) if(!col[i]) col[i] = 1, dfs(i);
  if(o2) {
    rep(i, 1, cntp + 1) ans[p[i].a][p[i].b] = col[i];
    return 2;
  }
  rep(i, 1, cntp + 1) p[i].id = i;
  sort(p + 1, p + 1 + cntp);
  rep(i, 1, cntp + 1) col[i] = 0;
  rep(i, 1, cntp + 1) {
    bool vis[4] = {0};
    for(auto j : g[p[i].id]) vis[col[j]] = 1;
    rep(j, 1, 4) if(!vis[j]) {
      col[p[i].id] = j;
      break;
    }
  }
  rep(i, 1, cntp + 1) ans[p[i].a][p[i].b] = col[p[i].id];
  return 3;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int T; cin >> T;
  while(T--) {
    cout << solve() << endl;
    rep(i, 0, n) rep(j, i + 1, n) cout << ans[i][j] << " \n"[j == n - 1];
  }
  return 0;
}
