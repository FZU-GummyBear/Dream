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

const int P = 1e9 + 7;

int m, n = 4;

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
  static const int N = 11;
  int a[N][N];
  inline void init() {
    rep(i, 0, n) rep(j, 0, n) a[i][j] = 0;
  }
  inline void e() {
    rep(i, 0, n) a[i][i] = 1;
  }
  inline void set() {
    init();
    a[0][0] = 3;
    a[0][1] = P - 2;
    a[0][2] = 1;
    a[0][3] = P - 1;
    a[1][0] = a[2][1] = a[3][2] = 1;
  }
  void print() {
    rep(i, 0, n) {
      rep(j, 0, n) cout << a[i][j] << " "; cout << endl;
    }
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
};

Mat kpow(Mat a, int b) {
  Mat r; r.init(); r.e();
  while(b) {
    if(b & 1) r = r * a;
    a = a * a;
    b >>= 1;
  }
  return r;
}
vi ans;
int solve() {
  if(m == 1) return 1; --m;
  if(m <= 4) return ans[4 - (m)];
  Mat a; a.set();
  a = kpow(a, m - 4);
  /*
  a.print();
  vi t = a * ans;
  return t[0];
  */
  int res = 0;
  rep(i, 0, n) res = add(res, mul(a.a[0][i], ans[i]));
  return res;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  ans.pb(2);
  ans.pb(6);
  ans.pb(16);
  ans.pb(36);
  reverse(all(ans));
  while(cin >> m) cout << solve() << endl;
  return 0;
}
