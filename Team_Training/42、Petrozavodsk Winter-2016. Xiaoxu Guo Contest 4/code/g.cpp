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

const int N = 505;

int n, m, w[N], r[N], f[2][N][N];

void upd(int &a, int b) { if(a > b) a = b; }

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> m;
  rep(i, 1, n + 1) cin >> w[i];
  rep(i, 1, m + 1) cin >> r[i];
  sort(w + 1, w + 1 + n);
  reverse(w + 1, w + 1 + n);
  memset(f, 0x3f, sizeof(f));
  int ans = f[0][0][0], o; f[o = 0][0][1] = 0;
  rep(i, 0, n + 1) {
    memset(f[o ^ 1], 0x3f, sizeof(f[0]));
    rep(j, 0, m + 1) rep(k, 1, n + 1) {
      if(i < n && j) upd(f[o ^ 1][j][k - 1], f[o][j][k] + w[i + 1] * j);
      if(j + 1 <= m) upd(f[o][j + 1][min(n, k * r[j + 1])], f[o][j][k]);
    }
    o ^= 1;
  }
  rep(i, 0, N) rep(j, 0, N) upd(ans, f[o ^ 1][i][j]);
  cout << ans << endl;
  return 0;
}
