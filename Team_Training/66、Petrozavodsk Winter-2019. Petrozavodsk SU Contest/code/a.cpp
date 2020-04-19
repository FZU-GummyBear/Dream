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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 111;

pii s[4][N * N];
int cnt[4];
int dis(int x, int y, int i, int j) {
	x -= i, y -= j;
	return x * x + y * y;
}
void gao(pii s[], int &cnt, int len, int x, int y) {
	rep(i, 0, 101) rep(j, 0, 101) if(dis(x, y, i, j) == len) s[++cnt] = mp(i, j);
}
bool check(pii a, pii b) {
	int x = abs(a.fi - b.fi);
	int y = abs(a.se - b.se);
	return (x == 0 && y == 1) || (x == 1 && y == 0);
}
void print() {
	rep(i, 1, cnt[0] + 1) rep(j, 1, cnt[1] + 1) if(check(s[0][i], s[1][j])) {
		rep(a, 1, cnt[2] + 1) if(check(s[1][j], s[2][a])) {
			rep(b, 1, cnt[3] + 1) if(check(s[2][a], s[3][b])) {
				printf("A %d %d\n", s[0][i].fi, s[0][i].se);
				fflush(stdout);
				return ;
			}
		}
	}
}
int main() {
	int x;

	printf("Q -997 973\n");
	fflush(stdout);
	scanf("%d", &x);
	gao(s[0], cnt[0], x, -997, 973);

	printf("Q -973 -977\n");
	fflush(stdout);
	scanf("%d", &x);
	gao(s[1], cnt[1], x, -973, -977);

	printf("Q 937 977\n");
	fflush(stdout);
	scanf("%d", &x);
	gao(s[2], cnt[2], x, 937, 977);

	printf("Q 977 -983\n");
	fflush(stdout);
	scanf("%d", &x);
	gao(s[3], cnt[3], x, 977, -983);

	print();
	return 0;
}
