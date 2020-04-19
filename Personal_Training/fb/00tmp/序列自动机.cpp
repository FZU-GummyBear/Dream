
/* 
	0 is root 
	a is char size
	n is string lenth
	include empty string
*/

// 构建 
for(LL i=n;i>=1;--i){
    for(LL j=1;j<=a;++j) nxt[i-1][j]=nxt[i][j];
    nxt[i-1][s[i]]=i;
}

// 求两串的公共子序列个数 

LL Dfs(LL x,LL y){
    if(f[x][y]) return f[x][y];
    for(LL i=1;i<=a;++i)
        if(nxt1[x][i]&&nxt2[y][i])
            f[x][y]+=Dfs(nxt1[x][i],nxt2[y][i]);
    return ++f[x][y];
}

// 求回文子序列个数 

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

// 求一个 A , B 的最长公共子序列 S ，使得 C 是 S 的子序列 
 
for(LL i=1;i<=a;++i) nxt[n][i]=n;
for(LL i=0;i<n;++i){
    for(LL j=1;j<=a;++j) nxt[i][j]=i;
    nxt[i][c[i+1]]=i+1;
}
