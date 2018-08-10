#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mul[3]={2,3,5};

int main(){
	set<LL> s;
	s.insert(1);
	for(int i=1; ;i++){
		LL x=*s.begin();
		s.erase(s.begin());
		if(i==1500){
			cout<<x<<endl;
			break;
		}
		for(int j=0;j<3;j++){
			LL x1=x*mul[j];
			s.insert(x1);
		}
	}
	
	return 0;
}
