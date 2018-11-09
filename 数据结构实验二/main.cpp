#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct Node{
	Node *next,*rear;
	string val;
	Node(string v):val(v),next(NULL),rear(NULL){
	}
};

struct DblLinkList{
	Node *first,*last;
	DblLinkList(){  //��ͷ��� 
		first=new Node("");
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
		if(p->next!=NULL){ //ɾȥ�����м�� 
			p->next->rear=q;
		}				
		else{ //ɾȥ����last
			last=q;
		}
		delete p;
	}
	void insert(int idx,string &str);
	void deleteList();
};

void DblLinkList::deleteList(){
	Node *p=last,*q;
	while(p!=first){
		q=p->rear;
		delete p;
		p=q;
	}
	last=first;
	last->next=NULL;
}

void duplicate(DblLinkList &des,DblLinkList &src){
	des.deleteList();
	Node *psrc=src.first->next;
	while(psrc!=NULL){
		des.appendNode(psrc->val);
		psrc=psrc->next;
	}
}

void DblLinkList::insert(int idx,string &str){
	Node *p=first,*temp=new Node(str);
	for(int i=0;i<idx-1;i++){
		p=p->next;
	}
	temp->next=p->next;
	temp->rear=p;
	if(temp->next!=NULL){
		temp->next->rear=temp;		
	}	
	last=temp;
	p->next=temp;
}

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
			outFile.open(outfName);
			readFile();
		}
		void Run();
		void changeLine();
		void findStr();
		bool gotoLine();
		void insert();
		void deleteLine();
		void view();
		void help();
		void writeFile();
		void readFile();
		~LineEditor(){
			inFile.close();
			outFile.close();
			textBuffer.deleteList();
			textUndoBuffer.deleteList();
		}
		
		template<class Type>
		void swap(Type &a,Type &b);
};

void LineEditor::readFile(){
	textBuffer.deleteList();
	bool hasContent=false;
	while(!inFile.eof()){
		string temp;
		inFile>>temp;
		hasContent=true;				
		textBuffer.appendNode(temp);
	}
	if(hasContent){
		curLineIdx=1;
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);
}

void LineEditor::writeFile(){ //no undo op for this
	for(int i=1;i<=textBuffer.length();i++){
		string str;
		textBuffer.getElem(i,str);
		outFile<<str<<endl;
	}
}

template<class Type>
void  LineEditor::swap(Type &a,Type &b){
	Type temp=a;
	a=b;
	b=temp;
}

void LineEditor::help(){
	cout<<"��Ч����: b(egin) c(hange) d(el) e(nd)"<<endl
	    <<"f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)"<<endl
	    <<"q(uit) r(ead) u(ndo) v(iew) w(rite)"<<endl;
}

void LineEditor::view(){
	textBuffer.print();
}

void LineEditor::insert(){ //�кŷ�Χ 1,2,..,textlen+1
	int ans;
	string str;
	bool initialResponse=true;
	
	do{
		if(initialResponse){
			cout<<"��Ҫ����ĵ������е��к�: ";
		}
		else{
			cout<<"������Ч�к�: ";
		}
		cin>>ans;	
		while(cin.get()!='\n');
		initialResponse=false;	
	} while(ans>textBuffer.length()+1||ans<=0);
	cout<<"��Ҫ��������е�����: ";
	cin>>str;
	while(cin.get()!='\n');
	curLineIdx=ans;
	
	textBuffer.insert(ans,str);
} 

void LineEditor::deleteLine(){	
    int len=textBuffer.length();
    textBuffer.deleteLine(curLineIdx);
	if(curLineIdx==len){
		curLineIdx--;
	}
	
	textBuffer.print();
}

bool LineEditor::gotoLine(){
	int des;
	cout<<"������Ҫת������: ";
	cin>>des;
	while(cin.get()!='\n');
	if(des>textBuffer.length()||des<=0){
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
	while(cin.get()!='\n');
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
			for(int j=0;j<strToBeFind.length();j++){
				cout<<"^";
			}
			cout<<endl;
			curLineIdx=i;
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
	while(cin.get()!='\n'); 
	bool success=false;
		
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
			success=true;		
		}
	} 
	if(success){
		textBuffer.print();
	}
	else{
		cout<<"δ�ҵ�ָ����"<<endl;
	}
}

void LineEditor::Run(){
	char userCommand;
	bool toExit=false;
	
	do{
		string curLine;
		
		cout<<"--------------"<<endl;
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
			duplicate(textUndoBuffer,textBuffer);
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
					deleteLine();					
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
			case 'n': //to next line
			    if(curLineIdx==textBuffer.length()){
			    	cout<<"ת��ָ����ʧ��"<<endl;
			    }
			    else{
			    	curLineIdx+=1;
			    }
			    break;
			case 'p': //to prior line
			    if(curLineIdx==1||textBuffer.empty()){
			    	cout<<"ת��ָ����ʧ��"<<endl;
			    }
			    else{
			    	curLineIdx-=1;
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
			case 'i': //insert new line
				insert();
				break;
			case 'v': //view all the text
			    if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					view();
				}
				break;
			case '?': //help
			case 'h': 
			    help();break;
			case 'u':	
			    swap(textBuffer,textUndoBuffer);
				swap(curLineIdx,curUndoLineIdx);
				break;
			case 'w':
				if(textBuffer.empty()){
					cout<<"���棺�ı������"<<endl;
				}
				else{
					writeFile();
				}
				break;
			case 'r':
				readFile();
				break; 
			case 'q':
				toExit=true;
				break;
			default:
				cout<<"����h��?��ð�����������Ч����"<<endl;
		}
		
	}while(toExit==false);
}

int main(){
	#ifdef LOCAL
	freopen("input.txt","r",stdin);
	#endif
	
	char infName[]="input.txt",outfName[]="out.txt";
	LineEditor ed(infName,outfName);
	ed.Run();
	
	return 0;
}
