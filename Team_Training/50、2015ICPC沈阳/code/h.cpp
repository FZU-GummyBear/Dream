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
typedef pair<short, short> pii;
typedef double db;
typedef vector<int> vi;

static const int N = 3030, D = 1001;

int n, m, o, l, dx, dy, pre[N * N];
pii a[N], g[N][N], ans[N][N];
string s;

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x), y = find(y);
  pre[y] = x;
}
void add(int x, int y, pii c) {
  if(g[x][y].fi) {
    join((g[x][y].fi - 1) * m + g[x][y].se, (c.fi - 1) * m + c.se);
  } else {
    g[x][y] = c;
  }
}
ll sqr(int x) {
  return x * 1ll * x;
}
ll solve() {
  cin >> n >> m >> o >> l;
  rep(i, 0, N * N) pre[i] = i;
  rep(i, 0, N) rep(j, 0, N) ans[i][j] = g[i][j] = mp(0, 0);
  rep(i, 1, n + 1) rep(j, 1, m + 1) g[i + D][j + D] = mp(i, j);
  dx = dy = D;
  rep(i, 1, o + 1) {
    int x, y; cin >> x >> y;
    a[i] = mp(x, y);
    g[x + D][y + D] = mp(0, 0);
    ans[x][y] = mp(-1, -1);
  }
  cin >> s;
  for(auto u : s) {
    if(u == 'U') {
      ++dx;
      rep(i, 1, o + 1) {
      	int x = a[i].fi, y = a[i].se;
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx + 1, ty, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
      int x = 0;
      rep(y, 1, m + 1) {
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx + 1, ty, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
    } else if(u == 'D') {
      --dx;
      rep(i, 1, o + 1) {
      	int x = a[i].fi, y = a[i].se;
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx - 1, ty, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
      int x = n + 1;
      rep(y, 1, m + 1) {
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx - 1, ty, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
    } else if(u == 'L') {
      ++dy;
      rep(i, 1, o + 1) {
      	int x = a[i].fi, y = a[i].se;
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx, ty + 1, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
      int y = 0;
      rep(x, 1, n + 1) {
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx, ty + 1, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
    } else {
      --dy;
      rep(i, 1, o + 1) {
      	int x = a[i].fi, y = a[i].se;
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx, ty - 1, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
      int y = m + 1;
      rep(x, 1, n + 1) {
      	int tx = x + dx, ty = y + dy;
      	if(g[tx][ty].fi) {
      	  add(tx, ty - 1, g[tx][ty]);
      	  g[tx][ty] = mp(0, 0);
	}
      }
    }
  }
  rep(i, 0, N) rep(j, 0, N) if(g[i][j].fi) {
    int x = g[i][j].fi, y = g[i][j].se;
    ans[x][y] = mp(i - dx, j - dy);
  }
  ll res = 0;
  rep(i, 1, n + 1) rep(j, 1, m + 1) if(~ans[i][j].fi) {
    if(!ans[i][j].fi) {
      int t = find((i - 1) * m + j);
      ans[i][j] = ans[(t - 1) / m + 1][(t - 1) % m + 1];
    }
    res += sqr(i - ans[i][j].fi) + sqr(j - ans[i][j].se);
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  db x = sizeof(ans) * 2 + sizeof(pre);
 // de(x / 1024);
  int T; cin >> T;
  rep(ca, 1, T + 1) {
    cout << "Case #" << ca << ": " << solve() << endl;
  }
  return 0;
}
