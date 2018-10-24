#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#define LOCAL
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){
	}
};

ListNode *reverseKGroup(ListNode *head, int k){
	 
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	ListNode *head=new ListNode(0) , *p=head;
	int k=2;
	for(int i=0;i<5;i++){
		int x;
		cin>>x;
		p->next=new ListNode(x);
		p=p->next;
	}
//	p=head->next;
//	for(int i=0;i<5;i++){
//		cout<<p->val<<endl;
//		p=p->next;
//	}
	
	
	
	return 0;
}
