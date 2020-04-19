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

const int N = 222, P = 1e9 + 7;

int n, cnt[N], sum[N];
int f[N][N][N];

int add(int a, int b) {
  if((a += b) >= P) a -= P;
  return a;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, n + 1) {
    int x; cin >> x;
    if(~x) ++cnt[x];
  }
  rep(i, 1, N) sum[i] = cnt[i] + sum[i - 1];
  f[0][0][0] = 1;
  rep(i, 0, N - 1) rep(j, 0, n + 1) rep(k, 0, n + 1) if(f[i][j][k]) {
    rep(t, 0, n + 1) if(j + t >= sum[i + 1] && j + t <= n && t <= cnt[i + 1] + k) {
      f[i + 1][j + t][t] = add(f[i + 1][j + t][t], f[i][j][k]);
    }
  }
  int ans = 0;
  rep(i, 0, N) rep(j, 0, N) ans = add(ans, f[N - 1][i][j]);
  cout << ans << endl;
  return 0;
}
