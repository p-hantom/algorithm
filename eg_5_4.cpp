#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

map<string,int> cnt;
vector<string> words;

string repr(const string &temp){
	string s=temp;
	for(int i=0;i<s.length();i++){
		s[i]=tolower(s[i]);
	}
	sort(s.begin(),s.end());
	return s;
}

int main(){
	string temp;
	while(cin>>temp){
		if(temp=="#"){
			break;
		}
		words.push_back(temp);
		string r=repr(temp);
		if(cnt.count(r)==0){
			cnt[r]=0;
		}
		cnt[r]++;
	}
	vector<string> ans;
	for(int i=0;i<words.size();i++){
		if(cnt[repr(words[i])]==1){
			ans.push_back(words[i]);
		}
	}
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<endl;
	}
	
	return 0;
} 
