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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10002020;
const int P = 1e9 + 7;

int n, w[N], m, u, v, tmp[N], cnt;
bool g[50][50];

int Add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a;
}

struct Ht {
	static const int N = 23333333;
	int L, hd[N], ne[N], pp[N], val[N];
	inline void init() {
		rep(i, 0, L) hd[pp[i] % N] = -1;
		L = 0;
	}
	inline int qry(int p) {
		for(int i = hd[p % N]; ~i; i = ne[i]) {
			if(pp[i] == p) return val[i];
		}
		return 0;
	}
	inline void add(int p, int w) {
		bool f = 0;
		int k = p % N;
		for(int i = hd[k]; ~i; i = ne[i]) {
			if(pp[i] == p) {
				f = 1;
				val[i] = Add(val[i], w);
				break;
			} 
		}
		if(!f) {
			pp[L] = p, val[L] = w;
			ne[L] = hd[k], hd[k] = L;
			L++; 
		}
	}
} ht;


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v;
		u--;v--;
		g[u][v] = g[v][u] = 1;
	}	
	rep(i, 0, ht.N) ht.hd[i] = -1;
	ht.add(0, 1);
	rep(i, 0, n) {
		rep(i, 0, ht.L) {
			tmp[i] = ht.pp[i];
			w[i] = ht.val[i];
		}
		cnt = ht.L;
		ht.init();
		rep(j, 0, cnt) {
			for (int t = tmp[j], p = t & -t; t; t &= t - 1, p = t & - t) {
				int x = __builtin_ctz(p);
				if (g[x][i]) {
					int ne = tmp[j] ^ p;
					ht.add(ne, w[j]);
				}
			}
			int ne = tmp[j] ^ (1 << i);
			if (__builtin_popcount(ne) <= n - i - 1) ht.add(ne, w[j]);  
		}
	}
	cout << ht.qry(0) << endl;
	return 0;
}
