#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#define LOCAL
using namespace std;

struct ListNode{
	int data;
	ListNode* next;
	ListNode(int x=0){
		data=x;
		next=NULL;
	}
	ListNode* nextNode(){
		return next;
	}
	void insertAfter(ListNode* p){
		p->next=next;
		next=p;
	}
	ListNode* removeAfter(){
		ListNode* p=next;
		if(next==NULL){
			return NULL;
		}
		next=p->next;
		return p;
	}
};

struct List{//有头结点的 
	ListNode *first,*last;

	List(){
		first=new ListNode();
		last=new ListNode();
		first->next=last;
	}
	bool insert(int x,int i){//在链表第 i 个结点处插入新元素 x
		ListNode *p=first;
		
		for(int k=0;k<i-1;k++){
			p=p->next;
			if(p==NULL){
				return false;
			}
		}
		ListNode *q=new ListNode(x);
		q->next=p->next;
		p->next=q;
	}
	~List(){
		makeEmpty();
		delete first;
		first=last=NULL;
	}
	void makeEmpty(){
		ListNode* p;
		p=first;
		while(p->next!=NULL){
			ListNode* q=p->next;
			delete p;
			p=q;
		}
	}
};

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	
	
	return 0;
}
