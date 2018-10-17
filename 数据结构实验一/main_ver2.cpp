#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <cctype>
#include <cmath>
#define MIN 5
#define LOCAL
using namespace std;

struct Op{
	char name;
	int level;
	Op(char n):name(n){
		if(n=='+'){
			level=1;
		}
		else if(n=='-'){
			level=2;
		}
		else if(n=='*'||n=='/'||n=='%'){
			level=3;
		}
		else if(n=='^'){
			level=4;
		}
	}
	char getOp(){
		return name;
	}
	void opAddLevel(int addLevel){
		this->level+=addLevel;
	}
};

double toDouble1(char s[],int& i){
	double ans=0,temp=1;
	int isIntPart=1;
	while(isdigit(s[i])||s[i]=='.'){
		if(isdigit(s[i])){
			if(isIntPart==1){
				ans*=10;
				ans+=s[i]-'0';				
			}
			else{
				temp/=10;
				ans+=temp*(s[i]-'0');
			}
		}
		if(s[i]=='.'){
			isIntPart=0;
		}
		i++;
	}
	
	return ans;
}

bool toDouble(char s[],int& i,double& ans){
	double temp=1;
	int isIntPart=1,startWithZero=0;
	while(isdigit(s[i])||s[i]=='.'){
		if(isdigit(s[i])){
			if(s[i]=='0'){
				if(startWithZero==0){
					startWithZero=1;
				}
				else if(startWithZero&&isIntPart){
					return false;
				}
			}
			if(isIntPart==1){
				ans*=10;
				ans+=s[i]-'0';				
			}
			else{
				temp/=10;
				ans+=temp*(s[i]-'0');
			}
		}
		else if(s[i]=='.'){
			isIntPart=0;
		}
		i++;
	}
	
	return ans;
}


bool opTwoNums(stack<double>& num,char op,double& temp_ans){
	double b=num.top();num.pop();
	double a=num.top();num.pop();
	if(op=='+'){
		temp_ans=a+b;
	}
	else if(op=='-'){
		temp_ans=a-b;
	}
	else if(op=='*'){
		temp_ans=a*b;
	}
	else if(op=='/'){
		if(b==0){
			return false;
		}
		temp_ans=a/b;
	}
	else if(op=='%'){
		if(b==0){
			return false;
		}
		temp_ans=(int)a%(int)b;
	}
	else if(op=='^'){
		temp_ans=pow((int)a,(int)b);
	}
	return true;
}

bool solve(char s[],double& ans){
	int len=strlen(s);
	stack<double> num;
	stack<Op> op;
	int addLevel=0,i=0;
	
	while(i<len||op.size()>0){//还在读入 或 已经读入完成并还在处理 
		if(i<len){
			if(isdigit(s[i])){
				double temp_int=0;
				if(!toDouble(s,i,temp_int)){
					return false;
				}
				num.push(temp_int);
			}
			else if(s[i]=='('){
				addLevel+=MIN;
				i++;
			}
			else if(s[i]==')'){
				addLevel-=MIN;
				i++;
			}
			else if(isalpha(s[i])||s[i]=='.'){
				return false;
			}
			
			else{  //if s[i] is an operator
				if(s[i]=='-'){
					if(i==0||(i>0&&!isdigit(s[i-1]))){
						num.push(0);
					}
				} 
				Op s_i(s[i]);
				s_i.opAddLevel(addLevel);
				if(!op.empty()){
					Op op_top=op.top();			
					if(op_top.level>=s_i.level){
						op.pop();
						double temp_ans;
						if(!opTwoNums(num,op_top.getOp(),temp_ans)){
							
							return false;
						}						
						num.push(temp_ans);
					}
					else{
						op.push(s_i);i++;
					}
				}				
				else{
					op.push(s_i);i++;
				}				
			}
		}
		
		else{
			double temp_ans;
			if(!opTwoNums(num,op.top().getOp(),temp_ans)){
				return false;
			}
			op.pop();
			num.push(temp_ans);
		}
		
		if(!num.empty()){
			ans=num.top();
		}		
	}
	
	return true;
}


int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	char s[100];
	while(cin>>s){
		double ans=0;
		if(solve(s,ans)){
			cout<<s<<"="<<ans<<endl;
		}
		else{
			cout<<s<<" is an invalid input"<<endl;
		}
	}
		
	return 0;
}
