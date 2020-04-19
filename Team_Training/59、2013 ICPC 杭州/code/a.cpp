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

const int N = 205;
int n, m, k, x, y, sum, ans, cnt[N][N], a[N][N];
pii pos[N];
string s[N];

int dx[] = {-1, 0, 1, 0, -1};
int dy[] = {0, 1, 0, -1, 0};

bool check(pii u, int o) {
	if (s[u.fi][u.se] == '#') return 0;
	if (s[u.fi + dx[o]][u.se + dy[o]] == '#') return 0;
	if (s[u.fi + dx[o+1]][u.se + dy[o+1]] == '#') return 0;
	return 1;
}

void add(pii u, int o) {
	cnt[u.fi][u.se]++;
	cnt[u.fi + dx[o]][u.se + dy[o]]++;
	cnt[u.fi + dx[o+1]][u.se + dy[o+1]]++; 
	sum++;
}

void del(pii u, int o) {
	cnt[u.fi][u.se]--;
	cnt[u.fi + dx[o]][u.se + dy[o]]--;
	cnt[u.fi + dx[o+1]][u.se + dy[o+1]]--; 
	sum--;
}

void dfs(int d, int o) {
	if (d == k) {
		bool ok = 1;
		rep(i, 0, k) ok &= cnt[pos[i].fi][pos[i].se] > 0;
		if (ok) ans = min(ans, sum);
		return;
	}
	rep(i, 0, 4) {
		if (i != 0 && o != 0) break;
		if (i == 0) dfs(d + 1, o);
		if (check(pos[d], i)) {
			add(pos[d], i);
			dfs(d + 1, o | (i != 0));
			del(pos[d], i);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		k = 0;
		rep(i, 1, n+1) {
			cin >> s[i];
			s[i] = " " + s[i] + " ";
			rep(j, 1, m+1) if (s[i][j] == '.') pos[k] = mp(i, j), a[i][j] = k++;
		}
		s[0] = s[n+1] = "";
		rep(j, 1, m + 5) s[0] += " ", s[n + 1] += " "; 
		if (k == 0) {
			cout << 0 << endl;
			continue;
		}
		ans = pw(30);
		dfs(0, 0);
		if (ans > 100000) cout << -1 << endl; else cout << ans << endl;
	}
	return 0;
}
