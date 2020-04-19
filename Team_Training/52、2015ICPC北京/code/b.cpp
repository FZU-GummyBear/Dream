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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int st[] = {4, 3, 2, 1, 0, 1, 2, 3, 4};
int ed[] = {6, 7, 8, 9, 10, 9, 8, 7, 6};
int river = 10;
int dx[] = {0, -1, -1, 0, 1, 1};
int dy[] = {2, 1, -1, -2, -1, 1};
int dx2[] = {1, -1, -2, -1, 1, 2};
int dy2[] = {3, 3, 0, -3, -3, 0};
bool cane[9][22], canm[9][22], cang[9][22], vish[9][22];

bool iss(char s) { return 'a' <= s && s <= 'z'; }
bool isb(char s) { return 'A' <= s && s <= 'Z'; }
bool over(int x, int y) { return x < 0 || x >= 9 || y < 0 || y >= 22; }
bool isl(char g[][22], int x, int y) { return !over(x, y) && (iss(g[x][y]) || isb(g[x][y])); }
bool iss(char g[][22], int x, int y) { return !over(x, y) && iss(g[x][y]); }
bool jiang(char g[][22], int nx, int ny) { return !over(nx, ny) && g[nx][ny] == 'g'; }
bool check(char g[][22]) {
  rep(i, 0, 9) {
    for(int l = 0, r = 21; l < r; ++l, --r) swap(g[i][l], g[i][r]);
    rep(j, 0, 22) {
      if(iss(g[i][j])) g[i][j] += 'A' - 'a';
      else if(isb(g[i][j])) g[i][j] += 'a' - 'A';
    }
  }
  rep(i, 0, 9) rep(j, 0, 22) {
    if(g[i][j] == 'S') {
      if(jiang(g, i, j + 2)) return 1;
      if(j >= river) {
	if(jiang(g, i - 1, j + 1)) return 1;
	if(jiang(g, i + 1, j + 1)) return 1;
      }
    } else if(g[i][j] == 'H') {
      rep(d, 0, 6) {
	int x = i + dx[d], y = j + dy[d];
	if(over(x, y) || g[x][y] != ' ') continue;
	rep(t, 0, 2) {
	  int nd = (d + t) % 6;
	  if(jiang(g, x + dx2[nd], y + dy2[nd])) return 1;
	}
      }
    } else if(g[i][j] == 'C') {
      rep(d, 0, 6) {
	int x = i, y = j;
	while(1) {
	  x += dx[d], y += dy[d];
	  if(jiang(g, x, y)) return 1;
	  if(over(x, y) || g[x][y] != ' ') break;
	}
      }
    } else if(g[i][j] == 'A') {
      // leap 
      rep(d, 0, 6) {
	int x = i, y = j;
	while(1) {
	  x += dx[d], y += dy[d];
	  if(over(x, y) || isl(g, x, y)) break;
	}
	if(!isl(g, x, y)) continue;
	int nx = x, ny = y;
	while(1) {
	  nx += dx[d], ny += dy[d];
	  if(over(nx, ny) || isl(g, nx, ny)) break;
	}
	if(!iss(g, nx, ny)) continue;
	if(jiang(g, nx, ny)) return 1;
      }
    } else if(g[i][j] == 'G') {
      int x = i, y = j;
      while(1) {
	y += 2;
	if(jiang(g, x, y)) return 1;
	if(over(x, y) || g[x][y] != ' ') break;
      }
    }
  }
  return 0;
}
// (x, y) -> (nx, ny) ' ' or iss
bool check(char g[][22], int x, int y, int nx, int ny) {
  if(over(nx, ny) || g[nx][ny] == '#' || isb(g[nx][ny])) return 0;
  char tg[9][22];
  rep(i, 0, 9) rep(j, 0, 22) tg[i][j] = g[i][j];
  tg[nx][ny] = g[x][y], tg[x][y] = ' ';
  return !check(tg);
}

int solve() {
  int ans = 0;
  char g[9][22]; rep(i, 0, 9) rep(j, 0, 22) g[i][j] = '#';
  rep(i, 0, 9) {
    int x = st[i];
    rep(j, 0, ed[i] + 1) g[i][x] = ' ', x += 2;
  }
  int n; cin >> n;
  rep(i, 0, n) {
    string s1, s2; cin >> s1 >> s2;
    int x = s2[0] - 'A', y = 0;
    rep(j, 1, sz(s2)) y = y * 10 + s2[j] - '0';
    g[x][st[x] + y * 2] = s1[0];
  }
  rep(i, 0, 9) rep(j, 0, 22) {
    if(g[i][j] == 'S') {
      ans += check(g, i, j, i, j + 2);
      if(j >= river) {
	ans += check(g, i, j, i - 1, j + 1);
	ans += check(g, i, j, i + 1, j + 1);
      }
    } else if(g[i][j] == 'H') {
      rep(d, 0, 6) {
	int x = i + dx[d], y = j + dy[d];
	if(over(x, y) || g[x][y] != ' ') continue;
	rep(t, 0, 2) {
	  int nd = (d + t) % 6;
	  ans += check(g, i, j, x + dx2[nd], y + dy2[nd]);
	}
      }
    } else if(g[i][j] == 'C') {
      rep(d, 0, 6) {
	int x = i, y = j;
	while(1) {
	  x += dx[d], y += dy[d];
	  ans += check(g, i, j, x, y);
	  if(over(x, y) || g[x][y] != ' ') break;
	}
      }
    } else if(g[i][j] == 'A') {
      rep(d, 0, 6) {
	int x = i, y = j;
	while(1) {
	  x += dx[d], y += dy[d];
	  if(over(x, y) || g[x][y] != ' ') break;
	  ++ans;
	}
      }
      // leap 
      rep(d, 0, 6) {
	int x = i, y = j;
	while(1) {
	  x += dx[d], y += dy[d];
	  if(over(x, y) || isl(g, x, y)) break;
	}
	if(!isl(g, x, y)) continue;
	int nx = x, ny = y;
	while(1) {
	  nx += dx[d], ny += dy[d];
	  if(over(nx, ny) || isl(g, nx, ny)) break;
	}
	if(!iss(g, nx, ny)) continue;
	ans += check(g, i, j, nx, ny);
      }
    } else if(g[i][j] == 'E') {
      rep(d, 0, 6) {
	int x = i + dx2[d], y = j + dy2[d];
	if(over(x, y) || g[x][y] != ' ') continue;
	x += dx2[d], y += dy2[d];
	if(over(x, y)  || !cane[x][y]) continue;
	ans += check(g, i, j, x, y);
      }
    } else if(g[i][j] == 'M') {
      rep(d, 0, 6) {
	int x = i + dx2[d], y = j + dy2[d];
	if(over(x, y) || !canm[x][y]) continue;
	ans += check(g, i, j, x, y);
      }
    } else if(g[i][j] == 'G') {
      rep(d, 0, 6) {
	int x = i + dx[d], y = j + dy[d];
	if(over(x, y) || !cang[x][y]) continue;
	ans += check(g, i, j, x, y);
      }
    }
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cane[2][2] = cane[6][2] = 1;
  cane[0][8] = cane[4][8] = cane[8][8] = 1;
  canm[3][1] = canm[5][1] = canm[4][4] = 1;
  cang[4][0] = cang[4][2] = cang[4][4] = 1;
  cang[3][1] = cang[3][3] = 1;
  cang[5][1] = cang[5][3] = 1;
  int T; cin >> T;
  while(T--) cout << solve() << endl;
  return 0;
}
