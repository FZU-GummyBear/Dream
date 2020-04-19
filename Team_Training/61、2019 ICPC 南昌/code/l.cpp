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

const int N = 111;

int n, a[N][N];
int x[N], y[N], p[N];

bool cmp(int i, int j) {
	if(x[i] != x[j]) return x[i] > x[j];
	return y[i] > y[j];
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) rep(j, 1, n + 1) cin >> a[i][j];
	rep(i, 1, n + 1) x[i] = y[i] = 0;
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
		if(a[i][j] > a[j][i]) {
			x[i] += 3;
		} else if(a[i][j] == a[j][i]) {
			x[i] += 1, x[j] += 1;
		} else {
			x[j] += 3;
		}
		y[i] += a[i][j] - a[j][i];
		y[j] += a[j][i] - a[i][j];
	}
	rep(i, 1, n + 1) p[i] = i;
	sort(p + 1, p + 1 + n, cmp);
	if(n > 1 && x[p[1]] == x[p[2]] && y[p[1]] == y[p[2]]) {
		cout << "play-offs" << endl;
		return ;
	}
	cout << p[1] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	solve();
	return 0;
}
