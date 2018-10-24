#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#define LOCAL
using namespace std; 

struct Node{
	int v;
	bool have_v;
	Node *left,*right;
	Node():have_v(false),left(NULL),right(NULL){
	}
};


Node* newnode(){
	return new Node();
}

void addnode(int t,char* s,Node *root){
	int len=strlen(s)-1;
//	if(len==0){
//		root->have_v=true;
//		root->v=t;
//	}
	Node *u=root;
	for(int i=0;i<len;i++){
		if(s[i]=='L'){
			if(u->left==NULL){
				u->left=newnode();
			}
			u=u->left;
			//root->have_v=true;
		}
		if(s[i]=='R'){
			if(u->right==NULL){
				u->right=newnode();
			}
			u=u->right;
			//root->have_v=true;
		}
	}
	if(u->have_v){
		cout<<"error"<<endl;
		return;
	}
	u->v=t;
	u->have_v=true;
}

bool bfs(vector<int> &ans, Node *root){
	ans.clear();
	queue<Node*> q; 
	q.push(root);
	while(!q.empty()){
		Node* u=q.front();
		q.pop();
		if(!u->have_v){
			cout<<"error"<<endl;
			return false;
		}
		ans.push_back(u->v);
		if(u->left!=NULL){
			q.push(u->left);
		}
		if(u->right!=NULL){
			q.push(u->right);
		}
	}
	return true;
}

void remove_tree(Node *u){
	if(u==NULL){
		return;
	}
	remove_tree(u->left);
	remove_tree(u->right);
	delete u;
}

int main(){
	#ifdef LOCAL
		freopen("eg_6_7.txt","r",stdin);
		//freopen("eg_6_7.out","w",stdout);
	#endif
	Node *root;
	char s[500];
	root=newnode();
	
	while(1){
		scanf("%s",s);
		if(strcmp(s,"()")==0){
			break;
		}
		int t;
		sscanf(&s[1],"%d",&t);
		//printf("value=%d ",t);
		addnode(t,strchr(s,',')+1,root);
	}
	vector<int> ans;
	if(bfs(ans,root)){
		for(int i=0;i<ans.size();i++){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
	
	remove_tree(root);
	
	return 0;
}
