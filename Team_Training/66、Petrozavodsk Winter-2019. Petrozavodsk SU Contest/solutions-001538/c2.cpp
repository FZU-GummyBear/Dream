#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define x first
#define y second

const int K = 2005, M = 505, N = 200005, SZ = (1 << 21);
const int dx[] = {-1, 0, 1, 1, 1, 0}, dy[] = {0, -1, -1, 0, 1, 1};
const int dxx[] = {-1, -1, 0, 1, 1, 0, -1}, dyy[] = {0, -1, -1, 0, 1, 1, 0};

int n, ord[M][M], xx[3], yy[3], qq, r;
char brd[K][K];
map<pii, vector<int>> mp;
vector<pii> v[2 * SZ];

struct UF{
	int p[N], r[N];
	UF(){ iota(p, p + N, 0); }
	int f(int x){
		while(p[x] != x) x = p[x];
		return x;
	}
	void u(int x, int y, vector<int> &v){
		x = f(x);
		y = f(y);
		if(x == y) return;
		if(r[x] < r[y]) swap(x, y);
		p[y] = x; v.push_back(y);
		if(r[x] == r[y]){
			r[x]++; v.push_back(-x);
		}
	}
	void rv(vector<int> &v){
		reverse(v.begin(), v.end());
		for(int i : v){
			if(i > 0) p[i] = i;
			else r[-i]--;
		}
	}
} U;

void u(int s, int e, pii x){
	for(s += SZ, e += SZ; s <= e; s >>= 1, e >>= 1){
		if( s & 1) v[s++].push_back(x);
		if(~e & 1) v[e--].push_back(x);
	}
}

void f(int x){
	vector<int> vv;
	for(pii i : v[x]) U.u(i.x, i.y, vv);
	if(x >= SZ){ if(x - SZ < qq){
		int t = 0;
		for(int i = 0; i < 3; i++) t += (U.f(xx[i]) == U.f(yy[i]));
		r += (t >= 3);
	}}
	else{
		f(2 * x);
		f(2 * x + 1);
	}
	U.rv(vv);
}

int main(){
	scanf("%d ", &n);
	for(int i = 1; i <= 4 * n - 1; i++) fgets(brd[i] + 1, K, stdin);
	for(int i = 1, cnt = 0; i <= 2 * n - 1; i++){
		int ss = max(1, i - n + 1);
		int ee = min(2 * n - 1, i + n - 1);
		for(int j = ss; j <= ee; j++){
			ord[i][j] = ++cnt;
			int x = 2 * i + n - j, y = 2 * j;
			if(brd[x][y] != ' '){
				if(brd[x][y] <= 'C') xx[brd[x][y] - 'A'] = cnt;
				else yy[brd[x][y] - 'a'] = cnt;
			}
		}
	}
	for(int i = 1; i <= 2 * n - 1; i++){
		int ss = max(1, i - n + 1);
		int ee = min(2 * n - 1, i + n - 1);
		for(int j = ss; j <= ee; j++){
			int adj[8] = {};
			int x = 2 * i + n - j, y = 2 * j;
			for(int t = 0; t < 6; t++) adj[t] = (brd[x + dx[t]][y + dy[t]] != '@');
			adj[6] = adj[0];
			for(int t = 0; t < 6; t++){
				int cn = ord[i][j];
				int nn = ord[i + dxx[t]][j + dyy[t]], mm = ord[i + dxx[t + 1]][j + dyy[t + 1]];
				if(!nn || !mm) continue;
				if(adj[t] && adj[t + 1]){
					mp[minmax(cn, nn)].push_back(qq);
					mp[minmax(cn, mm)].push_back(qq);
					qq++;
				}
			}
		}
	}
	for(auto &i : mp){
		//printf("%d - %d\n", i.x.x, i.x.y);
		u(0, i.y[0] - 1, i.x);
		for(int j = 0; j + 1 < i.y.size(); j++) u(i.y[j] + 1, i.y[j + 1] - 1, i.x);
		u(i.y.back() + 1, SZ - 1, i.x);
	}
	vector<int> dmy;
	for(int i = 1; i <= 2 * n - 1; i++){
		int ss = max(1, i - n + 1);
		int ee = min(2 * n - 1, i + n - 1);
		for(int j = ss; j <= ee; j++){
			for(int t = 0; t < 6; t++){
				int cn = ord[i][j];
				int nn = ord[i + dxx[t]][j + dyy[t]];
				if(!nn) continue;
				if(cn > nn) continue;
				int x = 2 * i + n - j, y = 2 * j;
				if(brd[x + dx[t]][y + dy[t]] == '@') continue;
				if(!mp.count(minmax(cn, nn))){
					//printf("| %d - %d\n", min(cn, nn), max(cn, nn));
					U.u(cn, nn, dmy);
				}
			}
		}
	}
	f(1);
	printf("%d\n", r);
}
