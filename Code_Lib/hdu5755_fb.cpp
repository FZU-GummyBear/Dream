#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
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

const int N = 905;

struct vec3{
	static const int N = ::N;
	bitset<N> a[3];
	vec3() { a[0].set(); a[1].reset(); a[2].reset(); }
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


//对 2 取模的 01 方程组
//namespace Gauss{
	//static const int N = 2e3 + 10;
	//有 equ 个方程， var 个变元。增广矩阵行数为 equ ,列数为 [0..var]
	vec3 a[N]; //增广矩阵 modif
	int x[N]; //解集
	int p, col, k; // k 为增广矩阵的秩
	int fre[N], fnum; //一组合法自由变元（多解枚举自由变元可以使用）
	//返回值为 -1 表示无解，为 0 是唯一解，否则返回自由变元个数
	
	void genx(int msk, int var) {
		rep(i, 0, fnum) x[fre[i]] = (msk >> i) & 1;
		per(i, 0, k) {
			rep(j, 0, var) if(a[i][j]) { p = j; break; }	
			x[p] = a[i][var];
			rep(j, p+1, var) x[p] -= (a[i][j] * x[j]);
			x[p] = (x[p] * a[i][p] % 3 + 3) % 3;
		}
	}
	
	int Gauss(int equ, int var){
		fnum = 0;
		for(k = 0, col = 0; k < equ && col < var; k++, col++){
			p = k; rep(i, k, equ) if (a[i][col]) {p = i; break;}
			if (p != k) swap(a[k], a[p]);
			if (!a[k][col]){
				k--; fre[fnum++] = col;//这个是自由变元
				continue;
			}
			rep(i, 0, equ) if (i != k && a[i][col]) {
				a[i] = a[i] - a[k] * (a[i][col] * a[k][col]);
			}
		}
		rep(i, col, var) fre[fnum++] = i;
		rep(i, k, equ) if (a[i][var]) return -1;
		if(k < var) {
			genx(0, var);
			return var - k;//自由变元个数
		} 
		//唯一解，回代
		per(i, 0, var){
			x[i] = a[i][var];
			rep(j, i+1, var) x[i] -= (a[i][j] * x[j]);
			x[i] = (x[i] * a[i][i] % 3 + 3) % 3; 
		}
		return 0;
	}
//}

int T, n, m, b[N][N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int id(int x, int y) {return x * m + y;}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 0, n) rep(j, 0, m) {
			cin >> b[i][j];
		}
		rep(i, 0, n * m) a[i].ini();
		rep(i, 0, n) rep(j, 0, m) {
			rep(k, 0, 4) {
				int x = i + dx[k], y = j + dy[k];
				if (check(x, y)) a[id(i, j)].set(id(x, y), 1);
				a[id(i, j)].set(id(i, j), 2);
				a[id(i, j)].set(n * m, -b[i][j]);
			}
		}
		int cnt = 0;
		Gauss(n * m, n * m);
		rep(i, 0, n * m) cnt += x[i];
		cout << cnt << endl;
		rep(i, 0, n * m) rep(j, 0, x[i]) {
			cout << i / m + 1 << " " << i % m + 1 << endl;
 		}
	} 
	return 0;
}


