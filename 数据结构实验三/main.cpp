#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include <cctype>
#include <map>
#define LOCAL
using namespace std;

struct Node{
	Node *left,*right;
	int weight;//权值
	char ch;//字符
	string code;//字符编码 
	bool isLeaf;
	Node(int w=0,char c=' ',Node *l=NULL,Node *r=NULL):weight(w),ch(c),left(l),right(r){
		isLeaf=false;
	}
};

struct CmpNode{
	bool operator () (const Node *p1,const Node *p2) {  
		return p1->weight > p2->weight || (p1->weight==p2->weight && p1->isLeaf);
	}
};

class HfmTree{
	Node *root;
	priority_queue<Node*,vector<Node*>,CmpNode> pq;
	map<char,int> weightMap;
	map<char,string> codeMap;
	public:
		void generateCodes(string &s);
		void createTree();
		void encode(Node *node,string codes);
		void decompress(string src);
		void compress(string src);
};

void HfmTree::compress(string src){
	string des;
	for(int i=0;i<src.length();i++){
		des.append(codeMap.find(src[i])->second);
	}
	cout<<src<<" 编码为 "<<des<<endl;
}

void HfmTree::decompress(string src){
	string des;
	Node *p=root;
	int i=0;
	while(i<src.length()){
		if(src[i]=='0'){
			if(p->left!=NULL){
				p=p->left;
				i++;
			}//else:wrong input	
			else{
				cout<<src<<" is a wrong input!"<<endl;
				return;
			}			
		}			
		else if(src[i]=='1'){
			if(p->right!=NULL){
				p=p->right;
				i++;
			}
			else{
				cout<<src<<" is a wrong input!"<<endl;
				return;
			}
		}
		
		if(p->left==NULL&&p->right==NULL){
			des.push_back(p->ch);
			p=root;
		}
		
	}
	cout<<src<<" 解码后为 "<<des<<endl;
}

void HfmTree::encode(Node *node,string codes){//左分支标0，右分支标1 
	if(node->left==NULL&&node->right==NULL){
		node->code=codes;
		codeMap.insert(pair<char,string>(node->ch,codes));
		cout<<node->ch<<":"<<codes<<endl;
		return;
	}
	if(node->left!=NULL){
		codes.push_back('0');
		encode(node->left,codes);
		codes.erase(codes.length()-1,1);
	}
	if(node->right!=NULL){
		codes.push_back('1');
		encode(node->right,codes);
		codes.erase(codes.length()-1,1);
	}
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

void HfmTree::generateCodes(string &s){	
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
		p->isLeaf=true;
		pq.push(p);
	}	
	createTree();
	encode(root,"");
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	string s;
	cin>>s;
	HfmTree ht;
	ht.generateCodes(s);
	cout<<endl;
	
	string code;
	while(cin>>code){
		if(isdigit(code[0])){
			ht.decompress(code);
			cout<<endl;
		}
		else{
			ht.compress(code);
			cout<<endl;
		}
	}
	
	
	return 0;
}
