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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----


const int mod=998244353;
map<string,string>trans;
map<string,int>state;
string str[15];int tot,n,m;
void add(string s){str[state[s]=++tot]=s;}
int f(string s){
    string t;
    for(int i=0;i<s.size();++i){
        t+=s[i];
        if(trans.count(t))t=trans[t];
    }
    return state[t];
}

// 12种等价类 应该是可以通过搜索设定一个迭代长度去搜出来 

// O(len^2)
// s_{m} = \sum_{j=0}^{m−1}s_{j}*c_{j} 适配线性递推
vi BM(vi s) {
	vi C(1, 1), B(1, 1);
	int L = 0, m = 1, b = 1;
	rep(n, 0, sz(s)) {
		ll d = 0;
		rep(i, 0, L+1) (d += 1ll * C[i] * s[n-i]) %= P;
		if(d == 0) ++m;
		else {
			vi T = C;
			ll c = P - d * kpow(b, P - 2) % P;
			while(sz(C) < sz(B) + m) C.pb(0);
			rep(i, 0, sz(B)) C[i + m] = add(C[i + m], mul(c, B[i]));
			if(2 * L <= n) L = n + 1 - L, B = T, b = d, m = 1;
			else ++m;
		}
	}
	reverse(all(C));
	rep(i, 0, sz(C)) C[i] = P - C[i];
	return vi(C.begin(), C.end() - 1);
}

// a_{m} = \sum_{j=0}^{m−1}a_{j}*c_{j} O(m^2lgn)
int linear_recurrence(ll n, int m, vi a, vi c) {
	if (n<m) return (a[n]+P)%P;
	vector<ll> v(m, 0), u(m<<1, 0);
	v[0] = 1;
	for(ll x = 0, W = n ? 1ll<<(63 - __builtin_clzll(n)) : 0; W; W >>= 1, x <<= 1) {
		fill(all(u), 0);
		int b = !!(n & W); if(b) x++;
		if(x < m) u[x] = 1;
		else {
			rep(i, 0, m) rep(j, 0, m) (u[i + b + j] += v[i] * v[j]) %= P;
			per(i, m, 2*m) rep(j, 0, m) (u[i - m + j] += c[j] * u[i]) %= P;
		}
		copy(u.begin(), u.begin() + m, v.begin());
	}
	ll ans = 0;
	rep(i, 0, m) (ans += v[i] * a[i]) %= P;
	return (ans+P)%P;
}

vi a[20];
int tmp[20];

int main(){
    add("");
    add("a");
    add("b");
    trans["aa"]="";
    add("ab");
    add("ba");
    add("bb");
    add("aba");
    add("abb");
    trans["baa"]="b";
    add("bab");
    add("bba");
    trans["bbb"]="";
    trans["abaa"]="ab";
    trans["abab"]="bba";
    trans["abba"]="bab";
    trans["abbb"]="a";
    trans["baba"]="abb";
    add("babb");
    trans["bbaa"]="bb";
    add("bbab");
    trans["babba"]="bbab";
    trans["babbb"]="ba";
    trans["bbaba"]="babb";
    trans["bbabb"]="aba";
    rep(i, 1, tot+1) a[i].pb(i == 1);
	rep(i, 1, 20+1) {
		rep(j, 1, tot+1) {
			int p1 = f(str[j] + "a"), p2 = f(str[j] + "b");
			tmp[p1] = add(tmp[p1], a[j].back()); 
			tmp[p2] = add(tmp[p2], a[j].back()); 
		}
		rep(j, 1, tot+1) a[j].pb(tmp[j]), tmp[j] = 0;
	} 
    cin >> n>> str[0] >> m;
    int p = f(str[0]);
    vi c = BM(a[p]);
    cout << linear_recurrence(m, sz(c), a[p], c) <<endl;
    return 0;
}
