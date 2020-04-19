#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

struct vec3{
	static const int N = 65;
	bitset<N> a[3];
	vec3() { a[0].set(); }
	inline void ini() { a[0].set(); a[1].reset(); a[2].reset(); }
	inline void set(int p, int x) { x = (x % 3 + 3) % 3; rep(i, 0, 3) if (i == x) a[i].set(p); else a[i].reset(p); }
 	inline int operator [] (int x) { rep(i, 0, 3) if (a[i][x]) return i; }
	int getval() { return (a[1].count() + a[2].count() * 2) % 3; }
	inline vec3 operator * (const vec3 &c) const {
		vec3 r;
		r.a[0] = a[0] | c.a[0];
		r.a[1] = (a[1] & c.a[1]) | (a[2] & c.a[2]);
		r.a[2].set(); r.a[2] ^= r.a[0] ^ r.a[1];
		return r;
	}
	inline vec3 operator + (const vec3 &c) const {
		vec3 r;
		r.a[1] = (a[0] & c.a[1]) | (a[1] & c.a[0]) | (a[2] & c.a[2]);
		r.a[2] = (a[0] & c.a[2]) | (a[2] & c.a[0]) | (a[1] & c.a[1]);
		r.a[0] ^= r.a[1] ^ r.a[2];
		return r;
	}
	inline vec3 operator - (const vec3 &c) const {
		return (*this) + (c * -1);
	}
	inline vec3 operator * (int x) const {
		vec3 r = *this;
		x = (x % 3 + 3) % 3;
		if (x == 0) { r.ini(); }
		if (x == 2) { swap(r.a[1], r.a[2]); }
		return r;
	}
	inline vec3 operator + (int x) const{
		vec3 r = *this;
		x = (x % 3 + 3) % 3;
		if (x == 1) { swap(r.a[0], r.a[2]); swap(r.a[1], r.a[2]); }
		if (x == 2) { swap(r.a[0], r.a[2]); swap(r.a[0], r.a[1]); }
		return r;
	}
};


ull a, b, last;
int n;


const int M = 65;
struct LB{
	vec3 a[M];
	int b[M];
	void clear() { memset(b, 0, sizeof(b)); }
	void ins(vec3 x, int v){
		for(int i = M-1; ~i; --i) if (x[i]) {
			if (a[i][i]) {
				if (v > b[i]) last += v - b[i], swap(v, b[i]), swap(x, a[i]);
				x = x - a[i] * (a[i][i] * x[i]);
			} else { a[i] = x; b[i] = v; last += v; break; }
		}
	}
} lb;

struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    bool ed;
    FastIO() : wpos(0), ed(0) { }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline ll xint() {
        int c = xchar(); ll x = 0, s = 1;
        while (c <= 32) {
            if(!~c) return ed = 1;
            c = xchar();
        }
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    ~FastIO() { if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0; }
} IO;

int main() {
	FI(a);
	n = IO.xint();
	rep(i, 1, n+1) {
		a = IO.xint(); b = IO.xint();
		a ^= last; b ^= last;
		vec3 t;
		rep(i, 0, 65) {
			if (a & 1) t.set(i, 1);
			a >>= 1;
		}
		lb.ins(t, b);
		IO.wint(last);
		IO.wchar('\n');
	}
	return 0;
}


