
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

int add(int a, int b, int P) {
	a = a + b;
	return (a % P + P) % P;
} 

int mul(int a, int b, int P) {
	return 1ll * a * b % P;
}

ll kpow(ll a, ll b, ll P) {
	ll r = 1;
	for(; b; b >>= 1, a = a * a % P) if(b & 1) r = r * a % P;
	return r;
}
void ex_gcd(int a, int b, int &x, int &y) {
	b ? (ex_gcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}
inline int Inv(int a, int P) {
	int x, y; ex_gcd(a, P, x, y);
	return x < 0 ? x + P : x;
}

template<class T1, class T2>
struct FastD {
  	const static int wb = sizeof(T1) * 8;
  	int len; T1 m, x;
  	FastD() = default;
  	FastD(T1 n): m(n) {
    	if (n == 1) x = 1, len = 0;
    	else {
    		if (wb == 32) len = 31 - __builtin_clz(n - 1) + wb;
    		else len = 63 - __builtin_clzll(n - 1) + wb;
      		x = ((T2(1) << len) + n - 1) / n;
    	}
  	}
  	friend T1 operator / (const T1 &n, const FastD &d) { return T2(n) * d.x >> d.len; }
  	friend T1 operator % (const T1 &n, const FastD &d) { return n - n / d * d.m; }
};

using FastDiv32 = FastD<ull, __int128>;
FastDiv32 PP;

struct HT{
	static const int P = 7333333, N = 1e6;
	int head[P], nxt[N], tot, v[N], e[N];
	inline void init() {
		rep(i, 1, tot+1) head[e[i] % P] = 0;
		tot = 0;
	}
	inline void I(int y, int c) {
		int x = y % P;
		e[++tot] = y, v[tot] = c; nxt[tot] = head[x]; head[x] = tot;
	}
	inline int F(int y) {
		for (int i = head[y % P]; i; i = nxt[i]) if (e[i] == y) return v[i]; return -1;
	}
} M;

struct BSGS {
//	unordered_map<ll, int> M;
	ll bsgs(ll x, ll z, ll P) {
		if(x % P == 0) return -1;
		ll res = z % P, sa, t = 1, sq = sqrt(P); 
		M.init();
		rep(i, 0, sq + 1) {
			if (M.F(t) != -1) break;
			M.I(t, i);  
			t = t * x % P;
		}
		t = P / sq, sa = Inv(kpow(x, sq, P), P);
		rep(i, 0, t + 1) {
			int tt = M.F(res);
			if(tt != -1) return i * sq + tt; else 
				res = res * sa % P;
		}
		return -1;
	}
	ll ex_bsgs(ll x, ll z, ll P) {
		ll t = 1 % P, w = 1, ans, c = 0; z %= P;
		rep(i, 0, 51) {if (t == z) return i; t = t * x % P;}
		for (t = __gcd(x, P); t != 1; t = __gcd(x, P)) {
			if (z % t) return -1;
			z /= t; P /= t; w = w * x / t % P, c++;
			if (z == w) return c;
		}
		z = z * Inv(w, P) % P, 
		ans = bsgs(x, z, P);
		return ans + (ans != -1) * c;
	}
} B;

ll n;
int x, a, b, P, v, T, q;
ll ans;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;	
	rep(cas, 0, T) {
		cin >> n >> x >> a >> b >> P;
		cin >> q; 
		PP = FastDiv32(P);
		rep(i, 0, q) {
			cin >> v;
			if (a == 1) {
				if (b == 0) {
					if (x == v) ans = 0;else ans = -1;
				}else {
					ans = mul(add(v, -x, P), Inv(b, P), P);
					if (ans >= n) ans = -1;
				}
			}else {
				int t = mul(b, Inv(add(1, -a, P), P), P);
				v = add(v, -t, P);
				if (x == t) {
					if (v == 0) ans = 0;else ans = -1;
				}else {
					v = mul(v, Inv(add(x, -t, P), P), P);
					ans = B.ex_bsgs(a, v, P);
					if (ans >= n) ans = -1;
				}
			}
			cout << ans << endl;
		}
	}
	return 0;
}
