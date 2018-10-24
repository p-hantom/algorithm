#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 100
#define LOCAL
using namespace std;

char a[maxn][maxn];
int m,n;

void dfs(int x,int y){
	if(x<0||x>=m||y<0||y>=n){
		return ;
	}
	if(a[x][y]!='@'){
		return ;
	}
	a[x][y]='*';
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i!=0||j!=0){
				dfs(x+i,y+j);	
			}			
		}
	}
}

int main(){	
#ifdef LOCAL
	freopen("eg_6_12.txt","r",stdin);
#endif
	memset(a,0,sizeof(a));
	
	cin>>m>>n;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	
	int cnt=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]=='@'){
				cnt++;
				dfs(i,j);
			}
		}
	}
	cout<<cnt<<endl;
	
	return 0;
}
