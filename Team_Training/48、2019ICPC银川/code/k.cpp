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

const int N = 1010;

int n, m, len[N][N], ans;
pii a[N * N], b[N][N];
int l[N], r[N];

void gao(vi &vec) {
	int n = sz(vec) - 2;
	rep(i, 1, n + 1) {
		l[i] = i - 1;
		while(vec[l[i]] >= vec[i]) l[i] = l[l[i]];
	}
	per(i, 1, n + 1) {
		r[i] = i + 1;
		while(vec[r[i]] >= vec[i]) r[i] = r[r[i]];
	}
	rep(i, 1, n + 1) ans = max(ans, (r[i] - l[i] - 1) * vec[i]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) rep(j, 1, m + 1) {
		int x; cin >> x;
		a[x] = mp(i, j);
	}
	rep(i, 1, n + 1) rep(j, 1, m + 1) {
		int x; cin >> x;
		b[i][j] = a[x];
	}
	rep(i, 1, n + 1) {
		vi vec; vec.pb(0);
		rep(j, 1, m + 1) {
			len[i][j] = 1;
			if(i > 1 && b[i - 1][j].fi + 1 == b[i][j].fi && b[i - 1][j].se == b[i][j].se) len[i][j] = len[i - 1][j] + 1;
			vec.pb(len[i][j]);
			if(j == m || b[i][j].fi != b[i][j + 1].fi || b[i][j].se + 1 != b[i][j + 1].se) {
				vec.pb(0);
				gao(vec);
				vec.clear(); vec.pb(0);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
