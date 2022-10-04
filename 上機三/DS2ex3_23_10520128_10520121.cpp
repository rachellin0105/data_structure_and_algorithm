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
bool set = false; // �O�_Ū�ҧ���
bool one = false ;

struct Data{
	int num;
	string school;
	string department;
	string day;
	string level;
	int graduate;
	vector<Data> *p1 = NULL;
	vector<Data> *p2 = NULL;
	vector<Data> *p3 = NULL;
	vector<Data> *p4 = NULL;
	
};

vector <Data> datavec;
typedef vector<Data>* DatavecPtr;
void Print(){ // �L�ŦX�ϥΪ̿�J���󪺩Ҧ���� 
	cout << "*** There are " << datavec.size() << " matched records, listed as below:" << endl;
	for( int i = 0; i < datavec.size() ;i++ ) {
		cout << "[" << datavec[i].num << "]" << datavec[i].school;
		cout << datavec[i].department << ',';
		cout << datavec[i].day << ',';
		cout << datavec[i].level << ',';
		cout << datavec[i].graduate << endl;
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
				if( count == 2)cur.school = cut;
				if( count == 4)cur.department = cut;
				if( count == 5)cur.day = cut;
				if( count == 6)cur.level = cut;
				if( count == 9){
					if( cut != "" )cur.graduate = atoi( cut.c_str() ); // atoi �� char *c �� int ; str.c_str() �� string �� char *c 
					else deletebool = true;
				} 
				count++;
				pre  = post+1;
			}
		
			count = 1;
			strcpy( cstr, "\0");
			if(!deletebool)datavec.push_back( cur ) ; // �p�G���~�ͤH�ƨS���ʶ� �N��J���VECTOR�� 
		}
	}
}


void Numbering(){
	for( int i = 1 ; i <= datavec.size() ; i++ )datavec[i-1].num = i;
}

DatavecPtr root;
DatavecPtr root1;

class TwoThreeTree{
	
	vector<Data> samevec;
	public:
		
	DatavecPtr New( Data data){ // �غc�@�� ���Ы��V�@��vector�����@�Ӹ�� 
		DatavecPtr temp = new vector<Data>;
		temp->push_back(data);
		return temp;
	}
	
	void Swap( Data & temp1, Data & temp2){ // temp1 swap with temp2 
		Data temp;
		temp = temp1;
		temp1 = temp2;
		temp2 = temp;
		
		DatavecPtr ptr;
		ptr = temp2.p1;
		temp2.p1 =temp1.p1;
		temp1.p1 = ptr;
		
		ptr = temp2.p2;
		temp2.p2 =temp1.p2;
		temp1.p2 = ptr;
		
		ptr = temp2.p3;
		temp2.p3 =temp1.p3;
		temp1.p3 = ptr;
		
	}
	
	int Height(DatavecPtr head, DatavecPtr item){ // ��item�Ҧb�� 
		int h = 1;

		while( head != item){
			if( head->size() == 2){
				if( item->size() == 2){
					if ( (*head)[0].school.compare((*item)[1].school) > 0 ) head = (*head)[0].p1;
					else if ( (*head)[0].school.compare((*item)[0].school) < 0 && (*head)[1].school.compare((*item)[1].school) > 0)head = (*head)[0].p2;
					else if ( (*head)[1].school.compare((*item)[0].school) < 0 )head = (*head)[0].p3;
				}
				else{
						if ( (*head)[0].school.compare((*item)[0].school) > 0 )head = (*head)[0].p1;
						else if ( (*head)[0].school.compare((*item)[0].school) < 0 && (*head)[1].school.compare((*item)[0].school) > 0)head = (*head)[0].p2;
						else if ( (*head)[1].school.compare((*item)[0].school) < 0 )head = (*head)[0].p3;
				}
			}
			else{
				if( item->size() == 2){
					if( (*head)[0].school.compare((*item)[1].school) > 0 )head = (*head)[0].p1;
					else head = (*head)[0].p2;
				}
				else{
					if ( (*head)[0].school.compare((*item)[0].school) > 0 ) head = (*head)[0].p1;
					else head = (*head)[0].p2;
				}

			}
			h++;
			
		}
		return h;
		
	
	}
	
	void PrintRoot(){  //�L�X�ڪ���� 
		int i = 0 ;
		int c = 0;
		bool print = false, B = false;
		while(i >= 0 ){
			cout << " " << ++c <<": ";
			cout << "["<< (*root)[i].num << "] ";
			cout << (*root)[i].school << ", ";
			cout << (*root)[i].department << ", ";
			cout << (*root)[i].day << ", ";
			cout << (*root)[i].level << ", ";
			cout << (*root)[i].graduate << endl;
			if( root->size() == 2&& !print) print = true,i =1;
			else B = true;
			for( int j = 0 ; j < samevec.size() ; j++ ){
				if( samevec[j].school.compare((*root)[i].school) == 0){
					c++;
					cout << " " << c << ": ";
					cout << "[" << samevec[j].num << "] " ;
					cout << samevec[j].school << ", " ;
					cout << samevec[j].department << ", " ;
					cout << samevec[j].day << ", " ;
					cout << samevec[j].level << ", " ;
					cout << samevec[j].graduate << endl ;
				}
				
			}
			if( B) break;
		}
	}
	
	void Print( DatavecPtr head){ // �L�Xnode&�Ҧb�� 
		if( head == NULL) ;
		else{
			
			cout << "^^^^^^ level : " << Height(root, head) << endl;
			for( int i = 0; i < head->size() ; i++){
				cout << " 1: ";
				cout << "["<< (*head)[i].num << "] ";
				cout << (*head)[i].school << ", ";
				cout << (*head)[i].department << ", ";
				cout << (*head)[i].day << ", ";
				cout << (*head)[i].level << ", ";
				cout << (*head)[i].graduate << endl;
				int c =2;
				for( int j = 0 ; j < samevec.size() ; j++ ){
					if( samevec[j].school.compare((*head)[i].school) == 0){
						cout << " "<< c << ": ";
						cout << "[" << samevec[j].num << "] " ;
						cout << samevec[j].school << ", " ;
						cout << samevec[j].department << ", " ;
						cout << samevec[j].day << ", " ;
						cout << samevec[j].level << ", " ;
						cout << samevec[j].graduate << endl ;
						c++;
					}
				}
				cout << "~~~~~~~~~~~~~~~~~~~~" << endl;				
			}
			
			Print((*head)[0].p1);
			Print((*head)[0].p2);
			Print((*head)[0].p3);
		}
	}
	
	void Sort( DatavecPtr & cur ){ // Key���Ƨ� 
		if( cur->size() == 1);
		else if( cur->size() == 2){
			if( (*cur)[0].school.compare((*cur)[1].school) > 0) Swap((*cur)[0],(*cur)[1]);
		}
		else {
			if( (*cur)[0].school.compare((*cur)[1].school) > 0) Swap((*cur)[0],(*cur)[1]);
			if( (*cur)[0].school.compare((*cur)[2].school) > 0)  Swap((*cur)[0],(*cur)[2]);
			if( (*cur)[1].school.compare((*cur)[2].school) > 0)  Swap((*cur)[1],(*cur)[2]);
		}

	}
	
	DatavecPtr FindParent(DatavecPtr p,DatavecPtr child){ // �^��child ������ 
		if( p == child ) return p; // root
		else if( p->size() == 2){
				if( (*p)[0].p1 == child || (*p)[0].p2 == child || (*p)[0].p3 == child ) return p;
				else if( child->size() == 2){
					if ( (*p)[0].school.compare((*child)[1].school) > 0 )FindParent( (*p)[0].p1, child );
					else if ( (*p)[0].school.compare((*child)[0].school) < 0 && (*p)[1].school.compare((*child)[1].school) > 0)FindParent( (*p)[0].p2,child );
					else if ( (*p)[1].school.compare((*child)[0].school) < 0 )FindParent( (*p)[0].p3,child);
				}
				else{
					if ( (*p)[0].school.compare((*child)[0].school) > 0 )FindParent( (*p)[0].p1, child );
					else if ( (*p)[0].school.compare((*child)[0].school) < 0 && (*p)[1].school.compare((*child)[0].school) > 0)FindParent( (*p)[0].p2,child );
					else if ( (*p)[1].school.compare((*child)[0].school) < 0 )FindParent( (*p)[0].p3,child);
				}
		}
		else if( p->size() == 1) {
			if((*p)[0].p1 == child || (*p)[0].p2 == child ) return p;
			else if( child->size() == 2 ){
				if( (*p)[0].school.compare((*child)[1].school) > 0 )FindParent( (*p)[0].p1 ,child);
				else FindParent( (*p)[0].p2,child);
			}
			else {
				if ( (*p)[0].school.compare((*child)[0].school) > 0 )FindParent( (*p)[0].p1 ,child);
				else FindParent( (*p)[0].p2,child);
			}

		}
	
	}
	
	void Split( DatavecPtr  cur, DatavecPtr  parent, int jump , DatavecPtr & A){ // ���� �Tkey�w�Ʀn��

		DatavecPtr temp = new vector<Data>;
		DatavecPtr temp2 = new vector<Data>;

		if ( cur->size() == 3 ){ // �ݭn���� 
			if( parent == cur ) {// �����  
				// temp���s����� 
				temp = New((*cur)[1]); 
				temp2 = New((*cur)[2]);	  
				cur->erase(cur->begin()+1);
				cur->erase(cur->begin()+2);

				(*temp)[0].p1 = cur;
				(*temp)[0].p2 = temp2;
				
				// �@�}�l �����u���T����Ʈ�  
					if( jump == 1 ){ // �ѥ�������W�Ӯ� 
						(*temp2)[0].p1 = (*cur)[0].p2;
						(*temp2)[0].p2 = (*cur)[0].p3;
						(*cur)[0].p2 = NULL;
						(*cur)[0].p3 = NULL;
						

					}
					if( jump == 2){  // �Ѥ��������W�Ӯ� 
						(*temp2)[0].p2 = (*cur)[0].p3;
						(*cur)[0].p3 = NULL;
						
						A = temp2;
						
					}
					if( jump == 3 ){// �ѥk������W�Ӯ� 
						
						(*temp2)[0].p1 = (*cur)[0].p3;
						(*cur)[0].p3 = NULL;
						A = temp2;

					}
					
					root =temp; // �@�}�l �����u���T����Ʈ� �u�ݭn���]�w 
										

			}
			else{
				if( parent->size() == 1 ){

					parent->push_back((*cur)[1]); // �����ȥ�W�h 
					Sort( parent ); // �Ƨ� �T�O���j�����|���\ 

					cur->erase(cur->begin()+1);
					temp = New((*cur)[1]);  // �j��Key �W�ߥX�� 
					cur->erase(cur->begin()+1); 
					if(cur == (*parent)[0].p1){ // ������ 
						(*parent)[0].p3 = (*parent)[0].p2;
						(*parent)[0].p2 = temp;
					}
					if(cur == (*parent)[0].p2){ // �k����  
						(*parent)[0].p3 = temp;
					}

					A = temp;

				}
				else{ // parent->size() == 2
					// jump �]�w���q���̨�(�^) 
					if( cur == (*parent)[0].p1) jump = 1;  
					else if( cur == (*parent)[0].p2) jump = 2;
					else if ( cur == (*parent)[0].p3) jump = 3;

					parent->push_back((*cur)[1]); // ����Key���W�� 
					Sort( parent ); 
					cur->erase(cur->begin()+1); // �R������Key 

					temp = cur; // temp �̤p��Key   
					temp2 = New((*cur)[1]); // temp �̤j��Key 
					cur->erase(cur->begin()+1);  
					
					Split( parent, FindParent(root,parent),jump,A); //���j ���W���� 
					
					
					// ������o��s�����`�I A
					// ��jump�ҰO������V �s��A�έ쥻��parent
					// A �]�n�]�w�p�G�U���٦��������ܭn������ (A�]��"�s"�����X�Ӫ�) 
					if(jump == 1 ){  
						if( A == NULL){ // root �T������ 
							(*parent)[0].p1 = temp;

								(*parent)[0].p2 = temp2;
								(*parent)[0].p3 = NULL;
								A = temp2;

						}
						else{
							(*parent)[0].p1 = temp;
								(*A)[0].p1 = (*parent)[0].p2;
								(*A)[0].p2 = (*parent)[0].p3;
								(*parent)[0].p2 = temp2;
								(*parent)[0].p3 = NULL;
								A = temp2;
						}
					}
					else if( jump == 2 ) {
						(*A)[0].p1 = temp2;
						if((*A)[0].p2 == NULL )(*A)[0].p2 = (*parent)[0].p3; 
						(*parent)[0].p2 = temp;
						(*parent)[0].p3 = NULL;
						A = temp2;
					}
					else if(jump == 3){
							(*parent)[0].p3 = NULL;												
							if((*A)[0].p1 == NULL) (*A)[0].p1 = temp;
							(*A)[0].p2 = temp2;						
							A = temp2;
					}

				}
			
			}

		}				 
	} 
	
	void Build(){ // �إ�2-3Tree 
		root = new vector<Data>;
		root = New(datavec[0]);
		datavec.erase(datavec.begin());
		while( datavec.size() != 0){ // �S���(�������ب��̤F)�ε��� 

			Insert( root, datavec[0] );
			datavec.erase(datavec.begin());
		}

	}
	
	void Insert(DatavecPtr cur, Data item){ // ���Ӹ�Ʃ��ݪ��� �é�J�� 
		
		DatavecPtr a = NULL;
		if ( (*cur)[0].p1 == NULL && (*cur)[0].p2 == NULL && (*cur)[0].p3 == NULL ) {// ��
			if( (*cur)[0].school.compare(item.school )== 0 ) samevec.push_back(item);
			else if( cur->size() == 2 && (*cur)[1].school.compare(item.school ) == 0 ) samevec.push_back(item);
			else cur->push_back(item);
				Sort( cur );
				DatavecPtr parent = FindParent(root,cur);
				if ( cur->size() == 3 )Split(cur,parent,0,a);// �p�L��J��KEY���T �h���� 		
		}
		//�S��� �~�򨫳X �@�˪��N��Jsamevec�� 
		else if( cur->size() == 1){
			if( (*cur)[0].school.compare(item.school )== 0 ) samevec.push_back(item);
			else if ( (*cur)[0].school.compare(item.school) > 0 )Insert( (*cur)[0].p1,item );
			else Insert( (*cur)[0].p2,item );
		}
		else 
		{
			if( (*cur)[0].school.compare(item.school )== 0 || (*cur)[1].school.compare(item.school )== 0) samevec.push_back(item);
			else if ( (*cur)[0].school.compare(item.school) > 0 )Insert( (*cur)[0].p1,item );
			else if ( (*cur)[0].school.compare(item.school) < 0 && (*cur)[1].school.compare(item.school) > 0)Insert( (*cur)[0].p2,item );
			else if ( (*cur)[1].school.compare(item.school) < 0 )Insert( (*cur)[0].p3,item );
		}

		
	}
	
	void search( string a ){ // ���ȤG�j�M�� 
		bool finish = false ;   
		one = false ;  // �ΨӧP�_�Ӹ`�I�O�_���ⵧ��� 
		int i = 0 ;
		DatavecPtr find = new vector<Data> ;
		vector<Data> *point = NULL ;
		find = root ;
		while ( !finish){
		if ( (*find)[0].p3 == NULL) { // �Y�ĤT��pointer = NULL �A����إi�� 1.�Ӹ`�I�u���@����� 2.�Ӹ`�I���ⵧ��ơB���O�O���l 
			if ( (*find).size() == 2 ){  // �Ӹ`�I�O���l 
				if ( a == (*find)[1].school) {
               		one = true ;
               	 	take( find); 
					finish = true ;
					break ;
				}
			}
			else if ( a == (*find)[0].school ){	
              take(find);   
              finish = true ;
              break ; 
			}
			else if ( a.compare( (*find)[0].school) < 0 ){
				if ( (*find)[0].p1 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
					finish = true ;
					break ;
				}
				else {
					find = (*find)[0].p1 ;  
				}
			}
			else{
				if ( (*find)[0].p2 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
					finish = true ;
					break ;
				}
				else {
					find = (*find)[0].p2 ;  
				}
			}
		} 
		else {  //�Ӹ`�I���ⵧ��� 
			if ( a == (*find)[0].school ){	
              take( find);  
              finish = true ;
              break ;
			}
			else if ( a == (*find)[1].school) {
                one = true ;
                take( find); 
				finish = true ;
				break ; 
			}
			else if ( a.compare( (*find)[0].school) < 0 ){ //Ū�J�����p�A������ 
				if ( (*find)[0].p1 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
					finish = true ;
					break ;
				}
				else {
					find = (*find)[0].p1 ;  
				}
				
			}
			else if ( a.compare( (*find)[1].school) > 0 ){  //Ū�J�����j�A���k�� 
				if ( (*find)[0].p3 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
             		finish = true;
             		break ;
				}
				else {
					find = (*find)[0].p3 ;  
				}
				
			}
			else {  //Ū�J�������Ƥ����A������ 
				if ( (*find)[0].p2 == NULL ) {
             		cout<< a << "cannot find a match!!!" << endl ; 
             		finish = true ;
             		break ;
				}
				else {
					find = (*find)[0].p2 ;
				}
			}
		}
	}
}

void take( DatavecPtr k){ // ��Ҧ���Ʀs�ifinal vector
	int run = 0 ;
	vector<Data> final ;
	if ( !one ){
		final.push_back( (*k)[0] ) ;
		while ( run < samevec.size() ){
			if( samevec[run].school.compare((*k)[0].school) == 0){ //��j�ǦW�٬ۦP����Ƥ]�s�i�h 
				final.push_back(samevec[run]) ;
			}
		run ++ ;
		}
	}
	else{
		final.push_back( (*k)[1] ) ;
		while ( run < samevec.size() ){
			if( samevec[run].school.compare((*k)[1].school) == 0){  //��j�ǦW�٬ۦP����Ƥ]�s�i�h  
				final.push_back(samevec[run]) ;
			}
			run ++ ;
		}		
	}

	order( final) ;
	mission2print( final) ;
}


void order ( vector<Data> &done){ // �Nvinal vector ������ƷӲ��~�H�ƥѤj��p��
 Data temp ;
 int how = done.size() ;
 int run1 = 0 ;
 int run2 = 0 ;
 while ( run1 < how ){
 	run2 = run1 ;
 	while ( run2 < how ) {
 		if ( done[run1].graduate < done[run2].graduate ) {
  	 	temp = done[run1] ;
  	 	done[run1] = done[run2];
  	 	done[run2] = temp ;
 	 	}
  		run2++ ;
	}
	run1 ++ ;
}
}


void mission2print( vector<Data> done ){  // �L�X���ȤG�n���F�� 
	int j = 0 ;
	while ( j < done.size()){
		cout << j+1 << " : " ;
		cout << "["<< done[j].num << "] ";
		cout << done[j].school << ", ";
		cout << done[j].department << ", ";
		cout << done[j].day << ", ";
		cout << done[j].level << ", ";
		cout << done[j].graduate << endl;
		j++ ;
	}
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
		cout << "***         Mission 1: construct 2-3 tree              ***" << endl;
		cout << "***   Mission 2: Find top-K maximums by min-max heap   ***" << endl;
		cout << "**********************************************************" << endl;

		
		while( !set ){
			datavec.clear();
			cout << "Input the file number: 301, 302, ..... [0]Quit" << endl;
			cin >> fileNum ;
			if ( fileNum =="0"){
				IsZero = true ;
				break ;
				
			}
			fileName = "input" + fileNum + ".txt";
			ReadFileAndBuildDatavec();
			Numbering();
		}
		if ( IsZero){
			break ;
		}
		set = false;
		fin.close();		

		Print(); // �L�X�Ҧ��ŦX����� 	
		cout << "**********************************************************" << endl;
		cout << "***         Mission 1: construct a min-max heap        ***" << endl;
		cout << "**********************************************************" << endl;	
			TwoThreeTree *twothreetree = new TwoThreeTree();
			root = NULL;
			twothreetree->Build();
			twothreetree->PrintRoot();
			twothreetree->Print(root);				
			root1 = NULL ;
			system("PAUSE");
			cout << endl ;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
			cout << "Mission 2: Search a 2-3 tree (Search key is college name)" << endl ;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
			cout << "Enter a name to search:" << endl ; 
			string k ;
			cin >> k ; //Ū�J�ϥΪ̿�J���j�ǦW�� 
			twothreetree->search(k) ;
	
			
			cout << "[0]Quit or [Any other]continue?" << endl;
			cin >> x ;
			if ( x == "0"){
				break ;
			}		
	}
}
