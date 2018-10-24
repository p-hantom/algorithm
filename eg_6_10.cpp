#include <iostream>
#include <cstdio>
#include <cstring>
#define LOCAL
#define maxn 100
using namespace std;

int sum[maxn];

void init(int p){
	int v;
	cin>>v;
	if(v==-1){
		return;
	}
	sum[p]+=v;
	init(p-1);
	init(p+1);
}

int main(){
	#ifdef LOCAL
	freopen("eg_6_10.txt","r",stdin);
	#endif
	memset(sum,0,sizeof(sum));
	init(maxn/2);
	int i=0;
	while(sum[i]==0){
		i++;
	}
	while(sum[i]!=0){
		cout<<sum[i]<<endl;
		i++;
	}
	
	return 0;
}
