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

const int N = 505;
int n, p, S, T, k, sx, sy;
vector<pii> ans[N], tmp;
pii now;
//int w[N][N];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, 1};

pii sub(pii a, pii b) { pii t = mp(a.fi - b.fi, a.se - b.se); 
if (abs(t.fi) + abs(t.se) != 1) dd(a.fi), dd(a.se), dd(b.fi), de(b.se);
return t;}

void solve(int n) {
	if (n == 1) {
		cout << "1 1" << endl << "1 1" << endl;
		return;
	}
	if (n == 2) {
		cout << "1 3" << endl;
		cout << "1 1" << endl;
		cout << "1 2 1 3" << endl;
		return;
	}
	tmp.clear();
	if (n % 4 == 0 || n % 4 == 3) {
		S = n * (n + 1) / 2;
		now = mp(2, 1); k = 0;
		rep(i, 1, S+1) {
			tmp.pb(now);
			now.fi += dx[k];
			now.se += dy[k];
			k = (k + 1) % 4;
		}
		p = 0;
		cout << 2 << " " <<  S / 2 << endl;
		sx = 2; sy = S / 2;
		rep(i, 1, n+1) {
			rep(j, 1, i+1) {
				cout << tmp[p].fi << " " << tmp[p].se << " \n"[j == i], p++; 
			//	w[tmp[p-1].fi][tmp[p-1].se] = i;
			}
		}
		return;
	}
	rep(i, 1, n+1) ans[i].clear();
	bool ok = 0;
	if (n % 4 == 2) {
		ok = 1; n--;
	}	
	cout << n + ok * 2 << " " << (n + 1) / 2 << endl;
	sx = n + ok * 2;
	sy = (n + 1) / 2;
	int m = n / 2, len = (n + 1) / 2;
	rep(i, 2, m+1) {
		S = len * 2; tmp.clear();
		now = mp((i - 1) * 2, 1); k = 0;
		rep(j, 1, S+1) {
			tmp.pb(now);
			now.fi += dx[k];
			now.se += dy[k];
			k = (k + 1) % 4;
		}
		rep(j, 1, i+1) ans[i].pb(tmp[j - 1]);
		rep(j, 1, S - i + 1) ans[S - i].pb(tmp[j + i - 1]);
	}
	ans[1].pb(mp((m - 1) * 2 + 1, len));
	rep(i, 1, len) ans[len].pb(mp((m - 1) * 2 + 1, len - i));
	ans[len].pb(mp((m - 1) * 2 + 2, 1));
	ans[n].pb(mp(n, 1));
	now = mp(n, 2);  k = 0;
	rep(i, 1, n) {
		ans[n].pb(now);
		now.fi += dx[k];
		now.se += dy[k];
		k = (k + 1) % 4;
	}
	//de(len);
	if (ok) {
		rep(i, 1, len+1) ans[n+1].pb(mp(n+1, i));
		per(i, 1, len+1) ans[n+1].pb(mp(n+2, i));
		n++;
	}
	rep(i, 1, n+1) {
		rep(j, 0, i) {
			cout << ans[i][j].fi << " " << ans[i][j].se << " \n"[j == i - 1];
			//w[ans[i][j].fi][ans[i][j].se] = i;
		}
		/*if (i > 2) {
				int cnt =0;
			rep(j, 2, i) {
				if (sub(ans[i][j], ans[i][j-1]) != sub(ans[i][j-1], ans[i][j-2])) cnt++;
				//dd(i), de(cnt);
			}
			assert((i & 1) == (cnt & 1));
		}*/
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n) {
		solve(n);
		/*de("-------");
		rep(i, 1, sx+1) rep(j, 1, sy+1) cout << w[i][j] << " \n"[j == sy];
		de("-------");*/
	}
	return 0;
}
