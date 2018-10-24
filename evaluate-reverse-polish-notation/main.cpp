#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define LOCAL
using namespace std;

////Êý×Ö×ª×Ö·û´®
//sprintf(str,"%d",num);
////×Ö·û´®×ªÊý×Ö
//sscanf(str,"%d",&rsl);

int evalRPN(vector<string> &tokens) {
	int ans=0;
	stack<int> s;

	int n;	
	n=tokens.size();
	
	for(int i=0;i<n;i++){
		string c=tokens[i];
		//cout<<c<<endl;
		if(c=="+"||c=="-"||c=="*"||c=="/"){
//			string b=s.top();
//			s.pop();
//			string a=s.top();
//			s.pop();
//		
			int ia,ib;//=atoi(a.c_str()),ib=atoi(b.c_str());
//			sscanf(a.c_str(),"%d",&ia);
//			sscanf(b.c_str(),"%d",&ib);
			ib=s.top();
			s.pop();
			ia=s.top();
			s.pop();
			
			if(c=="+"){
				ans=(ia+ib);
				//cout<<"ans="<<ans<<endl; 
			}
			else if(c=="-"){
				ans=(ia-ib);
			}
			else if(c=="*"){
				ans=(ia*ib);
				//cout<<"ans="<<ia<<"*"<<ib<<endl; 
			}
			else if(c=="/"){
				ans=(ia/ib);
				//cout<<"ans="<<ans<<endl; 
			}
//			char buffer[130];
//			string x;//=itoa(ans,buffer,10);
//			sprintf(buffer,"%d",ans);
//			x=buffer;
//			s.push(x);
			s.push(ans);
		}
		else{
			//s.push(c);
			sscanf(c.c_str(),"%d",&ans);
			s.push(ans);
		}
	}
	
    return s.top();
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	vector<string> tokens;//=["2", "1", "+", "3", "*"];
	char temp[100];
//	cin>>temp;
//	tokens.push_back(temp);
//	while(temp){
//		cin>>temp;
//		tokens.push_back(temp);
//	}
	
	while(cin>>temp){
		tokens.push_back(temp);
		//cout<<temp;
	}
	
	int ans=evalRPN(tokens);
	cout<<ans;
	
	return 0;
}
