// �q��G �L�οo 10520128 
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib> 
using namespace std;

string fileName = "-1", fileNum;
ifstream fin;
bool set = false; // �O�_Ū�Ҧ��\
 
struct Data{
	int num;
	string numofschool;
	string numofdepartment;
	string school;
	string department;
	string day;
	string level;
	int student;
	int teacher;
	int graduate;
	string city;
	string normal;
};

vector <Data> datavec;
vector <Data> matchvec;



void Print(){ // �L�ŦX�ϥΪ̿�J���󪺩Ҧ���� 
	cout << "*** There are " << matchvec.size() << " matched records, listed as below:" << endl;
	for( int i = 0; i < matchvec.size() ;i++ ) {
		cout << "[" << i+1 << "]" << matchvec[i].school;
		cout << matchvec[i].department << ',';
		cout << matchvec[i].day << ',';
		cout << matchvec[i].level << ',';
		cout << matchvec[i].graduate << endl;
	}
}

void ReadFileAndBuildDatavec(){ // Ū�� �ëإߩҦ�Ū�J��ƪ�vector ��Ʈw 
	Data cur;
	bool deletebool = false; // ���~�ͤH�ƬO�_�ʶ� 
	char cstr[255];
	string str = "0", cut = "0";
	int pre = 0, post = 0, count = 1;
	char c;
	fin.open( fileName.c_str() );
	if( !fin ) cout << "### " << fileName << " does not exist! ###"<< endl;
	else{
		set = true;
		while( str != "��t�O" ) fin >> str;
		fin >> c; 
		while( fin.getline( cstr ,255 , '\n') ) {
			str.assign(cstr);
			deletebool = false;
			while( pre < 255 && count < 12 ){
				post = str.find_first_of( '\t', pre); // ��X'\t'�Ҧb��index 
				cut = str.substr(pre,post-pre); // �qindex pre�}�l��post-pre�Ӧr��assign ��string cut
				if( count == 1)cur.numofschool = cut;
				if( count == 2)cur.school = cut;
				if( count == 3)cur.numofdepartment = cut;
				if( count == 4)cur.department = cut;
				if( count == 5)cur.day = cut;
				if( count == 6)cur.level = cut;
				if( count == 7)cur.student = atoi( cut.c_str() ); // atoi �� char *c �� int ; str.c_str() �� string �� char *c 
				if( count == 8)cur.teacher = atoi( cut.c_str() ); 
				if( count == 9){
					if( cut != "" )cur.graduate = atoi( cut.c_str() ); 
					else deletebool = true;
				} 
				
				if( count == 10)cur.city = cut;
				if( count == 11)cur.normal = cut;
				count++;
				pre  = post+1;
			}
		
			count = 1;
			strcpy( cstr, "\0");
			if(!deletebool)datavec.push_back( cur ) ; // �p�G���~�ͤH�ƨS���ʶ� �N��J���VEECTOR�� 
		}
	}
}

bool Include(string str1, string str2){ // str1 �O�_�t��Str2 
	if( strstr( str1.c_str() , str2.c_str() ) != NULL)return true; // strstr( char* a, char* b) a �����L�]�tb  ���t��NULL 
	else return false;
}

void Search(string key,string keytype){ // match vetor��Ƥ��O�_���t�ϥΪ̿�J�����
										//�]�t���ܴN���β���, �Ϥ��h���� 

	for( int i = 0; i < matchvec.size(); ){
		
		if( key == "*" ) break;
		
		if( keytype == "�ǮզW��") { // �ϥΪ̷j�䪺���O 
			if( !Include(matchvec[i].school,key) || key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++; // ����ƨϥΪ̭n�o �A���β��� ���U�@�Ӹ�Ƥ���ݬ� 
		}
		
		if( keytype == "��t�W��") {
			if( !Include(matchvec[i].department,key) || key == "") matchvec.erase(matchvec.begin()+i);
			else i++;
		}
		
		if( keytype == "��]�O") {
			if( !Include(matchvec[i].day,key)|| key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++;
		}
		
		if( keytype == "���ŧO") {
			if( !Include(matchvec[i].level,key)|| key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++;
		}
	}
}

class MaxHeap{
	
	vector<Data> maxheap;
	public:
		
	int Two( int n){ // return 2��N���� 
		int sum = 1 ;
		for(; n > 0 ; n--)sum = 2*sum;
		return sum;
	}
	
	int LeftBottomIndex(){ // return leftbottom ��index 
		 int level = 1;
		for(; maxheap.size() > Two( level)-1 ;level++);
		return Two(level-1)-1;
	}



	void Print(){ // �L�X root bottom leftbottom ���s�X�θ�� 
		if(maxheap.empty()) cout << "### There is noting matched ###" << endl;
		else{
			cout << "<max heap>" << endl;
			cout << "root: " << '[' << maxheap.front().num << ']'<< ' ' << maxheap.front().graduate << endl;
			cout << "bottom: " << '[' << maxheap.back().num << ']' << ' ' << maxheap.back().graduate << endl;
			cout << "Leftmost bottom: " << '[' << maxheap[LeftBottomIndex()].num << ']' << ' ' << maxheap[LeftBottomIndex()].graduate << endl;
		}
	
	}



	void Numbering(){ // �N���Ȥ@ �ŦX�������W�y���s�X 
		if( !matchvec.empty())for( int num = 1; num <= matchvec.size() ; num++ ) matchvec[num-1].num = num;
	}

	void SwapMaxHeap(int index, int parent){ // ���l���(��m)�洫 
		Data temp;
		temp = maxheap[index];
		maxheap[index] = maxheap[parent];
		maxheap[parent] = temp;
	}

	void ReHeapUp( int index ){ // �վ��ƨ�ŦXMAXheap 
		if( maxheap[index].graduate <= maxheap[(index-1)/2].graduate); // ��Ƥ����p�Τ@�� ���δ��A�_���洫 
		else{
			SwapMaxHeap(index,(index-1)/2);
			if( (index-1)/2 != 0 )ReHeapUp( (index-1)/2 );
		}
	}

	void Build(){ // �إ�MAXHEAP 
		Numbering(); // �N���Ȥ@ �ŦX�������W�y���s�X 
		while(!matchvec.empty()){
			maxheap.push_back(matchvec.front()); // ���ƨ�bottom 
			matchvec.erase(matchvec.begin());// �R����vec����� 
			if( maxheap.size() != 1 )ReHeapUp(maxheap.size()-1); // �վ��ƨ�ŦXMAXheap�Cmaxheap.size()-1�����J��ƪ�vindex 
		}
		
	}

};




int main(){
	
	// �}�� Ū�� �ظ�Ʈw(vector) 
	while( fileName != "0" && !set ){
		cout << "Input the file number: 101, 102, ..... [0]Quit" << endl;
		getline(cin,fileNum);
		fileName = "input" + fileNum + ".txt";
		ReadFileAndBuildDatavec();
	}
		
	while( fileNum != "0"){
		

		matchvec.clear();
		matchvec = datavec; // �ƻs���vec��ŦX���  ���]�٨S���� �Ҧ���Ƴ��O�ŦX�� 
		
		cout << "**********************************************************" << endl;
		cout << "***Mission One: Select Matched Records from a Text File***" << endl;
		cout << "**********************************************************" << endl;
		
		string key;
	
		cout << "Enter a keyword of �ǮզW��: [*]for all" << endl;
		getline(cin,key); //��J�ϥΪ̭n������ 
		Search( key, "�ǮզW��");
		cout << endl;
	
		cout << "Enter a keyword of ��t�W��: [*]for all" << endl;
		getline(cin,key);//��J�ϥΪ̭n������ 
		Search( key, "��t�W��");
		cout << endl;
		
		cout << "Enter a keyword of ��]�O: [*]for all" << endl;
		getline(cin,key);//��J�ϥΪ̭n������ 
		Search( key, "��]�O");
		cout << endl;
		
		cout << "Enter a keyword of ���ŧO: [*]for all" << endl; 
		getline(cin,key);//��J�ϥΪ̭n������ 
		Search( key, "���ŧO");
		cout << endl;
		
		Print(); // �L�X�Ҧ��ŦX����� 
		cout << "**********************************************************" << endl;
		system("pause");
		
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@ Mission Two: Build a Max Heap from the Selected Data @@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
		MaxHeap * maxheap = new MaxHeap();
		maxheap -> Build(); // �إ�max heap 
		maxheap -> Print(); // �LHEAP��root bottom leftbottom 
		cout << "[0]Quit or [Any other]continue?" << endl;
		getline(cin,fileNum);
	}
	
	fin.close();
	return 0;
}
