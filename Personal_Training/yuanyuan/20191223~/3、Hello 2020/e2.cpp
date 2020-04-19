// https://ac.nowcoder.com/acm/contest/view-submission?submissionId=41085983
#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const int maxn=3030;
const int E=2e9+7;
const int EE=1e4+83;
ll x[maxn],y[maxn],ans,sum;
ll sqr(ll x){return x*x;}
pi p[maxn],b[maxn*maxn],V[maxn][maxn];
unordered_map <ll,int> f;
int a[maxn][maxn],c[maxn*maxn],pos[maxn];
int n;
bool cmp(pi x,pi y){
	pi u=V[x.F][x.S];
	pi v=V[y.F][y.S];
	if (u.F*v.S==v.F*u.S) {
		if (x.F!=y.F) return x.F<y.F;
		return x.S<y.S;
	}
	return u.F*v.S<v.F*u.S;
}
ll mut(pi x,pi y,pi z){
	return (y.F-x.F)*(z.S-x.S)-(y.S-x.S)*(z.F-x.F);
}
int main(){
	cin >> n;
	for (int i=1;i<=n;i++) c[i*(i-1)/2]=i;
	for (int i=0;i<n;i++) cin >> x[i] >> y[i];
	for (int i=0;i<n;i++){
		p[i].F=x[i]; p[i].S=y[i];
		pos[i]=i;
	}
	sort(p,p+n);
	int cc=0;
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			b[++cc]=(pi){i,j},V[i][j]=(pi){p[j].F-p[i].F,p[j].S-p[i].S};
	sort(b+1,b+cc+1,cmp);
	for (int i=1;i<=cc;i++){
		int u=b[i].F,v=b[i].S;
		int l,r,mid,S,T;
		l=-1; r=n;
		while (r-l>1){
			int mid=(l+r)>>1;
			if (mut(p[pos[u]],p[pos[v]],p[mid])>0) l=mid; else r=mid;
		}
		S=l+1;
		l=-1; r=n;
		while (r-l>1){
			int mid=(l+r)>>1;
			if (mut(p[pos[u]],p[pos[v]],p[mid])<0) r=mid; else l=mid;
		}
		T=n-r;
		swap(p[pos[u]],p[pos[v]]);
		swap(pos[u],pos[v]);
		sum+=S*T;
	}
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++){
			ll p=x[i]-x[j],q=y[i]-y[j];
			bool o=0;
			if (p<0) o=1; else if (p==0&&q<0) o=1;
			if (o) p=-p,q=-q;
			int d=abs(__gcd(p,q));
			p/=d; q/=d;
			ll pp,qq;
			if (p==0) pp=0,qq=x[i];
			else {
				pp=y[i]*(x[j]-x[i])-x[i]*(y[j]-y[i]);
				qq=x[j]-x[i];
				ll dd=__gcd(pp,qq);
				pp/=dd; qq/=dd;
				if (qq<0) qq=-qq,pp=-pp;
			}
			f[(p*EE+q)*E+pp*EE+qq]++;
		}
	for (auto x:f){
		int t=c[x.second];
		sum-=1ll*t*(t-1)*(t-2)*(t-3)/24*2;
		sum+=1ll*t*(t-1)*(t-2)/6*(n-3);
	}
	ans=sum-1ll*n*(n-1)*(n-2)*(n-3)/24*2;
	cout << ans * (n - 4) / 2 << endl;
	return 0;
}
