// ��23�� 
// 10520121 ���Y�v	
// 10520128 �L�οo

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <HashTable.h>
#include <stdio.h>
# include <cstdio>
#include <stdlib.h>

using namespace std;

void print() ;

struct Data {   // �ΨӦsŪ���bin�ɪ���� 
	char Id1[10] ;
	char Id2[10] ;
	float weights ;
	bool visited;
};

vector<Data> one ; 

Data read ;



struct inside{
	char Id2[10] ;
	bool visited;
	float weights ; 
};




struct outside{
	char Id1[10] ; 
	bool visited;
	vector<inside> small ;
};



vector<outside> big ;  



bool open( string filenum){ //�}�� �AŪ�� 
	int i = 0 ;
	int run = 0 ; 
	FILE *file ;

	string filename = "pairs";
	filename = filename+ filenum + ".bin";
	file = fopen(filename.c_str(), "rb" ) ;
	
	
	if( file ){
	while ( 1 ) {
		
		if ( feof(file)) break ; 
		
		fread((char*)read.Id1, sizeof(read.Id1), 1, file) ;
		fread((char*)read.Id2, sizeof(read.Id2), 1, file) ;
 		fread(&read.weights, sizeof(read.weights), 1, file) ;
		one.push_back( read) ;

	
	}
	fclose( file) ;
	one.pop_back() ;
	return true; 
	}
	else{
		return false ;
	}
}


void Do(){
	
	int i = 0 ;
	int run1 = 0 ;
	int run2 = 0 ;
	outside tempout ; 
	inside tempin ; 

	while ( i < one.size() ){
		
		
	if ( big.empty() ){  // �Y�����S��� 
			
			strcpy( tempout.Id1, one[i].Id1 ) ;
			strcpy( tempin.Id2, one[i].Id2 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			big.push_back( tempout) ; // �b�۾F��C���إ߲Ĥ@����� 
			big[0].small.push_back( tempin ) ;
			
			//------------------------------------------------------------------- // �N�Ǹ���աB�إ߲ĤG����� 
			strcpy( tempout.Id1, one[i].Id2 ) ;  
			strcpy( tempin.Id2, one[i].Id1 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			if ( strcmp( one[i].Id1, one[i].Id2 ) > 0 ){  

				big.insert( big.begin(), tempout );
				big[0].small.push_back(tempin) ;
			}
			else{
				big.push_back( tempout) ;
				big[1].small.push_back( tempin ) ;
			}		

		} // if
		else{    // �۾F��C�w�g����� 
		
			strcpy( tempout.Id1, one[i].Id1 ) ;
			strcpy( tempin.Id2, one[i].Id2 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			run1 = 0 ;
			
			while ( run1 < big.size()  ){  //�i�h��O�_���ۦP���Ǹ� 

				if( strcmp(tempout.Id1, big[run1].Id1 ) <=0 ){   //�Ǹ�����p�άۦP 
					if (strcmp(tempout.Id1, big[run1].Id1 ) ==0 ){ //���ۦP���Ǹ� 
						big[run1].small.push_back( tempin ) ;	  //�NId2��J�P�Ǹ���vector 
						break ;
					}
					else{  
						big.insert(big.begin()+run1, tempout) ;
						big[run1].small.push_back(tempin) ;		
						break ;				
					} //else			
				} //if
				else{
					if ( run1 != big.size() -1){
						run1++ ;
					}
					else{
						big.push_back(tempout) ;
						big[run1+1].small.push_back(tempin) ;		
						break ;		
					}
				} //else 
							
			} //while	
			
			//--------------------------------------------------------// �N�Ǹ���աA�A���@���W�����ʧ@ 
			

			strcpy( tempout.Id1, one[i].Id2 ) ;
			strcpy( tempin.Id2, one[i].Id1 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			run1 = 0 ;
			
			while ( run1 < big.size()  ){  //�i�h��O�_���ۦP���Ǹ� 

				if( strcmp(tempout.Id1, big[run1].Id1 ) <=0 ){   //�Ǹ�����p�άۦP 
					if (strcmp(tempout.Id1, big[run1].Id1 ) ==0 ){ //���ۦP���Ǹ� 
						big[run1].small.push_back( tempin ) ;	  //�NId2��J�P�Ǹ���vector 
						break ;
					}
					else{  
						big.insert(big.begin()+run1, tempout) ;
						big[run1].small.push_back(tempin) ;		
						break ;				
					} //else			
				} //if
				else{
					if ( run1 != big.size() -1){
						run1++ ;
					}
					else{
						big.push_back(tempout) ;
						big[run1+1].small.push_back(tempin) ;		
						break ;		
					}
				} //else 
							
			} //while	

		} // else
	
		i++ ;

	} // while 

}




void arrange(){   // 	�N��Ʒ��v���ƶ��� 
	int run1 = 0 ;
	int run2 = 0 ; 
	int run3 = 1 ;
	int copy = 0 ;   
	inside tempin ; 
	while ( run1 < big.size()  ){
		
		while ( run2 < big.size()  ){
			
			while ( run3 < big[run1].small.size()  ){
				
				if ( big[run1].small[run2].weights <= big[run1].small[run3].weights){   // ��p������h 
					
					if ( big[run1].small[run2].weights == big[run1].small[run3].weights){  // �Y�ⵧ��Ƥ@�� 
					
						if ( strcmp(big[run1].small[run2].Id2 , big[run1].small[run3].Id2) > 0){  //�ⵧ��Ƥ@�ˡA��Ǹ��A�Ǹ��p���b�e�� 

							strcpy(tempin.Id2, big[run1].small[run3].Id2);					
							tempin.weights = big[run1].small[run3].weights ;
			// ------------------------------------------------------------------------------------
				 

							strcpy(big[run1].small[run3].Id2,  big[run1].small[run2].Id2);
					
							big[run1].small[run3].weights = big[run1].small[run2].weights ;
					
					
			// ------------------------------------------------------------------------------------

							strcpy(big[run1].small[run2].Id2,  tempin.Id2);
							big[run1].small[run2].weights = tempin.weights ;
						}
					}
					else{

						strcpy(tempin.Id2,  big[run1].small[run3].Id2 );
						tempin.weights = big[run1].small[run3].weights ;
			// ------------------------------------------------------------------------------------
				 

						strcpy(big[run1].small[run3].Id2, big[run1].small[run2].Id2);
						big[run1].small[run3].weights = big[run1].small[run2].weights ;
					
					
			// ------------------------------------------------------------------------------------

						strcpy(big[run1].small[run2].Id2,  tempin.Id2);
						big[run1].small[run2].weights = tempin.weights ;
				 				 
				 			 
					} // else

				} //if 
				
				run3 ++ ;
			}
	
			run2++ ;
			run3 = run2+1  ; 
		}
		
		run1 ++ ;
		run2 = 0 ;
		run3 = 1 ;	
	}
	

}




void print(){    // ���ե� 
	int i = 0 ; 
	int j = 0 ; 
	while ( i < big.size() ){
		
		cout << "[" << i+1 << "]" << big[i].Id1 << endl ;
		while ( j < big[i].small.size() ){
			cout << "(" << j + 1 << ")" << "" ;
			cout << big[i].small[j].Id2 << ", " <<  big[i].small[j].weights << "   "  ; 
			j++ ;
		}
		
		cout << endl ;
		i++ ; 
		j = 0 ;
		cout << endl ; 
	}
}

void Build(string filenum){  //�إ�ADJ�� 
	ofstream fileadj;
	string filename = "pairs";
	filename = filename+ filenum + ".adj";
	fileadj.open(filename.c_str());


	int i = 0 ; 
	int j = 0 ; 
	int node = 0 ;
	while ( i < big.size() ){
		
		fileadj << "[ " << i+1 << " ] " << big[i].Id1 << " : "<< endl ;
		fileadj <<"       ";
		while ( j < big[i].small.size() ){
			fileadj << "(" << j + 1 << ")" << "" ;
			fileadj << big[i].small[j].Id2 << ",   " <<  big[i].small[j].weights << "   "  ; 
			if ( (j+1) % 5 == 0 ){
				fileadj << endl ; 
				fileadj <<"       ";
			}
			j++ ;
			node ++ ;
		}
		
		i++ ; 
		j = 0 ;
		fileadj << endl <<endl ; 
	}
	
	
	fileadj << "<<<  There are " << node << " nodes in total. >>>" ;
	fileadj.close() ;

}


	
int count(){  // �p�⦳�X�ӵ��I 
	int i = 0 ; 
	int j = 0 ; 
	int node = 0 ;
	while ( i < big.size() ){
		
		while ( j < big[i].small.size() ){

			j++ ;
			node ++ ;
		}
		
		i++ ; 
		j = 0 ;
	}
	
	return node ;
}


void print2(){  //��ܥ��n���F��b�ù��W 
	cout << endl ; 
	cout << "<<< "  << one.size() << "pairs => " << count() << " nodes >>>" << endl ;
	system("PAUSE") ;
	cout << endl << endl << "Adjacency lists are written into a file... " << endl << endl ;
	cout << "<<<  There are " << count() << " nodes in total. >>>" << endl ;
	system("PAUSE") ;
}
struct Stack{
	char sId[10];
};


void Setvisied( char str[10]){  // �N�I�]��visited  (���P�ꤤ�Ǹ��@�˪����n�]��visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited = true;
		}
	}
	
}

bool AdjacentHasNotVisited( Stack temp, Stack &UnVisited){ // �p�Gtemp.sId�o�I �����٦��쨫�X�� �h�^��true ,�Ϥ���M 
	int i = 0;
	for( i = 0; i < big.size(); i++){
			if(strcmp(temp.sId,big[i].Id1) == 0) break;
	}
	
	for( int j = 0; j < big[i].small.size() ; j++){
		if( ! big[i].small[j].visited ){
			strcpy(UnVisited.sId,big[i].small[j].Id2);
			return true;
		}
	}
	
	return false;

}

void sort(vector<Stack> & connect){ // �N�b�P�@��subgraph���I�Ƨǫ�L�X 
	char temp[10] = " ";
	for( int i = 0; i < connect.size() ; i++){
		for( int j = i+1 ; j < connect.size() ; j++){
			if( strcmp(connect[i].sId, connect[j].sId ) > 0){
				strcpy( temp, connect[i].sId);
				strcpy( connect[i].sId, connect[j].sId);
				strcpy( connect[j].sId, temp);
			}
		}
	}
}
ofstream fout;
void BuildCC(vector<Stack> connect,string filenum,int count ){ // �C�@��subgraph�g�JCC�� 
	fout << endl <<"{ " << count << "}";
	fout <<" Connected Components: size = " << connect.size() << endl << '\t';
	for( int i = 0 ; i < connect.size() ; i++){
		fout << "(" << i+1 << ")" << connect[i].sId ;
		if( (i+1)%5 == 0 ) fout << endl<< '\t';
	} 
}
void Print( vector<Stack> connect, int count ){ //  �L�X�C�@��subgraph 
	cout << endl <<"{ " << count << "}";
	cout <<" Connected Components: size = " << connect.size() << endl << '\t';
	for( int i = 0 ; i < connect.size() ; i++){
		cout << "(" << i+1 << ")" << connect[i].sId ;
		if( (i+1)%5 == 0 ) cout << endl << '\t';
	}
	
}
vector<Stack> connect; //subgraphs
void DFS( char id[10] , int count,string filenum){ // �ϥ�stack��{DFS 
	vector<Stack> stack;
	Stack temp;
	Stack UnVisited;
	strcpy(temp.sId,id);
	stack.push_back( temp ); 
	Setvisied( temp.sId ); 
	while( !stack.empty()){
		temp = stack.back();
		if( AdjacentHasNotVisited(temp, UnVisited) ) {
			Setvisied( UnVisited.sId ); 
			stack.push_back( UnVisited ); // ���Uvisited		
		}
		else {
			connect.push_back( stack.back() );
			stack.pop_back(); // explored
		}
	}
	
	// �L�X�M��Xsubgraphs 
	sort(connect); 
	BuildCC(connect, filenum , count);
	Print(connect,count);
	connect.clear();
	 
}

void Traversals(string filenum){ // ���Xgraph 
	string filename = " pairs"+filenum + ".cc";
	fout.open( filename.c_str()); // �إ�CC�� 
	int count = 0;
	for( int i  = 0; i < big.size() ; i++ ){
		// �ˬd�O�_�٦��I������ ���X��Lsubgraph 
		if( !big[i].visited ) DFS( big[i].Id1,++count,filenum );
	}
	count = 0;
	fout.close();
}

int main() {
	

	string filenum = "-1";
		cout << "********************************************" << endl;
		cout << "On-machine Exercise                        *" << endl;
		cout << "Mission 1: Build adjacency lists           *" << endl;
		cout << "Mission 2: Find connected components       *" << endl;
		cout << "********************************************" << endl;
		cout<< "######################################################" << endl;
		cout<< " Mission 1: Build adjacency lists " << endl;
		cout<< "######################################################" << endl;
		cout << "Input the file name <e.g. , 501,502 >: [0]Quit" << endl;	
	 	cin >> filenum ; 
	
	while (filenum != "0" ){ 
	


		if ( open( filenum) ){
			// ���Ȥ@ 
			Do() ;  
			arrange() ;
			Build( filenum ) ; 
			print2() ;
			cout<< "######################################################" << endl;
			cout<< " Mission 2: Build adjacency lists " << endl;
			cout<< "######################################################" << endl;
			cout << "~~~ Connected Components ~~~"<< endl;
			Traversals(filenum);
			cout << endl <<"[0]Quit or [Any other]continue?" << endl;
			cin >> filenum ;
			if ( filenum != "0"){
				cout << "********************************************" << endl;
				cout << "On-machine Exercise                        *" << endl;
				cout << "Mission 1: Build adjacency lists           *" << endl;
				cout << "Mission 2: Find connected components       *" << endl;
				cout << "********************************************" << endl;
				cout<< "######################################################" << endl;
				cout<< " Mission 1: Build adjacency lists " << endl;
				cout<< "######################################################" << endl;
				cout << "Input the file name <e.g. , 501,502 >: [0]Quit" << endl;
				cin >> filenum ;			
			}
		} //if
		else if( filenum == "0" ) break;
		else {
			cout << endl ;
			cout << "pairs" << filenum << ".bin does not exist!!! " << endl << endl ;
			cout << "Input the file name (e.g., 501, 502): [0]Quit " << endl ;
			cin >> filenum ; 
		} // else	 
	
		connect.clear();
		big.clear();
		one.clear();
	
}
} 
