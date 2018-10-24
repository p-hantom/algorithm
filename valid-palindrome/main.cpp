#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstring>
#include <cctype>
#define LOCAL
using namespace std;

bool isPalindrome(string s){
	bool isP=true;
	int i=0,j=s.length()-1;
	while(i<=j){		
		//if(!isalpha(s[i])||!isalpha(s[j])){
		if(!isalpha(s[i])&&!isdigit(s[i])){
			i++;continue;
		}
		if(!isalpha(s[j])&&!isdigit(s[j])){
			j--;continue;
		}
			
		//}
		if(isalpha(s[i])){
			s[i]=tolower(s[i]);
		}
		if(isalpha(s[j])){
			s[j]=tolower(s[j]);
		}
		if(s[i]!=s[j]){
			isP=false;
			break;
		}
		i++;j--;
		
	}
	
	return isP;
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	string s,temp;
	while(cin>>temp){
		s.append(temp);
	}
	if(isPalindrome(s)){
		cout<<"yes"<<endl;
	}
	else{
		cout<<"no"<<endl;
	}
	
	return 0;
}
