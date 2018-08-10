#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <sstream>
using namespace std;

set<string> dict;

int main(){
	string s,buff;
	while(cin>>s){
//		cout<<s<<endl;
		for(int i=0;i<s.length();i++){
			if(isalpha(s[i])){
				s[i]=tolower(s[i]);
			}
			else{
				s[i]=' ';
			}
		}
		stringstream ss(s);
		while(ss>>buff){
			dict.insert(buff);
		}
	}
	for(set<string>::iterator it=dict.begin();it!=dict.end();it++){
		cout<<*it<<endl;
	}
	
	return 0;
}
