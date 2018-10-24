#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define maxn 100
#define LOCAL
using namespace std;

char a[maxn][maxn];
int m,n,book[maxn][maxn];

void dfs(int x,int y,int cnt){
	if(x<0||x>=m||y<0||y>=n||a[x][y]!='@'||book[x][y]>0){
		return;
	}
	book[x][y]=cnt;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0&&j==0){
				continue;
			}
			dfs(x+i,y+j,cnt);
		}
	}
}

struct Node{
	int x,y;
	int cnt;
	Node(int x1,int y1,int cnt1):x(x1),y(y1),cnt(cnt1){
	}
};

void bfs(int x,int y,int cnt){
	queue<Node> q;
	Node t(x,y,cnt);
	q.push(t);
	while(!q.empty()){
		t=q.front();
		q.pop();
		for(int i=-1;i<=1;i++){
			for(int j=-1;j<=1;j++){
				if(i==0&&j==0){
					continue;
				}
				if(i+t.x<0||i+t.x>=m||j+t.y<0||j+t.y>=n||a[i+t.x][j+t.y]!='@'||book[i+t.x][j+t.y]>0){
					continue;
				}
				book[t.x+i][t.y+j]=cnt;
				Node temp(t.x+i,t.y+j,cnt);
				q.push(temp);
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("eg_6_12.txt","r",stdin);
#endif
	memset(a,'0',sizeof(a));
	memset(book,0,sizeof(book));
	cin>>m>>n;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	
	int cnt=0;
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]=='@'&&book[i][j]==0){
				cnt++;
				//dfs(i,j,cnt);
				bfs(i,j,cnt);
			}
		}
	}	
	cout<<cnt<<endl;
	
	return 0;
}
