#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const db eps = 1e-12;

db w[10], w2[10];
int T;
db v1, v2, t;
int sign(db x) { return  (x > eps) - (x < -eps); }
bool check(db x) {return sign(x) >= 0 && sign(x - 300) <= 0; }

bool solve(db v1, db v2, db t) {
	if (sign(v1 - v2) >= 0) return 1;
	if (sign(v1) == 0) return 0;
	int cnt = 0;
	if (sign(300 * sqrt(2) / v1 - 600 / v2) < 0) {
		db cc = 1.0 * v1 / v2; cc = cc * cc;
		db a = 1 - cc, b = -600 * cc, c = 300 * 300 * (1 - cc);
		db d = sqrt(b * b - 4 * a * c);
		db xx1 = (-b + d) / 2 / a, xx2 = (-b - d) / 2 / a;
		db x = 1e18;
		if (check(xx1)) x = min(x, xx1);
		if (check(xx2)) x = min(x, xx2);
		if (sign(a * x * x + b * x + c) != 0) for (;;);
		w[0] = x; w[1] = w[2] = w[3] = 300;
		w2[0] = 0; w2[1] = 300 - x; w2[2] = w2[3] = 300;
		rep(i, 1, 4) {
			w[i] += w[i-1];
			w2[i] += w2[i-1];
			if (sign(w[i] / v1 - w2[i] / v2 - t) <= 0) cnt++;
		}
		cnt++;
		return cnt >= 3;
	}else if (sign(v2 - 3 * v1) < 0) {
		db cc = 1.0 * v1 / v2; cc = cc * cc;
		db a = 1 - cc, b = -600 * (1 + 2 * cc), c = 180000 * (1 - 2 * cc);
		db d = sqrt(b * b - 4 * a * c);
		db xx1 = (-b + d) / 2 / a, xx2 = (-b - d) / 2 / a;
		db x = 1e18;
		if (check(xx1)) x = min(x, xx1);
		if (check(xx2)) x = min(x, xx2);
		if (sign(a * x * x + b * x + c) != 0) for (;;);
		w[0] = sqrt(x * x + 300 * 300); w[1] = w[2] = w[3] = 300;
		w2[0] = w2[1] = 0; w2[2] = 300 - x; w2[3] = 300;
		rep(i, 1, 4) {
			w[i] += w[i-1];
			w2[i] += w2[i-1];
			if (i > 1 && sign(w[i] / v1 - w2[i] / v2 - t) <= 0) cnt++;
		}
		cnt++;
		return cnt >= 3;
	}else return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> t >> v1 >> v2;
		cout << "Case #" << cas + 1 << ": ";
		bool ok = solve(v1, v2, t);
		if (ok) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
