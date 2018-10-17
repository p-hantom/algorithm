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

int toInt(char s[],int& i){
	int ans=0;
	while(isdigit(s[i])){
		ans*=10;
		ans+=s[i]-'0';
		i++;
	}
//	cout<<ans<<endl;
	return ans;
}

double toDouble(char s[],int& i){
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
				//cout<<"temp="<<temp*(s[i]-'0')<<endl;
				ans+=temp*(s[i]-'0');
			}
		}
		if(s[i]=='.'){
			isIntPart=0;
		}
		i++;
	}
	//cout<<"ans="<<ans<<endl;
	return ans;
}

int opTwoNums(stack<int>& num,char op){
	int b=num.top();num.pop();
	int a=num.top();num.pop();
	int temp_ans;
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
		temp_ans=a/b;
	}
	else if(op=='%'){
		temp_ans=a%b;
	}
	else if(op=='^'){
		temp_ans=pow(a,b);
	}
	return temp_ans;
}

double opTwoNums1(stack<double>& num,char op){
	double b=num.top();num.pop();
	double a=num.top();num.pop();
	double temp_ans;
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
		temp_ans=a/b;
	}
	else if(op=='%'){
		temp_ans=(int)a%(int)b;
	}
	else if(op=='^'){
		temp_ans=pow((int)a,(int)b);
	}
	return temp_ans;
}

bool opTwoNums2(stack<double>& num,char op,double& temp_ans){
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
		temp_ans=(int)a%(int)b;
	}
	else if(op=='^'){
		temp_ans=pow((int)a,(int)b);
	}
	return true;
}

int solve(char s[]){
	int len=strlen(s);
	int ans=0;
	stack<int> num;
	stack<Op> op;
	int addLevel=0,i=0;
	
	//num.push(0); 
	
	while(i<len||op.size()>0){//还在读入 或 已经读入完成并还在处理 
		if(i<len){
			if(isdigit(s[i])){
				int temp_int=toInt(s,i);
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
			
			else{  //if s[i] is an operator
				//flag=1;
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
						int temp_ans=opTwoNums(num,op_top.getOp());
						num.push(temp_ans);
						//op.push(s_i);
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
			int temp_ans=opTwoNums(num,op.top().getOp());
			op.pop();
			num.push(temp_ans);
		}
		
		if(!num.empty()){
			ans=num.top();
		}
		
	}
	
	return ans;
}

bool solve1(char s[],double& ans){
	int len=strlen(s);
	//double ans=0;
	stack<double> num;
	stack<Op> op;
	int addLevel=0,i=0;
	
	//num.push(0); 
	
	while(i<len||op.size()>0){//还在读入 或 已经读入完成并还在处理 
		if(i<len){
			if(isdigit(s[i])){
				double temp_int=toDouble(s,i);
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
						if(!opTwoNums2(num,op_top.getOp(),temp_ans)){
							
							return false;
						}
						
						num.push(temp_ans);
						//op.push(s_i);
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
			double temp_ans;//=opTwoNums1(num,op.top().getOp());
			if(!opTwoNums2(num,op.top().getOp(),temp_ans)){
				//cout<<"invalid input!"<<endl;
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
		if(solve1(s,ans)){
			cout<<s<<"="<<ans<<endl;
		}
		else{
			cout<<s<<" is an invalid input"<<endl;
		}
	}
	
	
	return 0;
}
