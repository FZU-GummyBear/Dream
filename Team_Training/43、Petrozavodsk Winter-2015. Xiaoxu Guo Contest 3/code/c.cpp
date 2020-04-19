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

const int N = 2020, MOD = 1e9 + 7;

int add(int a, int b) {
  if((a += b) >= MOD) a -= MOD;
  return a < 0 ? a + MOD : a;
}
int mul(int a, int b) { return 1ll * a * b % MOD; }

struct P {
  ll x, y;
  P() {}
  P(ll x, ll y) : x(x), y(y) {}
  void read() { cin >> x >> y; }
  bool operator == (const P &c) const { return x == c.x && y == c.y; }
  bool operator != (const P &c) const { return !(*this == c); }
  P operator + (const P &c) const { return P(x + c.x, y + c.y); }
  P operator - (const P &c) const { return P(x - c.x, y - c.y); }
  bool operator < (const P &c) const {
    if(x != c.x) return x < c.x;
    return y < c.y;
  }
};

ll dot(P a, P b) { return a.x * b.x + a.y * b.y; }
ll det(P a, P b) { return a.x * b.y - a.y * b.x; }

int n, ans, pw[N];
P p[N];

bool cmp(P a, P b) { 
  bool o = P(0, 0) < a, t = P(0, 0) < b;
  if(o != t) return o < t;
  return det(a, b) > 0;
}
int calc(int x) {
  if(x < 0) x += n;
  return x;
}
void solve(int s) {
  vector<P> q;
  int cnt = 0;
  rep(i, 0, n) {
    if(p[i] != p[s]) q.pb(p[i] - p[s]);
    else if(i > s) ++cnt;
  }
  sort(all(q), cmp);
  vector<pii> vec;
  int pre = 0, n = sz(q);
  rep(i, 1, n + 1) {
    if(i == n || !(det(q[i], q[i - 1]) == 0 && dot(q[i], q[i - 1]) > 0)) {
      vec.pb(mp(pre, i - 1));
      pre = i;
    }
  }
  int t = sz(vec);
  rep(i, 0, n) q.pb(q[i]);
  rep(i, 0, t) vec.pb(mp(vec[i].fi + n, vec[i].se + n));
  vec.pb(mp(n << 1, n << 1));
  for(int i = 0, j = 1; i < t; ++i) {
    if(i == j) ++j;
    while(det(q[vec[i].fi], q[vec[j].fi]) > 0) ++j;
    rep(k, 0, vec[i].se - vec[i].fi + 1) ans = add(ans, pw[vec[j].fi - 1 - vec[i].se + k + cnt]);
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  pw[0] = 1; rep(i, 1, N) pw[i] = mul(pw[i - 1], 2);
  cin >> n;
  rep(i, 0, n) p[i].read();
  rep(i, 0, n) solve(i);
  int cnt = 0;
  sort(p, p + n);
  rep(i, 0, n) {
    ++cnt;
    if(i == n - 1 || p[i] != p[i + 1]) ans = add(ans, add(pw[cnt], -1)), cnt = 0;
  }
  cout << ans << endl;
  return 0;
}
