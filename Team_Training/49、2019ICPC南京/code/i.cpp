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

const int N = 101010, P = 1e9 + 7;

int n, a[N], cnt[N], ans, jc[N], pw[N], pw2[N];
unordered_map<ll, int> dp;

int add(int a, int b) {
  if((a += b) >= P) a -= P;
  return a;
}
int mul(int a, int b) {
  return 1ll * a * b % P;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  jc[0] = 1;
  rep(i, 1, N) jc[i] = mul(jc[i - 1], i);
  pw[0] = pw2[0] = 1;
  rep(i, 1, N) {
    pw[i] = mul(pw[i - 1], 233);
    pw2[i] = mul(pw2[i - 1], 153);
  }
  // read
  srand(time(0));
  cin >> n;
  rep(i, 0, n + 1) cin >> a[i], ++cnt[a[i]];
  // m
  int m = 0;
  per(i, 0, 51) if(cnt[i]) { m = i; break; }
  // que init
  vector<vi> que;
  vi s(m + 1); s[a[0]] = 1;
  dp[(ll)pw[a[0]] << 30 | pw2[a[0]]] = 1; que.pb(s);
  // cnt0
  int cnt0 = cnt[0] - (a[0] == 0);
  int res0 = 1;
  rep(i, 0, cnt0) res0 = mul(res0, n + 1 - cnt0 + i);
  // solve
  rep(i, 0, sz(que)) {
    auto u = que[i];
    int ma = 0, ct = 0, sum = 0;
    int hu = 0, hu2 = 0;
    rep(j, 1, m + 1) {
      if(cnt[j] - u[j]) ma = j;
      ct += u[j], sum += j * u[j];
      hu = add(hu, mul(pw[j], u[j]));
      hu2 = add(hu2, mul(pw2[j], u[j]));
    }
    if(sum >= ma) {
      cout << jc[n] << endl;
      return 0;
    }
    int dpu = dp[(ll)hu << 30 | hu2];
    auto v = u;
    rep(j, 1, sum + 1) if(cnt[j] - u[j]) {
      ++v[j];
      if(sum + j >= ma) {
      	// dpu * (cnt[j] - u[j]) * (n + 1 - ct - 1 - cnt0)! * res0
      	int res = mul(dpu, cnt[j] - u[j]);
      	res = mul(res, jc[n - ct - cnt0]);
      	res = mul(res, res0);
      	ans = add(ans, res);
      } else {
      	ll hv = (ll)add(hu, pw[j]) << 30 | add(hu2, pw2[j]);
      	if(dp.count(hv)) {
      	  dp[hv] = add(dp[hv], mul(dpu, (cnt[j] - u[j])));
	} else {
      	  dp[hv] = mul(dpu, (cnt[j] - u[j]));
      	  que.pb(v);
	}
      }
      --v[j];
    }
  }
  cout << ans << endl;
  return 0;
}
