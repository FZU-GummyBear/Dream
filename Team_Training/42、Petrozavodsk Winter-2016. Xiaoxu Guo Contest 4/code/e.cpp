#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<assert.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;
const db eps = 1e-6, pi = acos(-1.);

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
  db x, y;
  P() {}
  P(db x, db y) : x(x), y(y) {}
  void read() { cin >> x >> y; }
  void print() { cout << x << " " << y << endl; }
  P operator + (const P &c) const { return P(x + c.x, y + c.y); }
  P operator - (const P &c) const { return P(x - c.x, y - c.y); }
  P operator * (const db &c) const { return P(x * c, y * c); }
  P operator / (const db &c) const { return P(x / c, y / c); }
  bool operator < (const P &c) const {
    if(x != c.x) return x < c.x;
    return y < c.y;
  }
  int quad() const { return sign(y) > 0 || (sign(y) == 0 && sign(x) >= 0); }
  P rot90() { return P(-y, x); }
  P rot(db a) { return P(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x); }
  db len2() { return x * x + y * y; }
  db len() { return sqrt(len2()); }
  P norm() { return *this / len(); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
db dot(P o, P a, P b) { return dot(a - o, b - o); }
P isLL(db a0, db b0, db c0, db a1, db b1, db c1) {
  db d = a0 * b1 - a1 * b0;
  return P(b0 * c1 - b1 * c0, a1 * c0 - a0 * c1) / d;
}
vector<P> convexHull(vector<P> ps) {
  int n = sz(ps); if(n <= 1) return ps;
  sort(all(ps));
  vector<P> qs;
  for(int i = 0; i < n; qs.pb(ps[i++])) {
    while(sz(qs) > 1 && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
  }
  for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
    while(sz(qs) > t && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
  }
  qs.pop_back(); return qs;
}

int n, m, a[N][3], p[N];
bool ban[N];
set<pii> st;

bool cmp(int i, int j) {
  if(ban[i] != ban[j]) return ban[i] < ban[j];
  return a[i][1] * 1ll * a[j][0] < a[j][1] * 1ll * a[i][0];
}

void solve() {
  cin >> n >> m;
  rep(i, 0, n) rep(j, 0, 3) cin >> a[i][j];
  rep(i, 0, n) {
    a[i][2] = -a[i][2];
    if(a[i][0] < 0) rep(j, 0, 3) a[i][j] = -a[i][j];
  }
  rep(i, 0, m) {
    int x, y; cin >> x >> y;
    --x, --y;
    ban[x] = ban[y] = 1;
    st.insert(mp(x, y));
    st.insert(mp(y, x));
  }
  rep(i, 0, n) p[i] = i;
  sort(p, p + n, cmp);
  vector<P> ps;
  rep(i, 0, n) {
    int u = p[i];
    if(ban[u]) break;
    int v = p[(i + 1) % n];
    if(ban[v]) v = p[0];
    if(u != v) ps.pb(isLL(a[u][0], a[u][1], a[u][2], a[v][0], a[v][1], a[v][2]));
  }
  rep(i, 0, n) if(ban[i]) {
    bool f = 1;
    P ma, mi;
    rep(j, 0, n) if(i != j && st.find(mp(i, j)) == st.end()) {
      if(f) {
      	ma = mi = isLL(a[i][0], a[i][1], a[i][2], a[j][0], a[j][1], a[j][2]);
      	f = 0;
      } else {
      	P t = isLL(a[i][0], a[i][1], a[i][2], a[j][0], a[j][1], a[j][2]);
      	if(t < mi) mi = t;
      	if(ma < t) ma = t;
      }
    }
    if(!f) ps.pb(ma), ps.pb(mi);
  }
  ps = convexHull(ps);
  db ans = 0;
  rep(i, 0, sz(ps)) ans += (ps[i] - ps[(i + 1) % sz(ps)]).len();
  cout << ans << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cout << setiosflags(ios::fixed);
  cout << setprecision(10);
  solve();
  return 0;
}
