// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

typedef db T;
const db eps = 1e-9 , pi = acosl(-1.);
int sgn(T x){return (x>eps)-(x<-eps);}
struct P{
  T x,y; P(){} P(T x,T y):x(x),y(y){}
  P operator - (const P&b) const {return P(x-b.x,y-b.y);}
  P operator + (const P&b) const {return P(x+b.x,y+b.y);}
  T operator * (const P&b) const {return x*b.x+y*b.y;}
  T operator / (const P&b) const {return x*b.y-y*b.x;}
  P operator * (const T&k) const {return P(x*k,y*k);}
  P operator / (const T&k) const {return P(x/k,y/k);}
  bool operator < (const P&b) const {return sgn(x-b.x)?x<b.x:y<b.y;}
  bool operator == (const P&b) const{return !sgn(x-b.x)&&!sgn(y-b.y);}
  P rot90(){return P(-y,x);}
  db arg() const {return atan2(y,x);}
};
T norm(P a){return a*a;}
T abs(P a) {return sqrtl(norm(a));}
P proj(P p,P a,P b){return (b-a)*((p-a)*(b-a)/norm(b-a))+a;}
P reflect(P p,P a,P b){return proj(p,a,b)*2-p;}
T cross(P o,P a,P b){return (a-o)/(b-o);}
int crossOp(P o,P a,P b){return sgn(cross(o,a,b));}
db rad(P p1,P p2){return atan2l(p1/p2,p1*p2);}
bool onPS(P p,P s,P t){return sgn((t-s)/(p-s))==0&&sgn((p-s)*(p-t))<=0;}
bool order(const P&a,const P&b){ return a.arg() < b.arg();}
struct L{ P s,t;L(){} L(P s,P t):s(s),t(t){}};
P insLL(L a,L b){ // line x line
  P s = a.s - b.s , v = a.t - a.s , w = b.t - b.s;
  db k1 = s / w , k2 = w / v;
  if(sgn(k2) == 0) return abs(b.s - a.s) < abs(b.t - a.s) ? b.s : b.t;
  return a.s + v * (k1 / k2);
}
bool isSSr(const L&a,const L&b){ // seg x seg restrict
  T c1=(a.t-a.s)/(b.s-a.s) , c2=(a.t-a.s)/(b.t-a.s),
    c3=(b.t-b.s)/(a.s-b.s) , c4=(b.t-b.s)/(a.t-b.s);
  return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
bool isSS(L a,L b){ // seg x seg , replace x->y to accelerate
  T c1=(a.t-a.s)/(b.s-a.s),c2=(a.t-a.s)/(b.t-a.s);
  T c3=(b.t-b.s)/(a.s-b.s),c4=(b.t-b.s)/(a.t-b.s);
  return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0 &&
    sgn(max(a.s.x,a.t.x) - min(b.s.x,b.t.x)) >= 0 &&
    sgn(max(b.s.x,b.t.x) - min(a.s.x,a.t.x)) >= 0 &&
    sgn(max(a.s.y,a.t.y) - min(b.s.y,b.t.y)) >= 0 &&
    sgn(max(b.s.y,b.t.y) - min(a.s.y,a.t.y)) >= 0;
}
bool inRegion(T a,T p,T b) {return sgn(a-p)==0||sgn(b-p)==0||(a<p!=b<p);}
bool inRec(P p,L a){ // p in Rectangle
  return inRegion(a.s.x,p.x,a.t.x) && inRegion(a.s.y,p.y,a.t.y);
}
db disPL(P p,L a){return fabs((a.t-a.s)/(p-a.s)) / abs(a.t-a.s);}
db disPS(P p,L a){ // p x seg dis
  if(sgn((a.t-a.s)*(p-a.s)) == -1) return abs(p-a.s);
  if(sgn((a.s-a.t)*(p-a.t)) == -1) return abs(p-a.t);
  return disPL(p,a);
}
db disSS(L a,L b){ // seg x seg dis
  if(isSS(a,b)) return 0;
  return min(min(disPS(a.s,b),disPS(a.t,b)),min(disPS(b.s,a),disPS(b.t,a)));
}
typedef vector<P> polygon;
polygon convex(polygon A){ // counter-clockwise , <= : <=180 , < : <180
  int n=sz(A),m=0;
  polygon B;B.resize(n+1);
  sort(all(A));
  rep(i,0,n){
    while(m > 1 && sgn((B[m-1]-B[m-2])/(A[i]-B[m-2]))<=0) --m;
    B[m++]=A[i];
  }
  per(i,0,n-1){
    while(m > 1 && sgn((B[m-1]-B[m-2])/(A[i]-B[m-2]))<=0) --m;
    B[m++]=A[i];
  }
  B.resize(m);
  if(sz(B) > 1) B.pop_back();
  return B;
}
T area(polygon A) { // multiple 2 with integer type
  T res=0;
  rep(i,0,sz(A)) res+=A[i]/(A[(i+1)%sz(A)]);
  return fabs(res) / 2;
}
bool isconvex(polygon A){ // counter-clockwise
  bool ok=1;int n=sz(A);
  rep(i,0,2) A.pb(A[i]);
  rep(i,0,n) ok&=((A[i+1]-A[i])/(A[i+2]-A[i]))>=0;
  return ok;
}
int inPpolygon(P p,polygon A){ // -1 : on , 0 : out , 1 : in
  int res=0;
  rep(i,0,sz(A)){
    P u=A[i],v=A[(i+1)%sz(A)];
    if(onPS(p,u,v)) return -1;
    T cross = sgn((v-u)/(p-u)) , d1 = sgn(u.y-p.y) , d2 = sgn(v.y-p.y);
    if(cross > 0 && d1 <= 0 && d2 > 0) ++res;
    if(cross < 0 && d2 <= 0 && d1 > 0) --res;
  }
  return res != 0;
}
T diameter(polygon A) { // longest distance
  int n=sz(A);if(n <= 1) return 0;
  int l=0,r=0;rep(i,1,n) (A[i]<A[l])&&(l=i),(A[r]<A[i])&&(r=i);
  db res=abs(A[l]-A[r]);int i=l,j=r;
  do (++((A[(i+1)%n]-A[i])/(A[(j+1)%n]-A[j])>=0?j:i))%=n,
    res=max(res,abs(A[i]-A[j]));
  while(i!=l||j!=r);
  return res;
}
polygon convexCut(polygon A,P s,P t){ // counter-clockwise , left hand of st
  int n=sz(A);
  polygon B;
  rep(i,0,n){
    P u=A[i],v=A[(i+1)%n];
    int d1 = sgn((t-s)/(u-s)) , d2 = sgn((t-s)/(v-s));
    if(d1 >= 0) B.pb(u);
    if(d1 * d2 < 0) B.pb(insLL(L(u,v),L(s,t)));
  }
  return B;
}
namespace NearestPoints{
  T solve(int l,int r,vector<P>&p){
    if(l == r) return 1e100;
    int m=(l+r)>>1;
    T Xm = p[m].x , lim = min(solve(l,m,p) , solve(m+1,r,p));
    inplace_merge(p.begin()+l,p.begin()+m+1,p.begin()+r+1,[&](P a,P b){return a.y<b.y;});
    vector<P> V;
    rep(i,l,r+1) if(fabs(p[i].x - Xm) <= lim) V.pb(p[i]);
    rep(i,0,sz(V)) rep(j,i+1,sz(V)){
      if(fabs(V[j].y - V[i].y) >= lim) break;
      T dis = abs(V[i]-V[j]);
      lim = min(lim,dis);
    }
    return lim;
  }
  T solve(vector<P> A){
    sort(all(A),[&](P a,P b){return a.x<b.x;});
    return solve(0,sz(A)-1,A);
  }
}
struct C{P o;T r;C(){} C(P o,T r):o(o),r(r){}
  bool operator == (const C&b) const {return o==b.o&&sgn(r-b.r)==0;}};
vector<P> insCL(C c,L a){
  db x = (a.s-c.o)*(a.t-a.s) , y = norm(a.t-a.s);
  db d = x * x - y * (norm(a.s-c.o) - c.r*c.r);
  vector<P> res;
  if(sgn(d) < 0) return res;
  d = max(d,0.);
  P mid = a.s - (a.t - a.s) * (x / y);
  P del = (a.t - a.s) * (sqrt(d) / y);
  return {mid - del,mid + del}; // dir : a.s -> a.t
}
vector<P> insCC(C a,C b){
  vector<P> res;
  T x = norm(a.o - b.o);
  if(sgn(x)==0) return res;
  T  y = ((a.r * a.r - b.r * b.r) / x + 1) / 2 ,
     d = a.r * a.r / x - y * y;
  if(sgn(d) < 0) return res;
  d = max(d,0.);
  P mid = (b.o - a.o) * y + a.o ,
    del = ((b.o - a.o) * sqrt(d)).rot90();
  return {mid - del , mid + del};// counter-clockwise along a
}
vector<P> tanCP(C c,P p){
  db x = norm(p - c.o) , d = x - c.r * c.r;
  vector<P> res;
  if(sgn(d) < 0) return res;
  d = max(d,0.);
  P mid = c.o + (p - c.o) * (c.r * c.r / x) ,
    del = ((p-c.o)*(c.r*sqrt(d)/x)).rot90();
  return {mid - del ,mid + del}; // counter-clockwise
}
vector<pair<P,P> > tanCC(C c1,C c2){// need to unique
  vector<pair<P,P> > res;
  // extan
  if(!sgn(c1.r-c2.r)){
    P dir = c2.o-c1.o;
    dir = (dir*(c1.r/abs(dir))).rot90();
    res.pb({c1.o+dir,c2.o+dir});
    res.pb({c1.o-dir,c2.o-dir});
  } else {
    P p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
    vector<P> ps = tanCP(c1 , p) , qs = tanCP(c2 , p);
    rep(i,0,min(sz(ps),sz(qs))) res.pb({ps[i],qs[i]});
  }
  // intan
  P p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  vector<P> ps = tanCP(c1 , p) , qs = tanCP(c2 , p);
  rep(i,0,min(sz(ps),sz(qs))) res.pb({ps[i],qs[i]});
  return res;
}
db areaCT(db r,P s,P t) { // need divide 2
  vector<P> p = insCL(C(P(0,0),r),L(s,t));
  if(!sz(p)) return r*r*rad(s,t);
  bool b1 = sgn(norm(s)-r*r) == 1 , b2 = sgn(norm(t)-r*r) == 1;
  if(b1 && b2) {
    if(sgn((s-p[0])*(t-p[0])) <= 0 && sgn((s-p[1])*(t-p[1])) <= 0)
      return r*r*(rad(s,p[0]) + rad(p[1],t)) + (p[0]/p[1]);
    else return r*r*rad(s,t);
  } else if(b1) return r*r*rad(s,p[0])+(p[0]/t);
  else if(b2) return r*r*rad(p[1],t)+(s/p[1]);
  return (s/t);
}
P inC(P A,P B,P C){
  db a = abs(B - C) , b = abs(C - A) , c = abs(A - B);
  return (A * a + B * b + C * c) / (a + b + c);
}
P outC(P A,P B,P C){
  P b = B - A , c = C - A;
  db dB = norm(b) , dC = norm(c) , d = b / c * 2;
  return A - P(b.y * dC - c.y * dB , c.x * dB - b.x * dC) / d;
}
P othroC(P A,P B,P C){
  P b = B - A , c = C - A;
  db Y = b.y * c.y * (B - C).y,
     a = c / b,
     xx = (Y + c.x * b.y * B.x - b.x * c.y * C.x) / a,
     yy = -b.x * (xx - C.x) / b.y + c.y;
  return P(xx , yy);
}
C Mincir(P *p,int n){
  random_shuffle(p , p + n);
  P o = p[0];db r = 0;
  rep(i,1,n) {
    if(sgn(abs(o-p[i])-r) <= 0) continue;
    o = p[i] , r = 0;
    rep(j,0,i) {
      if(sgn(abs(o-p[j])-r) <= 0) continue;
      o = (p[i] + p[j]) / 2 , r = abs(o-p[j]);
      rep(k,0,j) {
        if(sgn(abs(o-p[k])-r) <= 0) continue;
        o = outC(p[i],p[j],p[k]) , r = abs(o-p[k]);
      }}}
  return C(o,r);
}
namespace CCC{
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

const int N = 55;

int n;
C c[N], nc[N];
T ans[N];

bool check(db mid) {
	rep(i, 1, n + 1) nc[i] = c[i], nc[i].r = mid - c[i].r;
	CCC::solve(nc + 1, n, ans);
	return sgn(ans[n]) > 0;
}

int main() {
	scanf("%d", &n);
	db l = 0, r = 10000;
	rep(i, 1, n + 1) {
		int x, y, r; scanf("%d%d%d", &x, &y, &r);
		c[i] = C(P(x, y), r);
		l = max(l, (db)r);
	}
	rep(i, 0, 100) {
		db mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.7f\n", l);
	return 0;
}
