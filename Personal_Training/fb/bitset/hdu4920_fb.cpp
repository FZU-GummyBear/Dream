#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 805;
int n, x;

struct vec3{
	static const int N = ::N;
	bitset<N> a[3];
	vec3() { rep(i, 0, 3) a[i].reset(); }
	void reset() { rep(i, 0, 3) a[i].reset(); }
	void set(int p, int x) { x = (x % 3 + 3) % 3; rep(i, 0, 3) if (i == x) a[i].set(p); else a[i].reset(p); }
	int get(int p) { rep(i, 0, 3) if (a[i][p]) return i; }
	int getval() { return (a[1].count() + a[2].count() * 2) % 3; }
	vec3 operator * (const vec3 &c) {
		vec3 r;
		r.a[0] = a[0] | c.a[0];
		r.a[1] = (a[1] & c.a[1]) | (a[2] & c.a[2]);
		r.a[2] = (a[1] & c.a[2]) | (a[2] & c.a[1]);
		return r;
	}
	vec3 operator + (const vec3 &c) {
		vec3 r;
		r.a[0] = (a[0] & c.a[0]) | (a[1] & c.a[2]) | (a[2] & c.a[1]);
		r.a[1] = (a[0] & c.a[1]) | (a[1] & c.a[0]) | (a[2] & c.a[2]);
		r.a[2] = (a[0] & c.a[2]) | (a[2] & c.a[0]) | (a[1] & c.a[1]);
		return r;
	}
	vec3 operator - (const vec3 &c) {
		return (*this) + (c * -1);
	}
	vec3 operator * (int x) const{
		vec3 r = *this;
		x = (x % 3 + 3) % 3;
		if (x == 0) { r.a[0].set(); r.a[1].reset(); r.a[2].reset(); }
		if (x == 2) { swap(r.a[1], r.a[2]); }
		return r;
	}
	vec3 operator + (int x) const{
		vec3 r = *this;
		x = (x % 3 + 3) % 3;
		if (x == 1) { swap(r.a[0], r.a[2]); swap(r.a[1], r.a[2]); }
		if (x == 2) { swap(r.a[0], r.a[2]); swap(r.a[0], r.a[1]); }
		return r;
	}
};

vec3 a[N], b[N];

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n) {
		rep(i, 0, n) a[i].reset(), b[i].reset();
		rep(i, 0, n)
			rep(j, 0, n) {
				cin >> x; a[i].set(j, x);
			}
		rep(i, 0, n)
			rep(j, 0, n) {
				cin >> x; b[j].set(i, x);
			}
		rep(i, 0, n) rep(j, 0, n) {
			cout << (a[i] * b[j]).getval() << " \n"[j == n - 1];
		}
	} 
	return 0;
}


