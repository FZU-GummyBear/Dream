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

const int N = 3e6 + 7;

int n, id[pw(24)], who[N], m, L, dp[N], val[22][22];	  
char str[22][22];
pii vec[22];
int top, tt[22];
inline void upd(int u, int c) {
  u = id[u];
  dp[u] = min(dp[u], c);
}
int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n; m = n << 1;
  rep(i, 1, n + 1) cin >> (str[i] + 1);
  rep(i, 1, n + 1) rep(j, 1, n + 1) cin >> val[i][j];
  int a[24] = {0};
  rep(i, 0, n) a[i + n] = 1;
  do { 
    int x = 0;
    rep(i, 0, m) x = x << 1 | a[i];
    id[x] = ++L;
    who[L] = x;
  } while(next_permutation(a, a + m));
  memset(dp, 0x3f, sizeof(dp));
  dp[1] = 0;
  rep(_, 1, L + 1) {
    int u = who[_], x = 0, y = 1;
    top = 0;
    per(i, 0, m) {
      int k = u >> i & 1, nk = i > 0 ? (u >> (i - 1) & 1) : -1;
      k ? ++y : ++x;
      if(!(!k && nk == 1)) continue;
      int xo = 1 << i ^ 1 << (i - 1);
      if(str[x][y] == '.') {
	upd(u ^ xo, dp[_]);
      } else {
	upd(u ^ xo, dp[_] + val[x][y]);
	rep(o, 0, top) {
	  short tx = vec[o].fi, ty = vec[o].se;
	  if(str[tx][ty] != str[x][y]) {
	    upd(u ^ xo ^ tt[o], dp[_] + abs(val[x][y] - val[tx][ty]));
	  }
	}
	tt[top] = xo;
	vec[top++] = mp(x, y);
      }
    }
  }
  cout << dp[L] << endl;
  return 0;
}
