#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;
string pole[1005];
int was[1005][1005];
int fup[1005][1005];
int timer = 0;
char to_a_danger_edge[1005][1005][7];
char to_A_danger_edge[1005][1005][7];
char to_b_danger_edge[1005][1005][7];
char to_B_danger_edge[1005][1005][7];
char to_c_danger_edge[1005][1005][7];
char to_C_danger_edge[1005][1005][7];

bool is_not_letter(char c)
{
	if(c == 'A')
		return 0;
	if(c == 'B')
		return 0;
	if(c == 'C')
		return 0;
	if(c == 'a')
		return 0;
	if(c == 'b')
		return 0;
	if(c == 'c')
		return 0;
	return 1;

}

int n;
/*
   _   
 _/ \_ 
/ \_/ \
\_/c\_/
/ \_/ \
\_/ \_/
  \_/  
*/

int ddx[] = {-1, 0, 1, 1,  1,  0, -1}; //up right ... up
int ddy[] = { 0, 1, 1, 0, -1, -1,  0};
char symbol[] = {'_', '\\', '/', '_', '\\', '/', '_'} ;

int dx[] = {-2, -1, 1, 2,  1, -1, -2};
int dy[] = { 0,  2, 2, 0, -2, -2,  0};

bool iscell(int x, int y)
{
	if(x < 0 || y < 0)
		return 0;
	if(pole[x][y] != ' '  && is_not_letter(pole[x][y])   )
		return 0;
	for(int i = 0; i < 6; i++)
	{
		int nx = x + ddx[i];
		int ny = y + ddy[i];
		if(nx < 0 || ny < 0)
			return 0;
		if(pole[nx][ny] != symbol[i] && pole[nx][ny] != '@')
			return 0;
	}
	return 1;
}

bool can_go(int x, int y, int t)
{
	int nnx1 = x + ddx[t];
    int nny1 = y + ddy[t];
    int nx1 = x + dx[t];
	int ny1 = y + dy[t];
	if(nnx1 >= 0 && nny1 >= 0 && pole[nnx1][nny1] != '@' && iscell(nx1, ny1) )
		return 1;
	return 0;
}

void set_danger(char c, int x, int y, int t)
{
	if(c == 'a'){
		to_a_danger_edge[x][y][t] = 1;	
		to_a_danger_edge[x][y][6] ++;			
	}
	if(c == 'b'){
		to_b_danger_edge[x][y][t] = 1;	
		to_b_danger_edge[x][y][6] ++;			
	}
	if(c == 'c'){
		to_c_danger_edge[x][y][t] = 1;	
		to_c_danger_edge[x][y][6] ++;			
	}
	if(c == 'A'){
		to_A_danger_edge[x][y][t] = 1;	
		to_A_danger_edge[x][y][6] ++;			
	}
	if(c == 'B'){
		to_B_danger_edge[x][y][t] = 1;	
		to_B_danger_edge[x][y][6] ++;			
	}
	if(c == 'C'){
		to_C_danger_edge[x][y][t] = 1;	
		to_C_danger_edge[x][y][6] ++;			
	}
	
}


void set6(char c, int x, int y)
{
	if(c == 'a'){
		to_a_danger_edge[x][y][6] = 6;			
	}
	if(c == 'b'){
		to_b_danger_edge[x][y][6] = 6;			
	}
	if(c == 'c'){
		to_c_danger_edge[x][y][6] = 6;			
	}
	if(c == 'A'){
		to_A_danger_edge[x][y][6] = 6;			
	}
	if(c == 'B'){
		to_B_danger_edge[x][y][6] = 6;			
	}
	if(c == 'C'){
		to_C_danger_edge[x][y][6] = 6;			
	}
	
}

void show()
{
		for(int i = 0; i < n; i++, cerr << "\n")
		for(int j = 0; j < n; j++)
			if(pole[i][j] == ' ' || isalpha(pole[i][j]))
				if(iscell(i, j))
					cerr << was[i][j];
				else
					cerr << "0";
			else
				cerr << pole[i][j];

}

bool dfs(int x, int y, char aim, int px = -1, int py = -1)  //надо ли начало отдельно?
{
	//show();
	//cerr << "\n";
	was[x][y] = ++timer ;
	fup[x][y] = was[x][y];
	bool was_aim = (pole[x][y] == aim);
	if(was_aim == 1)
		set6(aim, x, y);
	for(int t = 0; t < 6; t++)
	{
		if(can_go(x, y, t))
		{			
			int nx = x + dx[t];
			int ny = y + dy[t];
			if(nx == px && ny == py)
				continue;
			if(was[nx][ny] != 0)
			{
				fup[x][y] = min(was[nx][ny], fup[x][y]);
			}
			else
			{
				bool cur_aim = dfs(nx, ny, aim, x, y);
				was_aim |= cur_aim;
				fup[x][y] = min(fup[nx][ny], fup[x][y]);
			    if(fup[nx][ny] >= was[x][y] && cur_aim) //danger!
				{
					for(int i = 0; i < 6; i++)
					{
						if(can_go(x, y, i))
						{
							int nxc = x + dx[i];
							int nyc = y + dy[i];
							if(was[nxc][nyc] >= was[nx][ny]){
								set_danger(aim, x, y, i);
		//						cerr << "set danget " << x << " " << y << "  <-> " << nxc << " " << nyc << "\n";
							}
						}			        	
					}	
				}
			}
		
		}
	}
	return was_aim;
}

void read_ascii()
{
	cin >> n;
	n = 4*n - 1;
	getline(cin, pole[0]);
	for(int i = 0; i < n; i++)
	{
		getline(cin, pole[i]);
	}
}


int letter_for_which_it_is_dangerous(int x, int y, int t1, int t2)
{
	int res = 0;
	{//a -> A
	 	int to_a = to_a_danger_edge[x][y][6];
	 	int to_A = to_A_danger_edge[x][y][6];
		if((to_a == 0 || to_A == 0) && (pole[x][y] != 'a' && pole[x][y] != 'A') )
			;
		else
		{
			if(to_a_danger_edge[x][y][t1])
				to_a -- ;
			if(to_A_danger_edge[x][y][t1])
				to_A -- ;
			if(to_a_danger_edge[x][y][t2])
				to_a -- ;
			if(to_A_danger_edge[x][y][t2])
				to_A -- ;
			if(to_a == 0 || to_A == 0)
				res = 1;
		}		
	}
	{//b -> B

	 	int to_b = to_b_danger_edge[x][y][6];
	 	int to_B = to_B_danger_edge[x][y][6];
		if((to_b == 0 || to_B == 0) && (pole[x][y] != 'b' && pole[x][y] != 'B'))
			;
		else
		{
			if(to_b_danger_edge[x][y][t1])
				to_b -- ;
			if(to_B_danger_edge[x][y][t1])
				to_B -- ;

			if(to_b_danger_edge[x][y][t2])
				to_b -- ;
			if(to_B_danger_edge[x][y][t2])
				to_B -- ;
	   	
			if(to_b == 0 || to_B == 0)
				res = 1;		
		}
	}
	{//c -> C
	 	int to_c = to_c_danger_edge[x][y][6];
	 	int to_C = to_C_danger_edge[x][y][6];
		if((to_c == 0 || to_C == 0) && (pole[x][y] != 'c' && pole[x][y] != 'C'))
			;
		else
		{
			if(to_c_danger_edge[x][y][t1])
				to_c -- ;
			if(to_C_danger_edge[x][y][t1])
				to_C -- ;

			if(to_c_danger_edge[x][y][t2])
				to_c -- ;
			if(to_C_danger_edge[x][y][t2])
				to_C -- ;

			if(to_c == 0 || to_C == 0)
				res = 1;	
		}	
	}
	return res;

}
int danger_angles()                  
{
	int res  = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			if(iscell(i, j)){
				int x = i;
				int y = j;
				for(int t = 0; t < 6; t++)
				{
	                int nnx1 = x + ddx[t];
	                int nny1 = y + ddy[t];
	                int nnx2 = x + ddx[(t + 1) % 6];
	                int nny2 = y + ddy[(t + 1) % 6];

	                int nx1 = x + dx[t];
	                int ny1 = y + dy[t];
	                int nx2 = x + dx[(t + 1) % 6];
	                int ny2 = y + dy[(t + 1) % 6];

					if(pole[nnx1][nny1] != '@' && pole[nnx2][nny2] != '@' && iscell(nx1, ny1) && iscell(nx2, ny2))
					{
						res += letter_for_which_it_is_dangerous(x, y, t, (t+1)%6);	
		//				if(letter_for_which_it_is_dangerous(x, y, t, (t+1)%6) > 0)
		//					cerr << "ij = " << i << " " << j << "\n";							
					}	
				}
			}
		}
	return res;	
}
int all_angles()
{
	int res  = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			if(iscell(i, j)){
		//		cerr << " +1 cell \n" ;
				int x = i;
				int y = j;
				for(int t = 0; t < 6; t++)
				{
	                int nnx1 = x + ddx[t];
	                int nny1 = y + ddy[t];
	                int nnx2 = x + ddx[(t + 1) % 6];
	                int nny2 = y + ddy[(t + 1) % 6];

	                int nx1 = x + dx[t];
	                int ny1 = y + dy[t];
	                int nx2 = x + dx[(t + 1) % 6];
	                int ny2 = y + dy[(t + 1) % 6];

					if(pole[nnx1][nny1] != '@' && pole[nnx2][nny2] != '@' && iscell(nx1, ny1) && iscell(nx2, ny2))
					{
	//					cerr << "1";
						res ++;							
					}	
	//				else
	//					cerr << "0";
				}
	//			cerr << "\nres = " << res << "\n";
			}
		}
	return res;	
}

void go(int i, int j, char c)
{
	for(int x = 0; x < n; x++)
		for(int y = 0; y < n; y++)
		{
			was[x][y] = 0;
			fup[x][y] = 0;	
		}
	timer = 0;		
	dfs(i, j, (islower(c) ? toupper(c) : tolower(c)));
}
void calc_danger_edges()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){

			if(pole[i][j] == 'a'){
				go(i, j, 'a') ;
			}
			if(pole[i][j] == 'b')
				go(i, j,'b') ;
			if(pole[i][j] == 'c')
				go(i, j,'c') ;
			if(pole[i][j] == 'A'){
				go(i, j,'A') ;
			
			}
			if(pole[i][j] == 'B')
				go(i, j,'B') ;
			if(pole[i][j] == 'C')
				go(i, j,'C') ;
		}		
	}		

}

void solve()
{
	int all = all_angles();
	//cerr << all << " ?? all \n";
	
	calc_danger_edges();
	all -= danger_angles();
	//cerr << "to_a_danger_edge = " << (int)to_a_danger_edge[12][9][6] << "\n";
	cout << all;
}


int main()
{
	auto st=clock();
	ios::sync_with_stdio(0);
	read_ascii();
	/*
	for(int i = 0; i < n; i++, cerr << "\n")
		for(int j = 0; j < n; j++)
			if(pole[i][j] == ' ' || isalpha(pole[i][j]))
				if(iscell(i, j))
					cerr << '1';
				else
					cerr << "0";
			else
				cerr << pole[i][j];
	*/
	solve();
	cerr<<(double)(clock()-st)/CLOCKS_PER_SEC<<"\n";
}
