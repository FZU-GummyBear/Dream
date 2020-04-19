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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 20;
int nn, m, n, k, sum[N][N], f[1 << 20], T, id[N][N], S, w[N];
pii lim[N][N], a[20];
string s[N][N];

int get(pii a, pii b) {
	string s1 = s[a.fi][a.se], s2 = s[b.fi][b.se];
	int res = 0;
	rep(i, 0, sz(s1)) if (s1[i] == s2[i]) res++;
	return res;
}

pii cal(pii a, pii b) {
	pii t1 = a, t2 = b; int  res1 = 0, res2 = 0;
	while (a.fi > b.fi) {
		a.fi--;
		if (s[a.fi][a.se][0] != '-') res1 += pw(id[a.fi][a.se]);
	}
	while (a.fi < b.fi) {
		a.fi++;
		if (s[a.fi][a.se][0] != '-') res1 += pw(id[a.fi][a.se]);
	}
	while (a.se > b.se) {
		a.se--;
		if (s[a.fi][a.se][0] != '-') res1 += pw(id[a.fi][a.se]);
	}
	while (a.se < b.se) {
		a.se++;
		if (s[a.fi][a.se][0] != '-') res1 += pw(id[a.fi][a.se]);
	}
	a = t1, b = t2;
	while (a.se > b.se) {
		a.se--;
		if (s[a.fi][a.se][0] != '-') res2 += pw(id[a.fi][a.se]);
	}
	while (a.se < b.se) {
		a.se++;
		if (s[a.fi][a.se][0] != '-') res2 += pw(id[a.fi][a.se]);
	}
	while (a.fi > b.fi) {
		a.fi--;
		if (s[a.fi][a.se][0] != '-') res2 += pw(id[a.fi][a.se]);
	}
	while (a.fi < b.fi) {
		a.fi++;
		if (s[a.fi][a.se][0] != '-') res2 += pw(id[a.fi][a.se]);
	}
	return mp(res1, res2);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> k; nn = 0;
		rep(i, 1, n+1) rep(j, 1, m+1) {
			cin >> s[i][j];
			if (s[i][j][0] != '-') a[nn++] = mp(i, j), id[i][j] = nn - 1;
		}
		rep(i, 0, k+1) cin >> w[i];
		rep(i, 0, nn) rep(j, i+1, nn) {
			lim[i][j] = lim[j][i] = cal(a[i], a[j]);
			sum[i][j] = sum[j][i] = w[get(a[i], a[j])];
		}
		S = pw(nn) - 1;
		rep(i, 0, S+1) f[i] = - 1;
		f[S] = 0;
		per(i, 1, S+1) if (__builtin_popcount(i) % 2 == 0 && f[i] != -1){
			rep(j, 0, nn) if ((i >> j) & 1)
			 rep(k, j+1, nn) if ((i >> k) & 1) {
					 	int ne = i ^ pw(j) ^ pw(k);
					 	if ((ne & lim[j][k].fi) == 0 || (ne & lim[j][k].se) == 0) {
							f[ne] = max(f[ne], f[i] + sum[j][k]);
					 	}
				}
		}  
		cout << f[0] << endl;
	}
	return 0;
}
