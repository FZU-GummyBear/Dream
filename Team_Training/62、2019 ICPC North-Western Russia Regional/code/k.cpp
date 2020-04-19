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

const int N = 1010;

int n, m, ax, ay, cnt[N][N];
int ma, lx, rx, ly, ry;
int l[N], r[N];
char s[N][N];

void upd(int rx, int a[]) {
	a[0] = a[m + 1] = -1;
	rep(i, 1, m + 1) {
		l[i] = i - 1;
		while(a[l[i]] >= a[i]) l[i] = l[l[i]];
	}
	per(i, 1, m + 1) {
		r[i] = i + 1;
		while(a[r[i]] >= a[i]) r[i] = r[r[i]];
	}
	rep(i, 1, m + 1) {
		int ly = l[i] + 1, ry = r[i] - 1;
		int lx = rx - a[i] + 1, res = (rx - lx + 1) * (ry - ly + 1);
		if(res > ma && lx <= ax && ax <= rx && ly <= ay && ay <= ry) {
			ma = res; 
			::lx = lx;
			::rx = rx;
			::ly = ly;
			::ry = ry;
		}
	}
}
bool check(int l, int r, int j) {
	rep(i, l, r + 1) if(s[i][j] != '.') return 0;
	return 1;
}
void gao(int x, int y, char ch) {
	int lx = x, rx = x;
	while(lx - 1 >= 1 && s[lx - 1][y] == '.') --lx;
	while(rx + 1 <= n && s[rx + 1][y] == '.') ++rx;
	int ly = y, ry = y;
	while(ly - 1 >= 1 && check(lx, rx, ly - 1)) --ly;
	while(ry + 1 <= m && check(lx, rx, ry + 1)) ++ry;
	rep(i, lx, rx + 1) rep(j, ly, ry + 1) if(s[i][j] == '.') s[i][j] = ch;
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n + 1) {
		scanf("%s", s[i] + 1);
		rep(j, 1, m + 1) if(s[i][j] == 'A') ax = i, ay = j, s[i][j] = '.';
	}
	rep(i, 1, n + 1) {
		rep(j, 1, m + 1) cnt[i][j] = (s[i][j] == '.' ? cnt[i - 1][j] + 1 : 0);
		upd(i, cnt[i]);
	}
	rep(i, lx, rx + 1) rep(j, ly, ry + 1) s[i][j] = 'a';
	s[ax][ay] = 'A';
	rep(j, 1, m + 1) rep(i, 1, n+1) if('A' < s[i][j] && s[i][j] <= 'Z') gao(i, j, s[i][j] - 'A' + 'a');
	rep(i, 1, n + 1) {
		s[i][m + 1] = '\0';
		rep(j, 1, m+1) assert(s[i][j] != '.');
		printf("%s\n", s[i] + 1);
	}
	return 0;
}
