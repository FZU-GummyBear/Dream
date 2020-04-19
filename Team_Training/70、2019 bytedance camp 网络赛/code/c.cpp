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

const int N = 55;
const db eps = 1e-8, pi = acos(-1);

struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
};

int n, r[N];
P o[N];
int sign(db x) { return (x > eps) - (x < -eps); }
int main() {
	scanf("%d", &n);
	rep(i, 1, n + 1) {
		int x, y; scanf("%d%d%d", &x, &y, r + i);
		o[i] = P(x, y);
	}
	srand(time(0));
	P ans(1, 1); 
	db len = 0; rep(i, 1, n + 1) len = max(len, (ans - o[i]).len() + r[i]);
	db t = 10000;
	auto Rand = [&] () { return rand() % 10000 / 5000 * pi; };
	while(t > eps) {
		db ang = Rand();
		P np(ans.x + t * sin(ang), ans.y + t * cos(ang));
		db k = 0; rep(i, 1, n + 1) k = max(k, (np - o[i]).len() + r[i]);
		if(sign(len - k) > 0) ans = np, len = k;
		t *= 0.999;
	}
	printf("%.7f\n", len);
	return 0;
}
