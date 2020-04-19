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

const int N = 202020;

int n, m, k, a[N], b[N];
vi vec[N];
set<int> st[N];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> m >> k;
  rep(i, 1, m + 1) {
    int u, v; cin >> u >> v;
  }
  rep(i, 1, n + 1) cin >> a[i], st[a[i]].insert(i);
  rep(i, 1, n + 1) cin >> b[i], vec[b[i]].pb(i);
  vi que;
  rep(i, 1, k + 1) if(sz(st[i]) == 1) que.pb(i);
  rep(i, 0, sz(que)) {
    int col = que[i];
    if(!sz(st[col])) continue;
    int ind = *st[col].begin();
    for(auto j : vec[b[ind]]) if(j != ind) {
      st[a[j]].erase(st[a[j]].find(j));
      if(sz(st[a[j]]) == 1) que.pb(a[j]);
      a[j] = col;
      st[col].insert(j);
    }
  }
  cout << "TAK" << endl;
  rep(i, 1, n + 1) cout << a[i] << " \n"[i == n];
  return 0;
}
