#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef unsigned long long ull;
#define uint64 ull
typedef __uint128_t uint128;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;


ll mod_inv(ll a, ll mod) {
	if (__gcd(a, mod) != 1) return -1;
	ll b = mod, s = 1, t = 0;
	while (b) {
		ll q = a / b;
		swap(a -= q * b, b);
		swap(s -= q * t, t);
	}
	return s < 0 ? s + mod : s;
}

ull fact_pe(ull n, ull p, ull e) {
	vector<ull> pows(e+1, 1);
	ull pe = 1, min_pe = min(p, e);
	for (ull i = 1; i <= e; i++) pows[i] = (pe *= p);
	ull period = pe / p * 2, deg = e * 2 - 1;
	if (p == 2 && e >= 3) period >>= 1;
	vector<ull> s1(p* min_pe); s1[0] = 1;
	for (ull i = 1; i < p; ++i) {
		int o = i * min_pe;
		s1[o] = (uint128)s1[o - min_pe] * i % pe;
		for (ull j = 1; j < min_pe; ++j) {
			s1[o+j] = (s1[o+j - min_pe-1] + (uint128)s1[o+j - min_pe] * i) % pe;
		}
	}

	auto fact_range = [&] (ull u, ull  v) {
		ull coef = (uint128) u % pe * p % pe, prod = 1, ret = 0;
		for (ull k = 0; k < min_pe; ++k) {
			ret = (ret + (uint128)prod * s1[v * min_pe + k]) % pe;
			prod = (uint128) prod * coef % pe;
		}
		return ret;
	};

	ull fac = fact_range(0, p - 1), ifac = mod_inv(fac, pe);
	vector<ull> f_pe(deg, 1);
	for (ull i = 1; i < deg; ++i) {
		f_pe[i] = (uint128)f_pe[i-1] * fact_range(i-1, p-1) % pe * ifac % pe;
	}

	vector<ull> cifac(deg, 1), cfac_vs(deg);
	ull prod = 1;
	for (ull i = 1; i < deg; ++ i) {
		ull j = i, v = 0;
		for (; j % p == 0; j /= p, ++ v);
		cfac_vs[i] = cfac_vs[i-1] + v;
		cifac[i-1] = j;
		prod = (uint128) prod * j % pe;
	}
	cifac[deg-1] = mod_inv(prod, pe);
	for(int i = deg - 2; i >= 0; --i) {
		cifac[i] = (uint128)cifac[i + 1] * cifac[i] % pe;
	}

	auto evaluate = [&](uint64 x) {
		if(x < (uint64)deg) return f_pe[x];
		std::vector<uint64> vs(deg), inv(deg);
		uint64 v = 0, prod = 1;
		for(uint64 i = 0; i < deg; ++i) {
			uint64 m = x - i;
			for(; m % p == 0; m /= p, ++vs[i]);
			v += vs[i];
			inv[i] = prod;
			prod = (uint128)prod * m % pe;
		}
		uint64 iprod = mod_inv(prod, pe);
		for(int i = deg - 1; i >= 0; --i) {
			inv[i] = (uint128)iprod * inv[i] % pe;
			iprod = (uint128)iprod * ((x - i) / pows[vs[i]]) % pe;
		}
		uint64 ret = 0;
		for(uint64 i = 0; i < deg; ++i) {
			uint64 j = deg - 1 - i, ex = v - vs[i] - cfac_vs[i] - cfac_vs[j];
			if(ex >= e) continue;
			uint64 add = (uint128)cifac[j] * cifac[i] % pe;
			if(j & 1) add = pe - add;
			add = (uint128)pows[ex] * prod % pe * inv[i] % pe * add % pe * f_pe[i] % pe;
			ret = (ret + add) % pe;
		}
		return ret;
	};
	auto fact_p = [&](uint64 u, uint64 v) {
		return (uint128)fact_range(u, v) * evaluate(u) % pe;
	};
	uint64 ret = 1, ex = 0;
	while(n > 0) {
		uint64 q =  n / p, v = n % p;
		ull u = q % period;
		ret = (uint128)ret * fact_p(u, v) % pe;
		ex += u, n = q;
	}
	for(ex %= period; ex; ex >>= 1) {
		if(ex & 1) ret = (uint128)ret * fac % pe;
		fac = (uint128)fac * fac % pe;
	}
	return ret;

}

ull n, m, c1, c2, c3;
unsigned int a1, a2, a3;
ull cal(ull n) {
	ull res = 0;
	while (n) {
		n /= 2;
		res += n;
	}
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	c1 = cal(n);
	c2 = cal(m);
	c3 = cal(n - m);
	a1 = fact_pe(n, 2, 32);
	a2 = fact_pe(m, 2, 32);
	a3 = fact_pe(n - m, 2, 32);


	a1 *= mod_inv(a2, pw(32));
	a1 *= mod_inv(a3, pw(32));
	if (c1 - c2 - c3 >= 32) {
		cout << 0 << endl;
	}else {
		a1 = a1 * pw(c1 - c2 - c3);
		cout << a1 << endl;
	}
	return 0;
}
