#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double dbl;
typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back

const int MAXN = 333;

const int mod = (int) (1e9 + 7);

inline void add (int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

inline void sub (int &a, int b) {
	a -= b;
	if (a < 0) a += mod;
}

inline void mult (int &a, int b) {
	a = a * 1ll * b % mod;
}


int C[MAXN][MAXN];
int ft[MAXN];

int n, k;
int cnt[MAXN][MAXN];
int t[MAXN];
int ans[MAXN];
int id[MAXN];
int inv[MAXN], tmr[MAXN];

void pre () {
	for (int i = 0; i < MAXN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i - 1][j - 1];
			add (C[i][j], C[i - 1][j]);
		}
	}
	ft[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		ft[i] = ft[i - 1];
		mult (ft[i], i);
	}
}

void calcCnt () {
	for (int i = 1; i < n; i++) {
		int cnt = n - i;
		int need = k;
		if (cnt < need) break;
		auto &res = ::cnt[0][i];
		for (int st = 0; need < n; st++, need++) {
			for (int pos = need; pos < n; pos++) {
				int ad = C[cnt - 1][need - 1];
				mult (ad, ft[need]);
				mult (ad, C[pos][need]);
				mult (ad, C[n - pos - 1][cnt - need]);
				mult (ad, ft[cnt - need]);
				mult (ad, ft[n - cnt - 1]);
				add (res, ad);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		cnt[i][i] = ft[n];
		for (int j = 1; j < i; j++) {
			cnt[j][i] = cnt[0][i];
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cnt[i][j] = ft[n];
			sub (cnt[i][j], cnt[0][i]);
		}
	}
}

void load () {
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> t[i];
}

inline bool comp (int a, int b) {
	return t[a] < t[b];
}

void solve () {
	for (int i = 0; i < n; i++) id[i] = i;
	sort (id, id + n, comp);

	calcCnt ();

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		int val = cnt[i][j];
			mult (val, t[id[j]]);
			add (tmr[i], val);		
    	}
    	for (int j = i + 1; j < n; j++) {
    		add (inv[i], cnt[i][j]);	
    	}
    	ans[id[i]] = tmr[i];
    	clog << id[i] << ' ' << tmr[i] << ' ' << inv[i] << endl;
    	mult (ans[id[i]], inv[i]);
    }

    for (int i = 0; i < n; i++) {
    	cout << ans[i] << ' ';
    }

    cout << endl;
}


int main () {
	ios_base::sync_with_stdio (false);
	cin.tie (NULL);

	pre ();
	load ();
	solve ();

	return 0;
}