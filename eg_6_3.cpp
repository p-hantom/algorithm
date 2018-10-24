#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Matrix{
	int a,b;
	Matrix(int a1=0,int b1=0):a(a1),b(b1){
	}
}m[26];

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		char ap;
		cin>>ap;
		int k=ap-'A';
		cin>>m[k].a>>m[k].b;
	}
	
	string s;
	stack<Matrix> ss;
	while(cin>>s){
		int res=0,error=0;
		int len=s.length();
		for(int i=0;i<len;i++){
			if(isalpha(s[i])){
				ss.push(m[s[i]-'A']);
			}
			else if(s[i]==')'){
				Matrix m1,m2=ss.top();
				ss.pop();
				m1=ss.top();
				ss.pop();
				if(m1.b!=m2.a){
					cout<<"error"<<endl;
					error=1;
					break;
				}
				res+=m1.a*m1.b*m2.b;
				Matrix nm(m1.a,m2.b);
				ss.push(nm);
			}
		}
		if(!error){
			cout<<res<<endl;
		}
	}
	
	return 0;
}
