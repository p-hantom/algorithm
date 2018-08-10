#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(){
	int n,q,x;
	int a[100];
	while(scanf("%d%d",&n,&q)==2&&n){
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		sort(a,a+n);
		for(int i=0;i<q;i++){
			cin>>x;
			int p=lower_bound(a,a+n,x)-a;
			if(a[p]==x){
				cout<<x<<" found at "<<p+1<<endl;
			}
			else{
				cout<<"not found"<<endl;
			}
		}
	}
	
	return 0;
}
