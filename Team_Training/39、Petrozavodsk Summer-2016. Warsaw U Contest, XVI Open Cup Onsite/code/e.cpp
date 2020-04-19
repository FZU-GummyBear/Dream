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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 1e9 + 7;
const int N = 1e5 + 6;
int f[N][11], ans, n, m, k, b[N], r1, r2, l, r, L, R;
string s1, s2;
inline int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a;
}

inline int mul(int a, int b) {
	return 1ll * a * b % P;
}

struct vec{
	int a[10];
	vec() {memset(a, 0, sizeof(a));}
};

struct mat{
	int a[10][10];
	mat() { memset(a, 0, sizeof(a));}
	inline mat operator * (const mat &c) const {
		mat r;
		rep(i, 0, m) 
			rep(k, 0, m) if (a[i][k])
				rep(j, 0, m) if (c.a[k][j]) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
		return r;
	}
	inline vec operator * (const vec &c) const {
		vec r;
		rep(i, 0, m) rep(j, 0, m) r.a[i] = add(r.a[i], mul(a[i][j], c.a[j]));
		return r;
	}
	void print() {
		rep(i, 0, m) rep(j, 0, m) cout << a[i][j] << " \n"[j == m -1];
	}
} a[N], q1[N], q2[N];


void insert(const mat &c, int p) {
	//de(1);
	if (r1 == -1) q1[++r1] = c, b[r1] = p;
	else q1[r1+1] = c * q1[r1], r1++, b[r1] = p;
}

void del() {
	//de(2);
	if (r2 == -1) {
		per(i, 0, r1 + 1) {
			if (r2 == -1) q2[++r2] = a[b[i]];
			else q2[r2+1] = q2[r2] * a[b[i]], r2++; 
		}
		r1 = -1;
	}
	r2--;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	cin >> s1 >> s2;
	if (sz(s2) == 1) {
		cout << 0 << endl;
		return 0;
	}
	rep(i, 0, n) {
		rep(j, 0, m) a[i].a[j][j] = 1;
		rep(j, 1, m) a[i].a[j][j-1] = s1[i] == s2[j];
	} 
	l = 0; r = -1; r1 = r2 = -1;
	rep(i, 0, n) if (s1[i] == s2[0]) {
		vec t; t.a[0] = 1;
		L = i + 1; R = min(i + k - 1, n - 1);
		if (L <= R) {
			//dd(L); de(R);
			while (r < R) r++, insert(a[r], r);
			while (l < L) del(), l++;
			if (r2 >= 0 && r1 >= 0) t = q1[r1] * q2[r2] * t;
			else if (r2 >= 0) t = q2[r2] * t;
			else if (r1 >= 0) t = q1[r1] * t;
			//dd(r1), dd(r2);
			//dd(l), de(r);
			ans = add(ans, t.a[m-1]);
			//de(ans);
		}
	}
	f[0][0] = 1;
	rep(i, 1, n+1) rep(j, 0, m+1) {
		f[i][j] = add(f[i][j], f[i-1][j]);
		if (j > 0 && s1[i-1] == s2[j-1]) f[i][j] = add(f[i][j], f[i-1][j-1]);
	}
	cout << (f[n][m] - ans + P) % P  << endl;
	return 0;
}
