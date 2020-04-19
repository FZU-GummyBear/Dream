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

const int N = 77, P = 1e9 + 7, MT = 2e6 + 6;

int n, m, T, k = 200;
string g[N];
vi cx[MT];
int tmp[202], in[N], sum[N], f[N][202];

inline int add(int a, int b) {
  if ((a += b) >= P) a -= P;
  return a;
}

inline int mul(int a, int b) {
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

struct Mat {
  int a[N][N];
  inline void init() {
    rep(i, 0, n) rep(j, 0, n) a[i][j] = 0;
  }
  inline void e() {
    rep(i, 0, n) a[i][i] = 1;
  }
  inline void set() {
    rep(i, 0, n) rep(j, 0, n) a[i][j] = mul(g[j][i] - '0', in[sum[j]]);
  }
  Mat operator * (const Mat &c) const {
    Mat res; res.init(); 
    rep(i, 0, n) rep(k, 0, n) if(a[i][k]) rep(j, 0, n) res.a[i][j] = add(res.a[i][j], mul(a[i][k], c.a[k][j]));
    return res;
  }
  vi operator * (const vi &c) const {
    vi res(n);
    rep(i, 0, n) rep(j, 0, n) res[i] = add(res[i], mul(a[i][j], c[j]));
    return res;
  }
}a[202];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> m >> T;
  rep(i, 0, n + 1) in[i] = kpow(i, P - 2);
  rep(i, 0, n) {
    cin >> g[i];
    rep(j, 0, n) sum[i] += g[i][j] - '0';
  }
  rep(i, 0, m) {
    int t, v; cin >> t >> v;
    cx[t].pb(v - 1);
  }
  a[0].init(); a[0].e(); a[1].set();
  rep(i, 2, k + 1) a[i] = a[i - 1] * a[1];
  rep(i, 0, n) {
    vi ans(n); ans[i] = 1;
    rep(j, 1, k + 1) ans = a[1] * ans, f[i][j] = ans.back();
  }
  int pre = -1; vi ans(n);
  ll res = 0;
  rep(i, 1, T + 1) if(sz(cx[i]) || i == T) {
    if(pre != -1) {
      int t = i - pre;
      while(t >= k) {
      	rep(j, 1, k + 1) tmp[j] = 0;
      	rep(i, 0, n) if(ans[i]) rep(j, 1, k + (t - k > 0)) {
      	  tmp[j] += mul(ans[i], f[i][j]);
      	  if(tmp[j] >= P) tmp[j] -= P;
	}
      	rep(j, 1, k + (t - k > 0)) res ^= tmp[j];
      	ans = a[k] * ans, t -= k;
      }
      if(t) {
      	rep(j, 1, t) tmp[j] = 0;
      	rep(i, 0, n) if(ans[i]) rep(j, 1, t) {
      	  tmp[j] += mul(ans[i], f[i][j]);
      	  if(tmp[j] >= P) tmp[j] -= P;
	}
      	rep(j, 1, t) res ^= tmp[j];
      	ans = a[t] * ans;
      }
    }
    for(auto v : cx[i]) ans[v] = add(ans[v], 1);
    res ^= ans.back();
    pre = i;
  }
  cout << res << endl;
  return 0;
}
