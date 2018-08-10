#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	int t_group;
	cin>>t_group;
	map<int,int> team;
	for(int i=0;i<t_group;i++){
		int n,x;
		cin>>n;
		for(int j=0;j<n;j++){
			cin>>x;
			team[x]=i;
		}
	}
	
	string ins;
	queue<int> q_group,q[1000];//1000 groups at most
	while(cin>>ins){
		if(ins[0]=='S'){
			break;
		}
		else if(ins[0]=='E'){
			int x;
			cin>>x;
			int g=team[x];
			if(q[g].empty()){
				q_group.push(g);
			}
			q[g].push(x);
		}
		else if(ins[0]=='D'){
			int t=q_group.front();
			cout<<q[t].front();
			q[t].pop();
			if(q[t].empty()){
				q_group.pop(); 
			}
		}
	}
	
	return 0;
}
