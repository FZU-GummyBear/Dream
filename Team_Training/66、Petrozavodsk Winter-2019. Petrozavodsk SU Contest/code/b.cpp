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

const int N = 2e3 + 5;
int a[N][N], p[N], n;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	//de(4 * sqrt(2));
	rep(i, 1, n+1) cin >> p[i];
	if (n == 1) {
		cout << 1 << endl;
		cout << p[1] << endl;
		return 0;
	}
	if (n == 2) {
		cout << 3 << endl;
		cout << p[1] << " " << p[2] << " " << p[1] << endl;
		cout << p[2] << " " << p[1] << " " << p[2] << endl;
		cout << p[1] << " " << p[2] << " " << p[1] << endl;
		return 0;
	}
	cout << n * 2 - 1 << endl;
	int len = n * 2 - 1;
	int x = 1;
	rep(l, 2, len + len+1) {
		rep(i, 1, len+1) if (i < l && l - i <= len){
			a[i][l - i] = p[x];
		}
		x++;
		if (x > n) x = 1;
	}
	rep(i, 1, len+1) rep(j, 1, len+1) cout << a[i][j] << " \n"[j == len];
	return 0;
}
