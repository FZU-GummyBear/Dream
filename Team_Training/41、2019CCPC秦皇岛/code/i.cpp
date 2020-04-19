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

const int N = 1e5 + 7;
string s, a[200];
int f[N][30], tmp[10], p[10][10], m, ww, now;
vi h[200];
int c[10], b[10], id, pos;

int cal(string t) {
	rep(i, 0, 3) t[i] -= '0';
	return t[0] * 9 + t[1] * 3 + t[2];
}

void get(int x) {
	per(i, 0, 3) b[i] = x % 3, x /= 3;
}

void upd(int &t, int x) {
	if (t == -1) t = x;
	else t = min(t, x);
}

int cal2() {
	return c[0] * 9 + c[1] * 3 + c[2];
}

void dfs(int d) {
	int x = 0;
	rep(j, d - 3, d) c[x++] = b[j];
	int w = cal2();
	for (auto v : h[now]) if (w == v) {
		upd(f[pos][w], ww + d - 3);
		break;
	}
	if (d == 6) return;
	rep(j, 0, 3) {
		b[d] = j;
		dfs(d + 1);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	a['Y'] = "000";
	a['V'] = "001";
	a['G'] = "002";
	a['C'] = "111";
	a['X'] = "011";
	a['Z'] = "112";
	a['T'] = "222";
	a['F'] = "022";
	a['D'] = "122";
	a['B'] = "012";
	cin >> s;
	memset(f, -1, sizeof(f));
	rep(i, 0, 3) tmp[i] = i;
	do {
		rep(i, 0, 3) p[m][i] = tmp[i];
		++m;
	} while (next_permutation(tmp, tmp+3));
	string t = a[s[0]];
	rep(i, 0, m) {
		rep(j, 0, 3) t[j] = a[s[0]][p[i][j]];
		id = cal(t);
		f[0][id] = 3;
	}
	rep(k, 0, 200) if (sz(a[k]) > 0) {
		t = a[k];
		rep(i, 0, m) {
			rep(j, 0, 3) t[j] = a[k][p[i][j]];
			id = cal(t);
			h[k].pb(id);
		}
	}
	rep(i, 1, sz(s)) rep(j, 0, 27) if (f[i-1][j] != -1){
		get(j); pos = i; ww = f[i-1][j];
		now = s[i];
		dfs(3);
	}
	int ans = pw(30);
	rep(j, 0, 27) if (f[sz(s) - 1][j] != -1) ans = min(ans, f[sz(s)-1][j]);
	cout << ans + sz(s) << endl;
	return 0;
}
