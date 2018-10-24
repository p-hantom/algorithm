#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
//#define LOCAL
using namespace std;

struct Node{
	Node *next,*rear;
	string val;
	Node(string v):val(v),next(NULL),rear(NULL){
	}
};

struct DblLinkList{
	Node *first,*cur,*last;
	DblLinkList(){  //��ͷ��� 
		first=new Node("");
		cur=first;
		last=first;
	}
	void getElem(int idx,string &desStr){
		Node *p=first;
		for(int i=0;i<idx;i++){
			p=p->next;
		}
		desStr=p->val;
	}
	bool empty(){
		if(last==first) return true;
		return false;
	}
	void appendNode(string str){
		Node *temp=new Node(str);
		temp->next=last->next;		
		temp->rear=last;
		last->next=temp;
		last=temp;
	}
	void print(){
		Node *p=first->next;
		while(p!=NULL){
			cout<<p->val<<endl;
			p=p->next;			
		}
	}
	int length(){
		int len=0;
		Node *p=first->next;
		while(p!=NULL){
			len++;
			p=p->next;
		}
		return len;
	}
	void setVal(int idx,string str){//idx starts from 0
		Node *p=first;
		for(int i=0;i<idx;i++){
			p=p->next;
		}
		p->val=str;
	}
	void deleteLine(int idx){
		Node *p=first,*q;
		for(int i=0;i<idx;i++){
			p=p->next;
		}
		q=p->rear;
		q->next=p->next;
		if(p->next!=NULL){
			p->next->rear=q;
		}		
	}
};

int idxOfStr(string &src,string &partStr){
	int i=0,len=src.length();
	while(i<len){
		int j=0,temp=i;
		while(src[i]==partStr[j]){			
			if(j==partStr.length()-1){
				return temp;
			}
			i++;j++;
		}
		i++;
	}
	return -1;
}

class LineEditor{
	private:
		DblLinkList textBuffer;
		DblLinkList textUndoBuffer;
		ifstream inFile;
		ofstream outFile;
		int curLineIdx;  //the index of the first line is 1 not 0
		int curUndoLineIdx;
		
	public:
		LineEditor(char infName[],char outfName[]){
			curLineIdx=0;
			inFile.open(infName);
			while(!inFile.eof()){
				string temp;
				inFile>>temp;
				curLineIdx++;
				textBuffer.appendNode(temp);
			}
		}
		void Run();
		void changeLine();
		void findStr();
		bool gotoLine();
		~LineEditor(){
			inFile.close();
		}
};

bool LineEditor::gotoLine(){
	int des;
	cout<<"������Ҫת������: ";
	cin>>des;
	if(des>textBuffer.length()){
		return false;
	}
	curLineIdx=des;
	return true;
}

void LineEditor::findStr(){ 
	char ans;
	bool initialResponse=true;
	
	do{
		if(initialResponse){
			cout<<"�ӵ�һ�п�ʼf(irst)��ӵ�ǰ��c(urrent)��ʼ: ";
		}
		else{
			cout<<"��f��c�ش�: "; 
		}
		ans=getchar();
		while(cin.get()!='\n');
		ans=tolower(ans);
		initialResponse=false;
	} while(ans!='c'&&ans!='f');
	
	cout<<"���뱻���ҵ��ı���: ";
	string strToBeFind;
	cin>>strToBeFind;
	bool isFound=false;
	
	for(int i=1;i<=textBuffer.length();i++){
		if(ans=='c'&&i<curLineIdx){
			continue;
		}
		string strRow;
		textBuffer.getElem(i,strRow);
		int index=idxOfStr(strRow,strToBeFind);//index starts from 0
		if(index!=-1){
			cout<<strRow<<endl;
			for(int j=0;j<index;j++){
				cout<<" ";
			}
			for(int j=0;i<strToBeFind.length();j++){
				cout<<"^";
			}
			cout<<endl;
			curLineIdx=i;
			cout<<curLineIdx<<endl;
			isFound=true;
			break;
		}		
	}
	
	if(!isFound){
		cout<<"���Ҵ�ʧ��"<<endl;
	}
	
}

void LineEditor::changeLine(){
	char ans;
	bool initialResponse=true;
	
	do{
		if(initialResponse){
			cout<<"�滻��ǰ��c(urrent)���滻������a(ll): ";
		}
		else{
			cout<<"��c��a�ش�: "; 
		}
		ans=getchar();
		while(cin.get()!='\n');
		ans=tolower(ans);
		initialResponse=false;
	} while(ans!='c'&&ans!='a');
	
	cout<<"����Ҫ���滻��ָ���ı���: ";
	string strOld;
	cin>>strOld;
	cout<<"�������ı���: ";
	string strNew;
	cin>>strNew;
		
	for(int i=1;i<=textBuffer.length();i++){
		if(ans=='c'&&i!=curLineIdx){
			continue;
		}
		string strRow;
		textBuffer.getElem(i,strRow);
		int index=idxOfStr(strRow,strOld);
		//index starts from 0
		if(index!=-1){  
			string newLine=strRow;
			newLine.replace(index,strOld.length(),strNew);
			textBuffer.setVal(i,newLine);			
		}
	} 
	textBuffer.print();
}

void LineEditor::Run(){
	char userCommand;
	
	do{
		string curLine;
		
		if(curLineIdx!=0){
			textBuffer.getElem(curLineIdx,curLine);
			cout<<curLineIdx<<":"<<curLine.c_str()<<endl<<"?";
		}
		else{
			cout<<"�ļ������"<<endl<<"?";
		}
		
		userCommand=getchar();
		userCommand=tolower(userCommand);
		while(cin.get()!='\n');
		
		if(userCommand!='u'&&userCommand!='h'&&userCommand!='?'&&userCommand!='v'){
			//�洢������Ϣ 
			textUndoBuffer=textBuffer;
			curUndoLineIdx=curLineIdx;
		}
		
		switch(userCommand){
			case 'b': //begin
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					curLineIdx=1;
				}
				break;
			case 'c':  //change
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					changeLine();
				}
				break;
			case 'd': //delete the current line
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					textBuffer.deleteLine(curLineIdx);
					textBuffer.print();
				}
				break;
			case 'e': //to the end
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					curLineIdx=textBuffer.length();
				}
				break;
			case 'f': //find
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					findStr();
				}
				break;
			case 'g': //go to line
				if(gotoLine()==false){
					cout<<"ת��ָ����ʧ��"<<endl;
				}
				break;
		}
		
	}while(userCommand!='q');
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	char infName[]="input.txt",outfName[]="";
	LineEditor ed(infName,outfName);
	ed.Run();
	//string a="abcd",b="cd";
	//cout<<idxOfStr(a,b);
	
	return 0;
}
