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

const int N = 2020;

int n, p[N], a[N], rk[N], b[N], pre[N][N];
ll ans;

bool cmp(int i, int j) {
  return p[i] < p[j];
}

int qry(int a, int b, int l, int r) {
  if(l > r || a > b) return 0;
  int R = pre[r][b] - pre[r][a - 1];
  int L = pre[l - 1][b] - pre[l - 1][a - 1];
  return R - L;
}
void solve() {
  if(rk[1] == 1) {
    if(rk[2] == 2) {
      if(rk[3] == 3) {
      	//1234 23
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] < a[j]) ans += qry(1, a[i] - 1, 1, i - 1) * 1ll * qry(a[j] + 1, n, j + 1, n);
      } else {
      	//1243 24
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] < a[j]) ans += qry(1, a[i] - 1, 1, i - 1) * 1ll * qry(a[i] + 1, a[j] - 1, j + 1, n);
      }
    } else if(rk[2] == 3) {
      if(rk[3] == 2) {
      	//1324 23
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] > a[j]) ans += qry(1, a[j] - 1, 1, i - 1) * 1ll * qry(a[i] + 1, n, j + 1, n);
      } else {
      	//1342 23
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] > a[j]) ans += qry(1, a[j] - 1, 1, i - 1) * 1ll * qry(a[i] + 1, n, i + 1, j - 1);
      }
    } else {
      if(rk[3] == 2) {
      	//1423 24
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] > a[j]) ans += qry(1, a[j] - 1, 1, i - 1) * 1ll * qry(a[j] + 1, a[i] - 1, j + 1, n);
      } else {
      	//1432 24
      	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] > a[j]) ans += qry(1, a[j] - 1, 1, i - 1) * 1ll * qry(a[j] + 1, a[i] - 1, i + 1, j - 1);
      }
    }
  } else {
    ll t = 0;
    rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] < a[j]) t += qry(a[i] + 1, a[j] - 1, 1, i - 1) * 1ll * qry(a[j] + 1, n, i + 1, j - 1);
    if(rk[2] == 1) {
      //2143 13
      ans = t;
    } else {
      //2413 23
      rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] < a[j]) ans += qry(1, a[i] - 1, i + 1, j - 1) * 1ll * qry(a[j] + 1, n, i + 1, j - 1);
      ans -= t;
    }
  }
}
int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, 5) cin >> p[i], b[i] = i;
  sort(b + 1, b + 5, cmp);
  rep(i, 1, 5) rk[b[i]] = i;
  rep(i, 1, n + 1) cin >> a[i];
  if(rk[1] >= 3) {
    rep(i, 1, 5) rk[i] = 5 - rk[i];
    rep(i, 1, n + 1) a[i] = n + 1 - a[i];
  }
  if(rk[1] == 2 && rk[4] == 1) {
    reverse(rk + 1, rk + 5);
    reverse(a + 1, a + 1 + n);
  }
  if(rk[1] == 2 && rk[4] == 4) {
    reverse(rk + 1, rk + 5);
    reverse(a + 1, a + 1 + n);
    rep(i, 1, 5) rk[i] = 5 - rk[i];
    rep(i, 1, n + 1) a[i] = n + 1 - a[i];
  }
  rep(i, 1, n + 1) {
    rep(j, 1, n + 1) pre[i][j] = pre[i - 1][j];
    rep(j, a[i], n + 1) pre[i][j]++;
  }
  solve();
  cout << ans << endl;
  return 0;
}
