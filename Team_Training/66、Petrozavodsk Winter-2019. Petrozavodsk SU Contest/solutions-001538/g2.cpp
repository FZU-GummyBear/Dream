#include <bits/stdc++.h>
using namespace std;

#define pb push_back

typedef long long LL;

const int MAXN=100005,HE[52]={1,1,2,1,0,0,1,1,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1};

char s[MAXN];
int pay[MAXN][3],dp[MAXN*2],tmp[MAXN*2],tmp2[MAXN*2],q[MAXN*2],pre[52][MAXN*2],val[52];
vector <int> pos[52];

inline int get_id(char c)
{
	if ('A'<=c&&'Z'>=c)
		return (c-'A')*2;
	return (c-'a')*2+1;
}

inline char to_letter(int k)
{
	if (k&1)
		return 'a'+k/2;
	return 'A'+k/2;
}

void work(int cnt,int x,int m)
{
	for (int i=0;i<=m;i++)
		pre[x][i]=i;
	if (cnt==0)
		return;
	for (int i=0;i<=m;i++)
		tmp[i]=dp[i];
	if ((pay[x][2]-pay[x][0])>=2*(pay[x][1]-pay[x][0]))
	{
		for (int i=0;i<=m;i++)
			tmp2[i]=tmp[i]-i*(pay[x][1]-pay[x][0]);
		int h=0,t=-1;
		for (int i=0;i<=m;i++)
		{
			if (h<=t&&i-q[h]>cnt)
				h++;
			while (h<=t&&tmp2[q[t]]>=tmp2[i])
				t--;
			q[++t]=i;
			if (dp[i]>tmp2[q[h]]+i*(pay[x][1]-pay[x][0]))
			{
				dp[i]=tmp2[q[h]]+i*(pay[x][1]-pay[x][0]);
				pre[x][i]=q[h];
			}
		}
		for (int i=0;i<=m;i++)
			tmp2[i]=tmp[i]-i*(pay[x][2]-pay[x][1]);
		h=0;
		t=-1;
		for (int i=0;i<=m;i++)
		{
			if (h<=t&&i-q[h]>2*cnt)
				h++;
			if (i>=cnt)
			{
				while (h<=t&&tmp2[q[t]]>=tmp2[i-cnt])
					t--;
				q[++t]=i-cnt;
				if (dp[i]>tmp2[q[h]]+(i-cnt)*(pay[x][2]-pay[x][1])+cnt*(pay[x][1]-pay[x][0]))
				{
					dp[i]=tmp2[q[h]]+(i-cnt)*(pay[x][2]-pay[x][1])+cnt*(pay[x][1]-pay[x][0]);
					pre[x][i]=q[h];
				}
			}
		}
	}
	else
	{
		for (int i=0;i<=m;i++)
			tmp2[i]=tmp[i]-i/2*(pay[x][2]-pay[x][0]);
		int h=0,t=-1;
		for (int i=0;i<=m;i+=2)
		{
			if (h<=t&&i-q[h]>2*cnt)
				h++;
			while (h<=t&&tmp2[q[t]]>=tmp2[i])
				t--;
			q[++t]=i;
			if (dp[i]>tmp2[q[h]]+i/2*(pay[x][2]-pay[x][0]))
			{
				dp[i]=tmp2[q[h]]+i/2*(pay[x][2]-pay[x][0]);
				pre[x][i]=q[h];
			}
		}
		h=0;
		t=-1;
		for (int i=1;i<=m;i+=2)
		{
			if (h<=t&&i-q[h]>2*cnt)
				h++;
			while (h<=t&&tmp2[q[t]]>=tmp2[i])
				t--;
			q[++t]=i;
			if (dp[i]>tmp2[q[h]]+i/2*(pay[x][2]-pay[x][0]))
			{
				dp[i]=tmp2[q[h]]+i/2*(pay[x][2]-pay[x][0]);
				pre[x][i]=q[h];
			}
		}
		for (int i=0;i<=m;i++)
			tmp2[i]=tmp[i]-i/2*(pay[x][2]-pay[x][0]);
		h=0;
		t=-1;
		for (int i=1;i<=m;i+=2)
		{
			if (h<=t&&i-q[h]>=2*cnt)
				h++;
			while (h<=t&&tmp2[q[t]]>=tmp2[i-1])
				t--;
			q[++t]=i-1;
			if (dp[i]>tmp2[q[h]]+(i-1)/2*(pay[x][2]-pay[x][0])+(pay[x][1]-pay[x][0]))
			{
				dp[i]=tmp2[q[h]]+(i-1)/2*(pay[x][2]-pay[x][0])+(pay[x][1]-pay[x][0]);
				pre[x][i]=q[h];
			}
		}
		h=0;
		t=-1;
		for (int i=2;i<=m;i+=2)
		{
			if (h<=t&&i-q[h]>=2*cnt)
				h++;
			while (h<=t&&tmp2[q[t]]>=tmp2[i-1])
				t--;
			q[++t]=i-1;
			if (dp[i]>tmp2[q[h]]+(i-1)/2*(pay[x][2]-pay[x][0])+(pay[x][1]-pay[x][0]))
			{
				dp[i]=tmp2[q[h]]+(i-1)/2*(pay[x][2]-pay[x][0])+(pay[x][1]-pay[x][0]);
				pre[x][i]=q[h];
			}
		}
	}
}

int main()
{
#ifdef local
	freopen("read.txt","r",stdin);
#endif // local
	int n;
	LL k;
	scanf("%d%lld%s",&n,&k,s);
	if (k>=0&&k<=2*n)
	{
		for (char c='A';c<='Z';c++)
		{
			int k=get_id(c);
			memset(pay[k],-1,sizeof(pay[k]));
			for (int j=0;j<52;j++)
				if (pay[k][HE[(k+j)%52]]==-1)
					pay[k][HE[(k+j)%52]]=j;
		}
		for (char c='a';c<='z';c++)
		{
			int k=get_id(c);
			memset(pay[k],-1,sizeof(pay[k]));
			for (int j=0;j<52;j++)
				if (pay[k][HE[(k+j)%52]]==-1)
					pay[k][HE[(k+j)%52]]=j;
		}
		//        for (int i=0;i<52;i++)
		//        {
		//            for (int j=0;j<3;j++)
		//                printf("%d ",pay[i][j]);
		//            puts("");
		//        }
		int cnt[52],sum_init=0;
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<n;i++)
		{
			int k=get_id(s[i]);
			cnt[k]++;
			sum_init+=pay[k][0];
		}
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		//printf("%d\n",sum_init);
		for (int i=0;i<52;i++)
		{
			work(cnt[i],i,k);
			//            if (cnt[i])
			//            {
			//                for (int j=0;j<=k;j++)
			//                    printf("%d ",dp[j]);
			//                puts("");
			//            }
		}
		printf("%d\n",sum_init+dp[k]);
		for (int i=51,now=k;i>=0;i--)
		{
			val[i]=now-pre[i][now];
			now=pre[i][now];
		}
		for (int i=0;i<n;i++)
			pos[get_id(s[i])].pb(i);
		for (int i=0;i<52;i++)
		{
			char nxt[3];
			for (int j=0;j<3;j++)
				for (int k=0;;k++)
					if (HE[(i+k)%52]==j)
					{
						nxt[j]=to_letter((i+k)%52);
						break;
					}
			for (int p:pos[i])
				s[p]=nxt[0];
			if ((pay[i][2]-pay[i][0])>=2*(pay[i][1]-pay[i][0]))
			{
				for (int j=0;j<pos[i].size()&&val[i];j++)
				{
					s[pos[i][j]]=nxt[1];
					val[i]--;
				}
				for (int j=0;j<pos[i].size()&&val[i];j++)
				{
					s[pos[i][j]]=nxt[2];
					val[i]--;
				}
			}
			else
			{
				for (int j=0;j<pos[i].size()&&val[i];j++)
				{
					if (val[i]>=2)
					{
						val[i]-=2;
						s[pos[i][j]]=nxt[2];
					}
					else
					{
						val[i]--;
						s[pos[i][j]]=nxt[1];
					}
				}
			}
		}
		puts(s);
	}
	else
		puts("-1");
	return 0;
}
