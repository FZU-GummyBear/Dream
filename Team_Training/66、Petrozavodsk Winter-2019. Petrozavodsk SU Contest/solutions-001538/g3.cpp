#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
#include <assert.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define SZ 555555
int n; ll k;
char s[SZ];
string G;
map<string,int> H;
int pos[23333],px[23333];
pii mi[100055][3];

struct info {
	int value;
	int type;
	int id;

	info(int value, int type, int id): value(value), type(type), id(id) {
	}

	bool operator < (const info &b) const {
		return value < b.value;
	}
};
#define N 233333
int m, a[N], b[N], cnt[N], res[N];
long long ans, cur;

void update() {
	if (ans > cur) {
		ans = cur;
		for (int i = 1; i <= n; ++i) {
			res[i] = cnt[i];
		}
	}
}
int main()
{
#define P(a) H[#a]=1;
	P(A) P(a) P(b) P(D) P(d) P(e)
		P(O) P(o) P(P) P(p) P(Q) P(q) P(R)
		H["B"]=H["g"]=2;
	for(int i=0;i<26;++i)
		G.pb('A'+i),G.pb('a'+i);
	assert(G.size()==52);
	for(int i=0;i<52;++i)
		pos[G[i]]=i,px[i]=H[G.substr(i,1)];
	scanf("%d%lld%s",&n,&k,s+1);
	if(k<0||k>2*n)
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		memset(mi[i],127/3,sizeof mi[0]);
		int t=pos[s[i]];
		for(int j=0;j<52;++j)
			mi[i][px[j]]=min(mi[i][px[j]],
					pii((j-t+52)%52,G[j]));
	}
	m=k; ll ap=0;
	vector<info> events;
	for (int i = 1; i <= n; ++i) {
		a[i]=mi[i][1].fi-mi[i][0].fi;
		b[i]=mi[i][2].fi-mi[i][0].fi;
		ap+=mi[i][0].fi;
		if (b[i] >= a[i] * 2) {
			events.emplace_back(a[i] * 2, 1, i);
			events.emplace_back((b[i] - a[i]) * 2, 1, i);
		} else {
			events.emplace_back(b[i], 2, i);
		}
	}
	sort(events.begin(), events.end());
	ans = 1ll << 60;
	for (auto p : events) {
		if (m >= p.type) {
			m -= p.type;
			cnt[p.id] += p.type;
			cur += p.value / (3 - p.type);
		} else {
			break;
		}
	}
	if (!m) {
		update();
	} else {
		{
			int pos_add = 0, min_add = 1 << 30;
			for (int i = 1; i <= n; ++i) {
				if (!cnt[i]) {
					if (min_add > a[i]) {
						min_add = a[i];
						pos_add = i;
					}
				} else if (cnt[i] == 1) {
					if (min_add > b[i] - a[i]) {
						min_add = b[i] - a[i];
						pos_add = i;
					}
				}
			}
			cur += min_add;
			++cnt[pos_add];
			update();
			cur -= min_add;
			--cnt[pos_add];
		}
		{
			int pos_add = 0, min_add = 1 << 30;
			for (int i = 1; i <= n; ++i) {
				if (!cnt[i]) {
					if (min_add > b[i]) {
						min_add = b[i];
						pos_add = i;
					}
				}
			}
			cur += min_add;
			cnt[pos_add] = 2;
			int pos_del = 0, max_del = -2e9;
			for (int i = 1; i <= n; ++i) {
				if (cnt[i] == 1) {
					if (max_del < a[i]) {
						max_del = a[i];
						pos_del = i;
					}
				} else if (cnt[i] == 2) {
					if (max_del < b[i] - a[i]) {
						max_del = b[i] - a[i];
						pos_del = i;
					}
				}
			}
			cur -= max_del;
			--cnt[pos_del];
			update();
		}
	}
	printf("%lld\n", ans+ap);
	for(int i=1;i<=n;++i)
		putchar(mi[i][res[i]].se);
	return 0;
}
