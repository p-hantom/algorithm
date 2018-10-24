#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	int d,I;
	int tree[100000];
	while(scanf("%d%d",&d,&I)==2){
		memset(tree,0,sizeof(tree));
		int k,max=1<<d-1;
		for(int i=0;i<I;i++){
			k=1;
			while(k<(1<<d)){
				tree[k]=!tree[k];
				if(tree[k]==1){
					k=k*2;
				}
				else{
					k=k*2+1;
				}
			}
		}
		cout<<k/2<<endl;
	}
	
	return 0;
}
