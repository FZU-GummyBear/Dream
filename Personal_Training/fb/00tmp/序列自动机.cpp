
/* 
	0 is root 
	a is char size
	n is string lenth
	include empty string
*/

// ���� 
for(LL i=n;i>=1;--i){
    for(LL j=1;j<=a;++j) nxt[i-1][j]=nxt[i][j];
    nxt[i-1][s[i]]=i;
}

// �������Ĺ��������и��� 

LL Dfs(LL x,LL y){
    if(f[x][y]) return f[x][y];
    for(LL i=1;i<=a;++i)
        if(nxt1[x][i]&&nxt2[y][i])
            f[x][y]+=Dfs(nxt1[x][i],nxt2[y][i]);
    return ++f[x][y];
}

// ����������и��� 

LL Dfs(LL x,LL y){
    if(f[x][y]) return f[x][y];
    for(LL i=1;i<=a;++i)
        if(nxt1[x][i]&&nxt2[y][i]){
            if(nxt1[x][i]+nxt2[y][i]>n+1) continue;
            if(nxt1[x][i]+nxt2[y][i]<n+1) f[x][y]++;
            f[x][y]=(f[x][y]+Dfs(nxt1[x][i],nxt2[y][i]))%mod;
        }
    return ++f[x][y];
}

// ��һ�� A , B ������������� S ��ʹ�� C �� S �������� 
 
for(LL i=1;i<=a;++i) nxt[n][i]=n;
for(LL i=0;i<n;++i){
    for(LL j=1;j<=a;++j) nxt[i][j]=i;
    nxt[i][c[i+1]]=i+1;
}
