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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 7;
int n, T, a[N], s;
db f[N], p, t;

const db eps = 1e-8;

int sign(db x) {return (x > eps) - (x < -eps); }

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//cin >> T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		//cin >> n; 
		scanf("%d%lf", &n, &p);
		s = 0; t = 0;
		rep(i, 1, n+1) scanf("%d", &a[i]), s += a[i];
		rep(i, 1, s+1) f[i] = 0;
		f[0] = 1;
		rep(i, 1, n+1) {
			per(j, 0, s+1) f[j] = f[j] * 0.5 + (j >= a[i] ? f[j - a[i]] : 0) * 0.5;
		}
		rep(i, 0, s+1) {
			t += f[i];
			if (sign(t - p) >= 0) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
