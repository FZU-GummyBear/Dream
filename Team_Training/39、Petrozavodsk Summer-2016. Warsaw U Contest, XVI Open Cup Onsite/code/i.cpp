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

const int N = 1010101;

int n, k, A[N], B[N], K[N], o[N], ans[N], res, p[N], q[N];
unordered_map<int, vi> vec;
map<int, priority_queue<pii> > que;

bool cmp(int i, int j) { return A[i] < A[j]; }
bool cmp2(int i, int j) { return o[i] > o[j]; }
bool cmp3(int i, int j) { return B[i] > B[j]; }

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> k;
  rep(i, 1, n + 1) cin >> A[i] >> B[i] >> K[i], vec[K[i]].pb(i);
  bool ok = 1;
  for(auto &u : vec) {
    auto &v = u.se; sort(all(v), cmp);
    priority_queue<pii> que;
    for(int i = 0, j = -1; i < sz(v) || !que.empty(); ++j) {
      if(que.empty()) j = A[v[i]];
      while(i < sz(v) && A[v[i]] <= j) {
      	que.push(mp(-B[v[i]], v[i]));
      	++i;
      }
      auto t = que.top(); que.pop(); o[t.se] = j;
      if(j > B[t.se]) { ok = 0; break; }
    }
    if(!ok) break;
  }
  if(!ok) { cout << "NIE" << endl; return 0; }
  rep(i, 1, n + 1) p[i] = q[i] = i;
  sort(p + 1, p + 1 + n, cmp2);
  sort(q + 1, q + 1 + n, cmp3);
  for(int i = 1, j = 1; i <= n; ++i) {
    if(ans[p[i]]) continue;
    while(j <= n && B[q[j]] >= o[p[i]]) {
      int t = q[j];
      if(!ans[t]) que[K[t]].push(mp(o[t], t));
      ++j;
    }
    ++res; int t = o[p[i]];
    vi del;
    for(auto &u : que) {
      auto v = u.se.top(); u.se.pop();
      if(sz(u.se) == 0) del.pb(u.fi);
      ans[v.se] = t;
    }
    for(auto u : del) que.erase(u);
  }
  cout << res << endl;
  rep(i, 1, n + 1) cout << ans[i] << endl;
  return 0;
}
