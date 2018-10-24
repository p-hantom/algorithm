#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#define LOCAL
using namespace std;

struct Node{
	int val;
	Node* next;
	Node(int v=0,Node* n=NULL):val(v),next(n){
	}
};

struct CirList{
	Node *first,*cur,*last,*pre;
	int length;
	CirList(int val=0){
		first=new Node(val,NULL);
		cur=first;
		last=cur;
		length=1;
	}
	void insert(int val){
		last->next=new Node(val,first);
		last=last->next;
		last->next=first;
		length++;
	}
	void show(){
		Node* p=first;
		while(p!=last){
			cout<<p->val<<" ";
			p=p->next;
		}
		cout<<p->val<<" "<<endl;
	}
	void remove(){//remove the current node
		length--;
		pre->next=cur->next;
		cur=pre->next;
	}
	void Josephus(int n,int m){
		while(length>1){
			for(int i=0;i<m-1;i++){
				//cout<<cur->val<<" ";
				pre=cur;
				cur=cur->next;
			}
			//cout<<cur->val<<endl;
			remove();
		}
		cout<<cur->val<<endl;
	} 
}; 



int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	int n,m;
	cin>>n>>m;
	CirList cl(1);
	for(int i=2;i<=n;i++){
		cl.insert(i);
	} 
	cl.Josephus(n,m);
	
	return 0;
}
