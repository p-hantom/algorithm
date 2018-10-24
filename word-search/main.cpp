#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#define LOCAL
using namespace std;

int book[100][100];
int idx=0;

bool searchAja(vector<vector<char> > &board, string &word,int x,int y){
	//cout<<"("<<x<<","<<y<<")"<<endl;
	book[x][y]=1;
	if(idx==word.length()){
		return true;
	}
	char ch=word[idx];
	int x1=x,y1=y;
	if(x-1>=0&&board[x-1][y]==ch&&book[x-1][y]==0){
		idx++;
		if(searchAja(board,word,x-1,y)){
			return true;
		}
		else{
			idx--;
		}
	}
	if(x+1<=board.size()-1&&board[x+1][y]==ch&&book[x+1][y]==0){
		idx++;
		if(searchAja(board,word,x+1,y)){
			return true;
		}
		else{
			idx--;
		}
	}
	if(y+1<=board[0].size()-1&&board[x][y+1]==ch&&book[x][y+1]==0){
		idx++;
		if(searchAja(board,word,x,y+1)){
			return true;
		}
		else{
			idx--;
		}
	}
	if(y-1>=0&&board[x][y-1]==ch&&book[x][y-1]==0){
		idx++;
		if(searchAja(board,word,x,y-1)){
			return true;
		}
		else{
			idx--;
		}
	}
	book[x][y]=0;
	
	return false;
}

bool exist(vector<vector<char> > &board, string word){	
	idx=0;
	int r=board.size(),c=board[0].size();
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(board[i][j]==word[idx]){
				idx++;
				memset(book,0,sizeof(book));
				if(searchAja(board,word,i,j)){
					return true;
				}
				idx--;
			}
		}
	}
	return false;
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	vector<vector<char> > board;
	string word;
	int r=3,c=4;
	for(int i=0;i<r;i++){
		vector<char> temp;
		for(int j=0;j<c;j++){
			char ch;
			cin>>ch;
			temp.push_back(ch);
		}
		board.push_back(temp);
	}
	
	while(cin>>word){
		if(exist(board,word)){
			cout<<"yes"<<endl;
		}
		else{
			cout<<"no"<<endl;
		}
		
	}
	
	
	return 0;
}
