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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 105;
int n, m, k, dis[N][N][1 << 5], vis[N][N][1 << 5], x, y, z, nx, ny, nz;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

pii st;
int ans, now;
queue<pair<pii, int> > q;
int a[105][105];
string s[105];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);	
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		memset(a, 0, sizeof(a));
		rep(i, 1, n+1) {
			cin >> s[i];
			s[i] = " " + s[i];
			rep(j, 1, m+1) if (s[i][j] == '@') st = mp(i, j);
		}
		cin >> k;
		rep(i, 0, k) {
			cin >> x >> y;
			a[x][y] |= pw(i);
		}
		bool ok = 0;
		while(!q.empty()) q.pop();
		memset(vis, 0, sizeof(vis));
		now = a[st.fi][st.se];
		q.push(mp(st, now)); dis[st.fi][st.se][now] = 0; vis[st.fi][st.se][now] = 1; 
		if (now == pw(k) - 1) {
			cout << 0 << endl;
			continue;
		}
		while (!q.empty() && !ok) {
			auto t = q.front(); q.pop();
			x = t.fi.fi, y = t.fi.se; z = t.se;
			rep(i, 0, 4) {
				nx = x + dx[i];
				ny = y + dy[i];
				if (nx < 1 || nx > n || ny < 1 || ny > m || s[nx][ny] == '#') continue;
				nz = z | a[nx][ny];
				if (!vis[nx][ny][nz]) {
					vis[nx][ny][nz] = 1;
					dis[nx][ny][nz] = dis[x][y][z] + 1;
					q.push(mp(mp(nx, ny), nz));
					if (nz == pw(k) - 1) {
						ans = dis[nx][ny][nz];
						ok = 1;
						break;
					}
				}
			}
		}
		if (!ok) cout << -1 << endl;
		else cout << ans << endl;
	}
	return 0;
}
