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
typedef vector<int> vi;
typedef double db;

const int N = 505;

int n, m, q, ans[202020], x[N][N], y[N][N], sum[202020];
char s[N][N];
string str[202020];

struct Node {
	int lx, ly, rx, ry, i;
	void print() { dd(lx), dd(rx), dd(ly), dd(ry), de(i); }
}nd[202020];
struct Stru {
	int x, l, r, i;
	int y;
	Stru() {}
	Stru(int x, int l, int r, int i) : x(x), l(l), r(r), i(i) {}
	Stru(int x, int y) : x(x), y(y) { i = 0; }
	bool operator < (const Stru &c) const { 
		if(x != c.x) return x < c.x; 
		return abs(i) < abs(c.i);
	}
};
vector<Stru> vec;

namespace Doubling{
	static const int N = 707070;
	// sa[0~n]: 排名第i的后缀是以 sa[i] 开头
	// h[1~n]:S[sa[i-1]] 与 S[sa[i]] 的最长公共前缀长度为 h[i]
	int t[N] , wa[N] , wb[N] , sa[N] , h[N];
	void sort(int *x,int *y,int n,int m){
		rep(i,0,m) t[i] = 0;
		rep(i,0,n) t[x[y[i]]]++;
		rep(i,1,m) t[i] += t[i-1];
		per(i,0,n) sa[--t[x[y[i]]]] = y[i];
	}
	bool cmp(int *x,int a,int b,int d){ return x[a] == x[b] && x[a+d] == x[b+d]; }
	void da(int *s,int n,int m){
		int *x=wa,*y=wb;
		rep(i,0,n) x[i] = s[i] , y[i] = i;
		sort(x , y , n , m);
		for(int j=1,p=1;p<n;m=p,j<<=1){
			p = 0;rep(i,n-j,n) y[p++] = i;
			rep(i,0,n) if(sa[i] >= j) y[p++] = sa[i] - j;
			sort(x , y , n , m);
			swap(x , y);p = 1;x[sa[0]] = 0;
			rep(i,1,n) x[sa[i]] = cmp(y,sa[i],sa[i-1],j)?p-1:p++;
		}
	}
	void cal_h(int *s,int n,int *rk){
		int j,k=0;
		for(int i=1;i<=n;++i) rk[sa[i]] = i;
		for(int i=0;i<n;h[rk[i++]] = k) for(k&&--k,j=sa[rk[i]-1];s[i+k]==s[j+k];++k);
	}
}
// rank[0~n-1]: 以 i 开头的后缀排名 rank[i]
char tt[N];
struct DA{ // [0,n] , in[n] = 0 , n load
	static const int N = 707070;
	int p[21][N] , rk[N] , in[N] , Log[N] , n;
	void Build(){
		Doubling::da(in,n+1,300);
		Doubling::cal_h(in,n,rk);
		Log[0] = -1;for(int i=1;i<=n;++i) Log[i] = Log[i-1] + (i==(i&(-i)));
		for(int i=1;i<=n;++i) p[0][i] = Doubling::h[i];
		for(int j=1;1<<j<=n;++j){
			int lim = n+1-(1<<j);
			for(int i=1;i<=lim;++i) p[j][i] = min(p[j-1][i] , p[j-1][i+(1<<j>>1)]);
		}
	}
	void print() {
		rep(i, 0, n) tt[i] = (char)('A' + in[i]); tt[n] = '\0';
		rep(i, 0, n + 1) {
			int s = Doubling::sa[i];
			dd(i), dd(s), de(tt + s);
		}
	}
	// 某两个后缀的最长公共前缀
	int lcp(int a,int b){
		//a = rk[a] , b = rk[b];
		if(a == b) return N;
		if(a > b) swap(a , b);++a;
		int t = Log[b-a+1];
		return min(p[t][a] , p[t][b-(1<<t)+1]);
	}
	void Get(int x, int len, int &st, int &ed) {
		int l = 1, r = x;
		while(l <= r) {
			int mid = l + r >> 1;
			if(lcp(mid, x) >= len) {
				st = mid; r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		l = x, r = n;
		while(l <= r) {
			int mid = l + r >> 1;
			if(lcp(x, mid) >= len) {
				ed = mid; l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
	}
}da;
struct FW {
#define lb(x) (x & -x)
	int n, a[707070];
	void upd(int p) {
	//	de(p);
		for( ; p <= n; p += lb(p)) a[p]++;
	}
	int _qry(int p) {
		int r = 0;
		for( ; p; p ^= lb(p)) r += a[p];
		return r;
	}
	int qry(int l, int r) { 
		int ans = _qry(r) - _qry(l - 1); 
//		dd(l), dd(r), de(ans);
		return ans;
	}
}fw;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> q;
	rep(i, 0, n) cin >> s[i];
	rep(i, 0, q) cin >> str[i], sum[i + 1] = sum[i] + sz(str[i]) + 1;
	//
	int k = 0;
	rep(j, 0, m) {
		rep(i, 0, n) da.in[k++] = s[i][j] - 'A';
		da.in[k++] = 26;
	}
	rep(i, 0, q) {
		for(auto u : str[i]) da.in[k++] = u - 'A';
		da.in[k++] = 26;
	}
	da.in[k] = 0; da.n = fw.n = k; da.Build();
//	da.print();
	rep(i, 0, n) rep(j, 0, m) x[i][j] = da.rk[j * (n + 1) + i];
	k = 0; rep(i, 0, q) {
		rep(j, 0, sz(str[i])) {
			da.Get(da.rk[m * (n + 1) + sum[i] + j], sz(str[i]) - j, nd[k].lx, nd[k].rx);
			k++;
		}
	}
	// 
	k = 0;
	rep(i, 0, n) {
		per(j, 0, m) da.in[k++] = s[i][j] - 'A';
		da.in[k++] = 26;
	}
	rep(i, 0, q) {
		reverse(all(str[i]));
		for(auto u : str[i]) da.in[k++] = u - 'A';
		da.in[k++] = 26;
	}
	da.in[k] = 0; da.n = k; da.Build();
//	da.print();
	rep(i, 0, n) rep(j, 0, m) y[i][j] = da.rk[i * (m + 1) + m - 1 - j];
	k = 0; rep(i, 0, q) {
		rep(j, 0, sz(str[i])) {
			da.Get(da.rk[n * (m + 1) + sum[i] + sz(str[i]) - 1 - j], j + 1, nd[k].ly, nd[k].ry);
			nd[k].i = i + 1; k++;
		}
	}
	//
	rep(i, 0, k) {
		vec.pb(Stru(nd[i].lx - 1, nd[i].ly, nd[i].ry, -nd[i].i));
		vec.pb(Stru(nd[i].rx, nd[i].ly, nd[i].ry, nd[i].i));
		/*
		rep(ti, 0, n) rep(j, 0, m) {
			int tx = x[ti][j], ty = y[ti][j];
			if(nd[i].lx <= tx && tx <= nd[i].rx && nd[i].ly <= ty && ty <= nd[i].ry) ++ans[nd[i].i];
		}
		nd[i].print();
		*/
	}
	rep(i, 0, n) rep(j, 0, m) vec.pb(Stru(x[i][j], y[i][j]));//, dd(i), dd(j), dd(x[i][j]), de(y[i][j]);
	sort(all(vec));
	for(auto u : vec) {
		if(u.i == 0) {
			fw.upd(u.y);
		} else {
			int res = fw.qry(u.l, u.r);
			if(u.i > 0) ans[u.i] += res;
			else ans[-u.i] -= res;
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
