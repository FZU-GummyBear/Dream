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

const int N = 1e5 + 8;
unsigned int a[3] = {3, 4, 5};
int T, n, ma;
ll ans;

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};
//传入{3,4,5}, 枚举所有互素的勾股数对, 改成bfs可能会快一点

void dfs(int a[3], int d) {
  int b[3]; 
  ans += n / a[2];
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  if (b[2] <= n) dfs(b, d + 1);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  if (b[2] <= n) dfs(b, d + 1);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  if (b[2] <= n) dfs(b, d + 1);
}

int now[N], l, r, cnt; unsigned int tmp[3], b[N][3]; 

void bfs(unsigned int a[3]) {
  //int b[3]; 
  r = 0; now[r] = 0; memcpy(b[r], a, sizeof(b[r])); ans += n / 5;
  while (r >= 0) {
  	if (now[r] > 2) {r--;continue;}
	if (now[r] == 0) for (int i=0;i<3;++i) tmp[i]=A[i][0]*b[r][0]+A[i][1]*b[r][1]+A[i][2]*b[r][2];
  	if (now[r] == 1) for (int i=0;i<3;++i) tmp[i]=B[i][0]*b[r][0]+B[i][1]*b[r][1]+B[i][2]*b[r][2];
  	if (now[r] == 2) for (int i=0;i<3;++i) tmp[i]=C[i][0]*b[r][0]+C[i][1]*b[r][1]+C[i][2]*b[r][2];
  	now[r]++;
	if (tmp[2] <= n) cnt++, memcpy(b[++r], tmp, sizeof(tmp)), now[r] = 0, ans += n / tmp[2]; 
  }
}

int main() {
	FI(a);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T; 
	T = 1;
	rep(cas, 0, T) {
		cin >> n; ans = 0;
		if (n >= 5) bfs(a);
		cout << ans << endl;
		de(cnt);
	}
	return 0;
}


