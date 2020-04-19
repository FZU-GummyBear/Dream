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
typedef pair<int, int> pii;
typedef double T;
typedef double db;
typedef vector<int> vi;

const db eps = 1e-8, pi = acos(-1);

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
	db x, y;
	P(db x = 0, db y = 0) : x(x), y(y) {}
	db operator / (const P &c) const {return x * c.y - y * c.x; }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	bool operator == (const P &c) const { return sign(x - c.x) == 0 && sign(y - c.y) == 0; }
};
struct C {
	P o; db r;
	C() {}
	C(P o, db r) : o(o), r(r) {}
};

namespace CircleIntersection{ // ?
	struct E{
		P p;T ang;int delta;
		E(){} E(P p,T ang,int delta):p(p),ang(ang),delta(delta){}
		bool operator < (const E&b) const {return ang<b.ang;}
	};
	bool overlap(C a,C b) {return sgn(a.r-b.r-abs(a.o-b.o))>=0;}
	void solve(C *c,int n,T *ans) {
		memset(ans , 0 , sizeof(T) * (n + 1));
		rep(i,0,n) {
			int cnt=1;
			vector<E> evt;
			rep(j,0,i) if(c[i]==c[j]) cnt++;
			rep(j,0,n) if(j!=i&&!(c[i]==c[j])&&overlap(c[j],c[i])) cnt++;
			rep(j,0,n) if(j!=i){
				vector<P> pts=insCC(c[i],c[j]);
				if(sz(pts)) {
					T a[2];
					rep(j,0,2) a[j]=(pts[j]-c[i].o).arg();
					evt.pb(E(pts[0],a[0],1));
					evt.pb(E(pts[1],a[1],-1));
					cnt += a[0] > a[1];
				}
			}
			if(!sz(evt)) ans[cnt] += pi*c[i].r*c[i].r;
			else{
				sort(all(evt));
				evt.pb(evt.front());
				rep(j,0,sz(evt)-1) {
					cnt+=evt[j].delta;
					ans[cnt] += evt[j].p / evt[j+1].p / 2;
					db ang = evt[j + 1].ang - evt[j].ang;
					if(ang < 0) ang += pi * 2;
					ans[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
				}}}}}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	return 0;
}
