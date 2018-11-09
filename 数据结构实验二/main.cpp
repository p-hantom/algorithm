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
	DblLinkList(){  //有头结点 
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
		if(p->next!=NULL){ //删去的是中间的 
			p->next->rear=q;
		}				
		else{ //删去的是last
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
	cout<<"有效命令: b(egin) c(hange) d(el) e(nd)"<<endl
	    <<"f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)"<<endl
	    <<"q(uit) r(ead) u(ndo) v(iew) w(rite)"<<endl;
}

void LineEditor::view(){
	textBuffer.print();
}

void LineEditor::insert(){ //行号范围 1,2,..,textlen+1
	int ans;
	string str;
	bool initialResponse=true;
	
	do{
		if(initialResponse){
			cout<<"所要插入的单个新行的行号: ";
		}
		else{
			cout<<"输入有效行号: ";
		}
		cin>>ans;	
		while(cin.get()!='\n');
		initialResponse=false;	
	} while(ans>textBuffer.length()+1||ans<=0);
	cout<<"所要插入的新行的内容: ";
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
	cout<<"输入需要转到的行: ";
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
			cout<<"从第一行开始f(irst)或从当前行c(urrent)开始: ";
		}
		else{
			cout<<"用f或c回答: "; 
		}
		ans=getchar();
		while(cin.get()!='\n');
		ans=tolower(ans);
		initialResponse=false;
	} while(ans!='c'&&ans!='f');
	
	cout<<"输入被查找的文本串: ";
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
		cout<<"查找串失败"<<endl;
	}
	
}

void LineEditor::changeLine(){
	char ans;
	bool initialResponse=true;
	
	do{
		if(initialResponse){
			cout<<"替换当前行c(urrent)或替换所有行a(ll): ";
		}
		else{
			cout<<"用c或a回答: "; 
		}
		ans=getchar();
		while(cin.get()!='\n');
		ans=tolower(ans);
		initialResponse=false;
	} while(ans!='c'&&ans!='a');
	
	cout<<"输入要被替换的指定文本串: ";
	string strOld;
	cin>>strOld;
	cout<<"输入新文本串: ";
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
		cout<<"未找到指定串"<<endl;
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
			cout<<"文件缓存空"<<endl<<"?";
		}
		
		userCommand=getchar();
		userCommand=tolower(userCommand);
		while(cin.get()!='\n'); 
		
		if(userCommand!='u'&&userCommand!='h'&&userCommand!='?'&&userCommand!='v'){
			//存储撤销信息 
			duplicate(textUndoBuffer,textBuffer);
			curUndoLineIdx=curLineIdx;
			
		}
		
		switch(userCommand){
			case 'b': //begin
				if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
				}
				else{
					curLineIdx=1;
				}
				break;
			case 'c':  //change
				if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
				}
				else{
					changeLine();
				}
				break;
			case 'd': //delete the current line
				if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
				}
				else{
					deleteLine();					
				}
				break;
			case 'e': //to the end
				if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
				}
				else{
					curLineIdx=textBuffer.length();
				}
				break;
			case 'n': //to next line
			    if(curLineIdx==textBuffer.length()){
			    	cout<<"转到指定行失败"<<endl;
			    }
			    else{
			    	curLineIdx+=1;
			    }
			    break;
			case 'p': //to prior line
			    if(curLineIdx==1||textBuffer.empty()){
			    	cout<<"转到指定行失败"<<endl;
			    }
			    else{
			    	curLineIdx-=1;
			    }
			    break;
			case 'f': //find
				if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
				}
				else{
					findStr();
				}
				break;
			case 'g': //go to line
				if(gotoLine()==false){
					cout<<"转到指定行失败"<<endl;
				}
				break;
			case 'i': //insert new line
				insert();
				break;
			case 'v': //view all the text
			    if(textBuffer.empty()){
					cout<<"警告：文本缓存空"<<endl;
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
					cout<<"警告：文本缓存空"<<endl;
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
				cout<<"输入h或?获得帮助或输入有效命令"<<endl;
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
