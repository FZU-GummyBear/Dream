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

const int N = 1010;

int a[N][N];
int cnt;
int n, sum, m;

bool check(int x, int y, int v) {
	a[x][y] = v;
	if(y == n - 1) {
		int tot = 0;
		rep(i, 0, n) tot += a[x][i];
		tot %= m;
		if(sum != -1) {
			if(sum != tot) return 0;
		} else {
			sum = tot;
		}
	}
	if(x == n - 1) {
		int tot = 0;
		rep(i, 0, n) tot += a[i][y];
		tot %= m;
		if(sum != -1) {
			if(sum != tot) return 0;
		} else {
			sum = tot;
		}
	}
	if(x == n - 1 && y == n - 1) {
		int tot = 0;
		rep(i, 0, n) tot += a[i][i];
		tot %= m;
		if(sum != -1) {
			if(sum != tot) return 0;
		} else {
			sum = tot;
		}
	}
	if(x == n - 1 && y == 0) {
		int tot = 0;
		rep(i, 0, n) tot += a[n - 1 - i][i];
		tot %= m;
		if(sum != -1) {
			if(sum != tot) return 0;
		} else {
			sum = tot;
		}
	}
	return 1;
}

void dfs(int x, int y) {
	if(x == n && y == 0) {
		/*
		int sum = 0;
		rep(i, 0, n) sum += a[i][0];
		sum %= m;
		rep(i, 0, n) {
			int tot = 0;
			rep(j, 0, n) tot += a[i][j];
			if(tot % m != sum) return ;
			tot = 0;
			rep(j, 0, n) tot += a[j][i];
			if(tot % m != sum) return ;
		}
		int tot = 0;
		rep(i, 0, n) tot += a[i][i];
		if(tot % m != sum) return ;
		tot = 0;
		rep(i, 0, n) tot += a[n - 1 - i][i];
		if(tot % m != sum) return ;
		*/
//		rep(i, 0, n) rep(j, 0, n) cout << a[i][j] << " \n"[j == n - 1];
//		cout << endl;
		++cnt;
		return ;
	} 
	int nx = x, ny = y + 1;
	if(ny == n) ++nx, ny = 0;
	rep(v, 0, m) {
		int psum = sum;
		if(check(x, y, v)) {
			dfs(nx, ny);
			sum = psum;
		}
	}
}

int solve(int n, int m) {
	//dd(n), de(m);
	::n = n; ::m = m;
	cnt = 0; sum = -1;
	dfs(0, 0);
	return cnt;
	//de(cnt);
	//cout << "---------------" << endl;
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	int mn = 10, mm = 3;
	rep(n, 3, mn + 1) rep(m, 2, mm + 1) {
		dd(n), dd(m);
	//	if(n % 2 == 0 && m % 2 == 0) dd(2 * pow(m, 2 * n));
	//	if(n % 2 == 0 && m % 2) dd(pow(m, 2 * n));
		de(solve(n, m) - pow(m, (n - 1) * (n - 1) - 1));
	}
	return 0;
}
