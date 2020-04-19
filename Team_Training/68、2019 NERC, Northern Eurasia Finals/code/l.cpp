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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1010;

int n, l, k;
char s[N * N], ans[N][N];

int main() {
	scanf("%d%d%d%s", &n, &l, &k, s);
	sort(s, s + n * l);
	int len = k, p = 0;
	rep(i, 0, n) rep(j, 0, l) ans[i][j] = ' ';
	rep(i, 0, l) {
		rep(j, k - len, k) ans[j][i] = s[p++];
		int tmp = 1;
		per(j, k - len, k - 1) {
			if(ans[j][i] == ans[j + 1][i]) ++tmp;
			else break;
		}
		len = tmp;
	}
	rep(i, 0, n) {
		rep(j, 0, l) {
			if(ans[i][j] == ' ') ans[i][j] = s[p++];
			cout << ans[i][j];
		}
		cout << endl;
	}
	return 0;
}
