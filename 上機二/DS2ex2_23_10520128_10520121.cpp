// ��23�� 
// �q��G �L�οo 10520128 
// �q��G ���Y�v 10520121 
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib> 
#include <cmath>
using namespace std;

string fileName = "-1", fileNum ;
string x ;
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


class MinMaxHeap{
	
	vector<Data> maxitems;
	vector<Data> minmaxheap;
	public:
		
	int Two( int n){ // return 2��N���� 
		int sum = 1 ;
		for(; n > 0 ; n--)sum = 2*sum;
		return sum;
	}
	
	int LeftBottomIndex(){ // return leftbottom ��index 
		 int level = 1;
		for(; minmaxheap.size() > Two( level)-1 ;level++);
		return Two(level-1)-1;
	}

	void Print(){ // �L�X  bottom leftbottom ���s�X�θ�� 
		if(minmaxheap.empty()) cout << "### There is noting matched ###" << endl;
		else{
			cout << "bottom: " << '[' << minmaxheap.back().num << ']' << ' ' << minmaxheap.back().graduate << endl;
			cout << "Leftmost bottom: " << '[' << minmaxheap[LeftBottomIndex()].num << ']' << ' ' << minmaxheap[LeftBottomIndex()].graduate << endl;
		}
	}
	
	void PrintMaxItems(){ // �L�X  bottom leftbottom ���s�X�θ�� 
		for( int i = 0; i < maxitems.size() ; i++)	cout << "Top  " << i+1 << ":  [" <<maxitems[i].num << "]"  << maxitems[i].school << maxitems[i].department << ", " <<
			  maxitems[i].day << ", " <<  maxitems[i].level << ", " <<  maxitems[i].graduate << endl; 
	}
	
	int HowBig() {  // �d�ݾ𪺤j�p �A �Ψ��ˬdŪ�JK���ɭԬO�_�W�X�d�� 
	  return minmaxheap.size() ;
	}

	
	
	
	
	/* debug �� 
	void PrintAll(){  
		for( int i = 0; i < minmaxheap.size() ; i++)	cout << "[" << i+1 <<"]"<<minmaxheap[i].num << ", " << minmaxheap[i].school << minmaxheap[i].department << ", " <<
			  minmaxheap[i].day << ", " <<  minmaxheap[i].level << ", " <<  minmaxheap[i].graduate << endl; 
	}
	*/
	 
	void Swap(int index, int index2){ // ���l���(��m)�洫 
		Data temp;
		temp = minmaxheap[index];
		minmaxheap[index] = minmaxheap[index2];
		minmaxheap[index2] = temp;
	}

	int Level( int  index ){ // �p��bMin�h �٬O Max�h min return 0 max return 1 
		return (int)floor( log2(index+1) ) %2;
	}
	
	void ReHeapUp( int index ){ 
		if( index == 0 );
		else if( Level(index) == 0 ) {// min heap
			if( minmaxheap[index].graduate > minmaxheap[(index-1)/2].graduate){  // ����j 
				Swap( index, (index-1)/2);
				ReHeapUp((index-1)/2);
			}
			while( index > 2 && minmaxheap[index].graduate < minmaxheap[(index-3)/4].graduate ){ // �񯪤��j 
					Swap( index, (index-3)/4);
					index = (index-3)/4;
			}
		}
		else{ // maxheap
			if( minmaxheap[index].graduate < minmaxheap[(index-1)/2].graduate ){ // ����p 
				Swap( index, (index-1)/2 );
				ReHeapUp((index-1)/2);	
			} 
			while( index > 2 && minmaxheap[index].graduate > minmaxheap[(index-3)/4].graduate) { // �񯪤��j
					Swap( index, (index-3)/4);			 
					index = (index-3)/4;					
			}
		}

	}
	
	void Numbering(){ // �N���Ȥ@ �ŦX����ƽs�W�y���s�X 
		if( !matchvec.empty())for( int num = 1; num <= matchvec.size() ; num++ ) matchvec[num-1].num = num;
	}
	
	void Build(){      // �إ�minmax heap 
		Numbering();
		while(!matchvec.empty()){
			minmaxheap.push_back(matchvec.front());
			matchvec.erase(matchvec.begin());
			ReHeapUp(minmaxheap.size()-1); 			
		}
	}
	
	int BiggestChild( int index ){   //���o���j�l�𪺦�m 
		if( (index*2)+1 >= minmaxheap.size() ) return -1;
		else if( (index*2)+1 == minmaxheap.size()-1 ) return (index*2)+1;
		else if( (index*2)+2 < minmaxheap.size() && minmaxheap[(index*2)+1].graduate >= minmaxheap[(index*2)+2].graduate ) return (index*2)+1;
		else return (index*2)+2;
	}
	
	int BiggestGrandchild( int index ){
		
		if( (index*4)+3 > minmaxheap.size()-1 ) return -1;
		else if( (index*4)+6 < minmaxheap.size() ) {// �|�]���s�b  

			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate && minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+5].graduate
				&& minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+3;
			
			else if( minmaxheap[(index*4)+4].graduate >= minmaxheap[(index*4)+3].graduate && minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+5].graduate
				&& minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+4;
			
			else if( minmaxheap[(index*4)+5].graduate >= minmaxheap[(index*4)+3].graduate && minmaxheap[(index*4)+5].graduate >=  minmaxheap[(index*4)+4].graduate
				&& minmaxheap[(index*4)+5].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+5;
			
			else return (index*4)+6;
		} 
		else if((index*4)+5 == minmaxheap.size() -1 ) {// �T�] 
			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate && minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+5].graduate) return (index*4)+3;
			
			else if( minmaxheap[(index*4)+4].graduate >= minmaxheap[(index*4)+3].graduate && 
					minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+5].graduate) return (index*4)+4;
			
			else return(index*4)+5;			
		}
		else if((index*4)+5 == minmaxheap.size() -1 ) {// �G�] 
			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate ) return (index*4)+3;		
			else return (index*4)+4;		
		}
		else return (index*4)+3;
	}

	void Delete(int index){ 
		minmaxheap[index] = minmaxheap[minmaxheap.size()-1]; // �Nbottom �ƻs�W�h
		minmaxheap.pop_back(); // �R��bottom 
		if( BiggestChild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestChild(index)].graduate) Swap( index,BiggestChild(index) ); // ��p���ˬd 
		while( BiggestGrandchild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestGrandchild(index)].graduate ) { // ��]�l�ˬd 
			int temp = BiggestGrandchild(index);
			Swap( index,BiggestGrandchild(index) );
			index = temp;
		}
		if( BiggestChild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestChild(index)].graduate) Swap( index,BiggestChild(index) );
			// ��̫᭱���p�Ħb��p���ˬd�@�� 
	}  
	
	void GetMax( int k){   // �����̤j�� 
		if ( k <= 0);
		else if ( minmaxheap.size() > 2) {  
				if( minmaxheap[1].graduate >= minmaxheap[2].graduate) maxitems.push_back(minmaxheap[1]),Delete(1);  //�Y���l����j�A�����l�� 
				else maxitems.push_back(minmaxheap[2]),Delete(2);   //�Ϥ��A���k�l��                                                 
				GetMax(--k);
		}
		else if ( minmaxheap.size() == 2 ){
			maxitems.push_back(minmaxheap[1]),Delete(1);
			GetMax(--k);
		}
		else{
			maxitems.push_back(minmaxheap[0]) ;
			GetMax(--k);
		}
	}
	
	void ClearMaxItems(){
		maxitems.clear();
	}
};


int main(){
	
	bool NumOk = false ;  // �ˬdK�O�_�b�d�� 
	bool IsZero = false ; 

	string readnum ;
	int a = 0 ;
	int k = 0 ;
	
	// �}�� Ū�� �ظ�Ʈw(vector) 
	while( fileName != "0" ){
		cout << "**********************************************************" << endl;
		cout << "***                On-machine Exercise                 ***" << endl;
		cout << "***         Mission 1: construct a min-max heap        ***" << endl;
		cout << "***   Mission 2: Find top-K maximums by min-max heap   ***" << endl;
		cout << "**********************************************************" << endl;

		
		while( !set ){
			datavec.clear();
			cout << "Input the file number: 201, 202, ..... [0]Quit" << endl;
			cin >> fileNum ;
			if ( fileNum =="0"){
				IsZero = true ;
				break ;
				
			}
			fileName = "input" + fileNum + ".txt";
			ReadFileAndBuildDatavec();
		}
		if ( IsZero){
			break ;
		}
		set = false;
		fin.close();
		
		matchvec.clear();
		matchvec = datavec; // �ƻs���vec��ŦX���  ���]�٨S���� �Ҧ���Ƴ��O�ŦX�� 
		

		
		string key;
	
		cout << "Enter a keyword of �ǮզW��: [*]for all" << endl;
		cin >> key ; //��J�ϥΪ̭n������ 
		Search( key, "�ǮզW��");
		cout << endl;
	
		cout << "Enter a keyword of ��t�W��: [*]for all" << endl;
		cin >> key ;//��J�ϥΪ̭n������ 
		Search( key, "��t�W��");
		cout << endl;
		
		cout << "Enter a keyword of ��]�O: [*]for all" << endl;
		cin >> key ;//��J�ϥΪ̭n������ 
		Search( key, "��]�O");
		cout << endl;
		
		cout << "Enter a keyword of ���ŧO: [*]for all" << endl; 
		cin >> key ;//��J�ϥΪ̭n������ 
		Search( key, "���ŧO");
		cout << endl;
		
		a = matchvec.size() ;
		if ( a == 0) {  // �Y�z�粒�����S���ŦX����ơA�h���i���ȤG 
			cout << "There is no matched records!" << endl ;
		}
		if ( a != 0) { // �z�缾����ơA�i���ȤG 

			Print(); // �L�X�Ҧ��ŦX����� 
			system("pause");
		
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << "@@@         Mission 1: Min-max Heap Construction         @@@" << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
			MinMaxHeap * minmaxheap = new MinMaxHeap();
			minmaxheap -> Build(); // �إ�minmax heap 
			minmaxheap -> Print(); // �LHEAP��bottom leftbottom 
			cout << endl << endl ;
			
			NumOk = false ;
		
			while ( !NumOk) {
				cout << "Enter the value of K:" << endl;
				int max = minmaxheap -> HowBig() ;
				cout << "[" << "1..." << max << "]" ;			
				cin >> readnum;//��J�ϥΪ̭n�X��MAx�� 
				k = atoi(readnum.c_str() ) ;
				if ( k >=1 && k <= max){  
					NumOk = true ;
				}
			}
		
			cout << "========================================================" << endl;
			cout << "Mission 2: Top-K maximums from min-max heap  K=(" << k <<  ")" << endl;
			cout << "========================================================" << endl;
		
		 
			minmaxheap -> GetMax(k);
			minmaxheap -> PrintMaxItems();	
			minmaxheap -> ClearMaxItems();	
			
			cout << "[0]Quit or [Any other]continue?" << endl;
			cin >> x ;
			if ( x == "0"){
				break ;
			}
		}

	}
	
	return 0;
}
