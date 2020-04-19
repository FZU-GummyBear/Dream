#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
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
const int N = 211;

struct vec{
	vi a;
	void clear(int n){
		a.clear(); a.resize(n);
	}
	int& operator[] (int idx) {
		return a[idx];
	}
	vec operator + (vec &c) {
		vec r = *this;
		per(i, 0, sz(a)) r[i] = add(r[i], c[i]); 
		return r;
	}
	vec operator - (vec c) {
		vec r = *this;
		per(i, 0, sz(a)) r[i] = add(r[i], -c[i]); 
		return r;
	}
	int operator * (vec &c) {
		int res = 0;
		per(i, 0, sz(a)) res = add(res, mul(a[i], c[i])); 
		return res;
	}
	vec operator * (int x) {
		vec r = *this;
		per(i, 0, sz(a)) r[i] = mul(r[i], x); 
		return r;
	}
	vec operator / (int x) {
		vec r = *this; x = kpow(x, P - 2);
		per(i, 0, sz(a)) r[i] = mul(r[i], x); 
		return r;
	}
	vec operator - (int x) {
		vec r = *this;
		r.a.back() = add(r.a.back(), -x); 
		return r;
	}
};
 
int n, m;
bool hole[N][N];
int id[N][N], stx, sty;
vec expr[N][N];
vector<vec> eqs;
int A[N][N], B[N][N];
 
vec gauss(vector<vec> &eqs){
	vector<vec> tmp = eqs;
	int n = sz(eqs[0].a), m = sz(eqs);
	assert(m && m >= n-1);
	for (int i = 0; i+1 < n; ++i){
		int id = -1;
		rep(j, i, m) if (eqs[j][i]) {id = j; break;}
		if (id != i) swap(eqs[i], eqs[id]);
		eqs[i] = eqs[i] * kpow(eqs[i][i], P - 2);
		rep(j, i+1, m) eqs[j] = eqs[j] - eqs[i] * eqs[j][i];
	}
	vec ans; ans.clear(n); ans.a.back() = 1;
	for (int i = n-2;i >= 0; --i)
		ans[i] = mul(eqs[i] * ans, kpow(P - eqs[i][i], P - 2));
	return ans;
}
 
const int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
 
inline int D(int x,int y){
	return 4-(x==1)-(x==n)-(y==1)-(y==n);
}
int x[N], y[N];
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cin >> T;
	rep(cas, 0, T){
		cin >> n >> m;
		rep(i, 0, n+2) rep(j, 0, n+2) hole[i][j] = !(i>=1 && i<=n && j>=1 && j<=n);
		rep(i, 1, m+1) cin >> x[i] >> y[i], hole[x[i]][y[i]] = 1;
		cin >> stx >> sty;
		int N = 0;
		rep(i, 1, n+1) rep(j, 1, n+1) id[i][j] = -1;
		rep(j, 1, n+1) if (!hole[1][j]) id[1][j] = N++;
		rep(i, 2, n+1) rep(j, 1, n+1) if (hole[i-1][j] && !hole[i][j]) id[i][j] = N++;			
		eqs.clear();
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j] && id[i][j] != -1){ // 初始化主元 主元为所有非洞且上方为洞的变量 
			expr[i][j].clear(N+1);
			expr[i][j][id[i][j]] = 1;
		}
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j]){
			if (hole[i+1][j]){ // 下方是洞 那么会产生一个方程 
				vec eq = expr[i][j];
				if (i == stx && j == sty) eq[N] -= 1;
				rep(k, 0, 3) {
					int nx = i + dx[k], ny = j + dy[k];
					if (!hole[nx][ny]) eq = eq - expr[nx][ny] / D(nx, ny);
				} 
				eqs.eb(eq);
			}else{ // 下方不是洞 那么下方变量可以用主元表示 
				vec &eq = expr[i+1][j]; eq = expr[i][j];
				if (i == stx && j == sty) eq[N] -= 1;
				rep(k, 0, 3) {
					int nx = i + dx[k], ny = j + dy[k];
					if (!hole[nx][ny]) eq = eq - expr[nx][ny] / D(nx, ny);
				} 
				eq = eq * D(i+1, j);
			}
		}
		assert((int)eqs.size()==N); // A数组表示经过每个点的期望次数   Au = sigma(Av / Dv) + (u == st) 
		vec ans = gauss(eqs);
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j]) A[i][j] = expr[i][j] * ans;
		rep(i, 1, n+1) rep(j, 1, n+1) if (hole[i][j]){
			A[i][j] = 0;
			rep(k, 0, 4) {
				int nx = i + dx[k], ny = j + dy[k];
				if (!hole[nx][ny]) A[i][j] = add(A[i][j], mul(A[nx][ny], kpow(D(nx,ny), P - 2)));
			}
		}			
		
		
		eqs.clear();
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j] && id[i][j] != -1){
			expr[i][j].clear(N+1);
			expr[i][j][id[i][j]] = 1;
		}
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j]){
			if (hole[i+1][j]){
				vec eq = expr[i][j];
				rep(k, 0, 3) {
					int nx = i + dx[k], ny = j + dy[k];
					if (!hole[nx][ny]) eq = eq - expr[nx][ny] / D(nx, ny) - mul(A[nx][ny], kpow(D(nx, ny), P - 2));
				} 
				eqs.eb(eq);
			}else{
				vec &eq=expr[i+1][j]; eq=expr[i][j];
				rep(k, 0, 3) {
					int nx = i + dx[k], ny = j + dy[k];
					if (!hole[nx][ny]) eq = eq - expr[nx][ny] / D(nx, ny) - mul(A[nx][ny], kpow(D(nx, ny), P - 2));
				} 
				eq = eq * D(i+1,j); eq = eq - A[i+1][j];
			}
		}
		assert((int)eqs.size()==N); // B数组表示到每个点所有的路径长度期望  Bu = sigma((Bv + Av) / Dv)
		ans = gauss(eqs);
		rep(i, 1, n+1) rep(j, 1, n+1) if (!hole[i][j]) B[i][j] = expr[i][j] * ans;
		rep(i, 1, n+1) rep(j, 1, n+1) if (hole[i][j]){
			B[i][j] = 0;
			rep(k, 0, 4) {
				int nx = i + dx[k], ny = j + dy[k];
				if (!hole[nx][ny]) B[i][j] = add(B[i][j], mul(A[nx][ny] + B[nx][ny], kpow(D(nx,ny), P - 2)));
			}
		}
		rep(i, 1, m+1) {
			if (!A[x[i]][y[i]]) cout << "GG";else cout << mul(B[x[i]][y[i]], kpow(A[x[i]][y[i]], P - 2));
			cout << " \n"[i == m];
		}
	}
}
