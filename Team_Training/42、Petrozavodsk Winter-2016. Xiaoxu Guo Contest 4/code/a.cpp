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
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020, B = 120;

int n, fail[N], rt, cnt[N], dep[N], pre[N][22];
unordered_map<int, int> ne[N];
vi vec[N];

void ini() { fail[0] = fail[N - 1] = N - 1; rep(i, 0, 22) pre[N - 1][i] = N - 1;}
bool check(int u, int v) {
  if(dep[u] == -1) return 0;
  per(i, 0, 22) if(dep[pre[v][i]] >= dep[u]) v = pre[v][i];
  return u == v;
}
int calc(int p, int c) {
  if(cnt[c] >= B) {
    while(p != N - 1 && !ne[p].count(c)) p = fail[p];
    return (ne[p].count(c) ? ne[p][c] : 0);
  } else {
    int ans = -1, d = -1;
    for(auto u : vec[c]) {
      if(check(u, p) && dep[u] > d) {
	ans = u, d = dep[u];
      }
    }
    return (ans != -1 ? ne[ans][c] : 0);
  }
}
void upd(int u, int fa) {
  dep[u] = dep[fa] + 1;
  pre[u][0] = fa;
  rep(i, 1, 22) pre[u][i] = pre[pre[u][i - 1]][i - 1];
}
void build() {
  vi v; v.pb(rt);
  rep(i, 0, sz(v)) {
    int c = v[i];
    for(auto t : ne[c]) {
      v.pb(t.se);
      fail[t.se] = calc(fail[c], t.fi);
      upd(t.se, fail[t.se]);
    }
  }
}

int p[N], c[N];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, n + 1) cin >> p[i];
  memset(dep, -1, sizeof(dep)); dep[0] = 1;
  rep(i, 1, n + 1) cin >> c[i], ++cnt[c[i]];
  rep(i, 1, n + 1) ne[p[i]][c[i]] = i, vec[c[i]].pb(p[i]);
  rep(i, 1, n + 1) {
    sort(all(vec[i]));
    vec[i].erase(unique(all(vec[i])), vec[i].end());
  }
  ini();
  build();
  rep(i, 1, n + 1) cout << fail[i] << " \n"[i == n];
  return 0;
}
