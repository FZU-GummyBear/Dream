
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 11;
const db eps = 1e-8;

int n = 3;

int sign(db x) {
	return (x > eps) - (x < -eps);
}

struct P {
	ll x, y;
	P() {}
	P(ll x, ll y) : x(x), y(y) {}
	P operator + (const P &c) const {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	P operator / (const db &c) const {
		return P(x / c, y / c);
	}
	db len() {
		return sqrt(x * x + y * y);
	}
};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	vector<P> p(n);
	while(cin >> p[0].x >> p[0].y) {
		cin >> p[1].x >> p[1].y;
		//p[2] = p[1];
		cin >> p[2].x >> p[2].y;
		/*p[4] = p[5] = p[3];
		P ans(0, 0); rep(i, 0, n) ans = ans + p[i]; ans = ans / n;
		db len = 0; rep(i, 0, n) len += (ans - p[i]).len();
		db t = 100;
		while(t > eps) {
			bool f = 1;
			while(f) {
				f = 0;
				for(int i = -1; i <= 1; i += 2) {
					for(int j = -1; j <= 1; j += 2) {
						P np(ans.x + i * t, ans.y + j * t);
						db k = 0; rep(i, 0, n) k += (np - p[i]).len();
						if(sign(len - k) > 0) ans = np, len = k, f = 1;
					}
				}
			}
			t *= 0.5;
		}*/
		cout << setiosflags(ios::fixed);
		cout << setprecision(7);
		db res = 0;
		P ans = p[2];
		rep(i, 0, n) res += (ans - p[i]).len() * (i+1);
		cout << res << endl;
	}
	return 0;
}
