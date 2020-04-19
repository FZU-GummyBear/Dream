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

const int N = 24;

int n, ans;
int a[N];
int p1[] = {20, 1, 22, 3, 10, 4, 0, 7, 8, 9, 11, 5, 2, 13, 14, 15, 6, 17, 12, 19, 16, 21, 18, 23};
int p2[] = {1, 3, 0, 2, 23, 22, 4, 5, 6, 7, 21, 20, 10, 11, 12, 13, 18, 16, 19, 17, 15, 14, 9, 8};
int p3[] = {10, 4, 11, 5, 18, 16, 12, 6, 2, 0, 19, 17, 13, 7, 3, 1, 14, 8, 15, 9, 21, 23, 20, 22};
int col[] = {0, 1, 2, 3, 4, 5, 10, 11, 6, 7, 12, 13, 8, 9, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

int check(int a[]) {
	int ans = 0;
	rep(i, 0, 6) {
		bool ok = 1;
		rep(j, 1, 4) if(a[col[i * 4 + j]] != a[col[i * 4 + j - 1]]) ok = 0;
		ans += ok;
	}
	return ans;
}

void gao(int a[], int p[]) {
	int tmp[N];
	rep(i, 0, N) tmp[i] = a[p[i]];
	rep(i, 0, N) a[i] = tmp[i];
}

void dfs(int a[], int n) {
	ans = max(ans, check(a));
	if(n) {
		gao(a, p1);
		dfs(a, n - 1);
		rep(o, 0, 2) gao(a, p1);
		dfs(a, n - 1);
		gao(a, p1);

		gao(a, p2);
		gao(a, p1);
		dfs(a, n - 1);
		rep(o, 0, 2) gao(a, p1);
		dfs(a, n - 1);
		gao(a, p1);
		rep(o, 0, 3) gao(a, p2);

		gao(a, p3);
		gao(a, p1);
		dfs(a, n - 1);
		rep(o, 0, 2) gao(a, p1);
		dfs(a, n - 1);
		gao(a, p1);
		rep(o, 0, 3) gao(a, p3);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		ans = 0;
		rep(i, 0, N) cin >> a[i];//, cout << a[i] << " \n"[i == N - 1];
		dfs(a, n);
//		rep(i, 0, N) cout << a[i] << " \n"[i == N - 1];
		cout << ans << endl;
	}
	return 0;
}
