#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 66;

int f[N][N][N][2];
string s;
vi tmp;
int ans, n, K, g1, g2, g3;

bool calc(int l, int r) { if (l > r) return 0; return (r - l + 1) % 2;}

bool check1(int x) {
	return x > 0 && x < n - 1 && s[x-1] == '.' && s[x+1] == '.';
}

bool check2(int x, int y) {
	bool t1 = x > 0 && x < n - 1 && s[x-1] == '.' && s[x+1] == '.';
	bool t2 = y > 0 && y < n - 1 && s[y-1] == '.' && s[y+1] == '.';
	return t1 && t2 && y - x >= 3;
}

void upd(int &x, int y) {
	x = max(x, y);
}

int solve(int n, int k1, int k2) {
	if (g1 * 2 >= g2) {
		k1 = min(k1, n);
		int res = k1 * g1 + min((n - k1) / 2, k2) * g2;
		if (k1 > 0) {
			k1--;
			res = max(res, k1 * g1 + min((n - k1) / 2, k2) * g2);
		} 
		return res;
	}else {
		int cnt = n - k2 * 2;
		return k2 * g2 + min(cnt, k1) * g1;
	}
}
int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> K >> g1 >> g2 >> g3;
	cin >> s;
	rep(i, 0, n) if (s[i] == '#') tmp.pb(i);
	// f[i][j][k][l] 第i个# 前面用了j个# 有k段奇数 第i个有没有用 
	memset(f, -10, sizeof(f));
	if(sz(tmp) == 0) {
		ans = solve(n, K, n / 2);
	} else {
		f[0][0][0][0] = 0;
		rep(i, 0, sz(tmp)) 
			rep(j, 0, i+1)
				rep(k, 0, i+2) 
					rep(l, 0, 2) if (f[i][j][k][l] >= 0) {
						int t = calc(i > 0 ? tmp[i-1] + 1 + l : 0, tmp[i] - 1);
						if (i == sz(tmp) - 1) t += calc(tmp[i] + 1, n - 1);
						upd(f[i+1][j][k + t][0], f[i][j][k][l]);
						if (!check1(tmp[i])) continue;
						if (l == 0 || check2(tmp[i-1], tmp[i])) {
							int t = calc(i > 0 ? tmp[i-1] + 1 + l : 0, tmp[i] - 2);
							if (i == sz(tmp) - 1) t += calc(tmp[i] + 2, n - 1);
							//if (i) dd(i), dd(j), dd(l), dd(tmp[i - 1]), de(tmp[i]);
							upd(f[i+1][j + 1][k + t][1], f[i][j][k][l] + g3);
						}
					}
		rep(j, 0, 51) rep(k, 0, 52) rep(l, 0, 2) if (f[sz(tmp)][j][k][l] >= 0) {
			//dd(j);dd(k);dd(l);de(f[sz(tmp)][j][k][l]);
			int cnt =  n - j * 2 - sz(tmp);
			ans = max(ans, solve(cnt, K, (cnt - k) / 2) + f[sz(tmp)][j][k][l]);
		}
	}
	cout << ans << endl;
	return 0;
}


