#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include <map>
#define LOCAL
using namespace std;

struct Node{
	Node *left,*right;
	int weight;//权值
	char ch;//字符
	string code;//字符编码 
	Node(int w=0,char c=' ',Node *l=NULL,Node *r=NULL):weight(w),ch(c),left(l),right(r){
	}
};

struct CmpNode{
	bool operator () (const Node *p1,const Node *p2) {  
		return p1->weight > p2->weight;
	}
};

class HfmTree{
	Node *root;
	priority_queue<Node*,vector<Node*>,CmpNode> pq;
	map<char,int> weightMap;
	public:
		void generateWeight(string &s);
		void createTree();
		void encode();
};

void HfmTree::encode(Node *node){//左分支标0，右分支标1 
	if(node==NULL){
		return;
	}
	while()
}

void HfmTree::createTree(){
	while(pq.size()!=1){
		Node *t1,*t2;
		t1=pq.top();
		pq.pop();
		t2=pq.top();
		pq.pop();
		Node *t=new Node(t1->weight+t2->weight);
		t->left=t1;
		t->right=t2;
		pq.push(t);
	}
	root=pq.top();
}

void HfmTree::generateWeight(string &s){
	
	for(int i=0;i<s.length();i++){
		if(weightMap.find(s[i])==weightMap.end()){
			weightMap.insert(pair<char,int>(s[i],1));
		}
		else{
			weightMap[s[i]]++;
		}
	}
	
	for(map<char,int>::const_iterator it=weightMap.begin();it!=weightMap.end();it++){
		int wt=it->second;
		Node *p=new Node(wt);
		p->ch=it->first;
		//cout<<it->first<<" "<<p->weight<<" ";
		pq.push(p);
	}
	//cout<<endl;	
	createTree();
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	string s;
	cin>>s;
	HfmTree ht;
	
	ht.generateWeight(s);
	ht.encode();
//	priority_queue<Node*,vector<Node*>,CmpNode> pq;
//	Node *a1=new Node(1);
//	Node *a2=new Node(-9);
//		Node *a3=new Node(7);
//	Node *a4=new Node(3);
//	pq.push(a1);
//	pq.push(a2);
//	pq.push(a3);
//	pq.push(a4);
//	for(int i=0;i<4;i++){
//		cout<<pq.top()->weight<<" ";
//		pq.pop();
//	}
	

	
	return 0;
}
