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
	bool visited2;
	float weights ; 
};




struct outside{
	char Id1[10] ; 
	bool visited;
	bool visited2;
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
			tempin.visited2 = false;
			tempout.visited2 = false;
			big.push_back( tempout) ; // �b�۾F��C���إ߲Ĥ@����� 
			big[0].small.push_back( tempin ) ;
			
			//------------------------------------------------------------------- // �N�Ǹ���աB�إ߲ĤG����� 
			strcpy( tempout.Id1, one[i].Id2 ) ;  
			strcpy( tempin.Id2, one[i].Id1 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			tempin.visited2 = false;
			tempout.visited2 = false;
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
			tempin.visited2 = false;
			tempout.visited2 = false;
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
			tempin.visited2 = false;
			tempout.visited2 = false;
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
				
				if ( big[run1].small[run2].weights >= big[run1].small[run3].weights){   // ��p������h 
					
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
	float sweights;
};


void Setvisied( char str[10]){  // �N�I�]��visited ��ܦbDFS�� �]���w���X (���P�ꤤ�Ǹ��@�˪����n�]��visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited = true;
		}
	}
	
}
void Setvisited2( char str[10]){ //// �N�I�]��visited2 ��ܦbPrim �t��k�� �]���w���X (���P�ꤤ�Ǹ��@�˪����n�]��visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited2 = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited2 = true;
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

void sortInside(vector<inside> & item){ //  PQ �����v���Ƨ� �H�T�Ovec���Ĥ@����Ƭ��̤p�v�� 
	char temp[10] = " ";
	bool tempv;
	bool tempv2;
	float tempws ; 
	for( int i = 0; i < item.size() ; i++){
		for( int j = i+1 ; j < item.size() ; j++){
			if( item[i].weights > item[j].weights ){
				
				strcpy( temp, item[i].Id2);
				strcpy( item[i].Id2, item[j].Id2);
				strcpy( item[j].Id2, temp);
				
				tempv = item[i].visited;
				item[i].visited =  item[j].visited;
				item[j].visited =  tempv;
				
				tempv2 = item[i].visited2;
				item[i].visited2 =  item[j].visited2;
				item[j].visited2 =  tempv2;
				
				tempws = item[i].weights;
				item[i].weights =  item[j].weights;
				item[j].weights =  tempws;
			}
		}
	}
}



void Print( vector<Stack> item, int count ){ //  �L�X�C�@��subgraph 
	cout << endl <<"{ " << count << "}";
	cout <<" Connected Components: size = " << item.size() << endl << '\t';
	for( int i = 0 ; i < item.size() ; i++){
		cout << "(" << i+1 << ")" << item[i].sId ;
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
	
	sort(connect);
	 
}



vector< inside> pq;

// PQ �� priority queue 

void PQDelete( char id[10] ){ // �NPQ���w���X�L���I ���ݭn���䪺�R�� 
	for( int i = 0 ; i <pq.size() ;){
		if( strcmp(pq[i].Id2, id ) == 0 ) pq.erase( pq.begin() + i );
		else i++;
	}
}


inside PQ( char id[10] ){ // �N�i��Ҧ���w���X�I�s�������JPQ�� 
	int i = 0;
	for( i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,id) == 0 )break;
	}
	
	for( int j = 0 ; j < big[i].small.size() ; j++ ){
		if(  ! big[i].small[j].visited2 ) { // �Y�٥�visited �h��JPQ 
			pq.push_back( big[i].small[j] );
		}
		
	}
	
	
	 sortInside( pq ); // �Ƨ� 
	 inside temppq =  pq.front(); // ���Ĥ@�� 
	 PQDelete(temppq.Id2 ); // �R���w���X���I�ұ�����L�� 
	 return temppq;
	
	
}

vector<float> sumvec;
void MST( char id[10], int numOfConnect ){ // ��XMST���`�v�� 

	inside unvisited;
	char temp[10];
	strcpy( temp , id);
	Setvisited2( temp );

	int countEdge = 0;
	float sum = 0;
	while( countEdge < numOfConnect -1  ) { // �ϥ�Prim's �t��k 
		unvisited = PQ(temp); // PQ �|�^���٨S���X��B�즹�I�v���̤p���I 
		strcpy(temp,unvisited.Id2);
		Setvisited2( unvisited.Id2 );  
		sum = sum + unvisited.weights; // ���v�� 
		countEdge++;
	}
	
	sumvec.push_back(sum); 
	pq.clear();
}

void PrintSum( int count ){ // �L�X��count �� connected component ���`�v�� 
	for( int c =  1 ; c <= count ; c++)
	cout << "The MST cost of connect component <" << c << "> = " << sumvec[c-1] << endl;
}

void Traversals(string filenum){ // ���Xgraph 
	int count = 0, numOfConnect = 0;
	for( int i  = 0; i < big.size() ; i++ ){
		// �ˬd�O�_�٦��I������ ���X��Lsubgraph 
		if( !big[i].visited ) {
			DFS( big[i].Id1,++count,filenum ); // DFS ���X 
			numOfConnect = connect.size();  // ���X���X���� 
			MST( big[i].Id1, numOfConnect ); // ��MST 
			Print(connect,count); // �L�X�M��Xsubgraphs
			connect.clear();
		}
	}

	PrintSum( count ); // �L�X�Ҧ�connected component ���`�v�� 
	sumvec.clear();
	count = 0;
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char what[10] ;

struct m3 {
	char Id[10] ;
};

m3 ok ;
vector<m3> already ; 

struct use {
	char Id[10] ;
	float weights ;
};

vector<use> save ;
use take ; 


void copy() {
	int a = 0 ;
	while ( a < connect.size() ){
		strcpy( take.Id, connect[a].sId );
		take.weights = 0 ;
		save.push_back( take ) ;
		a++ ;	
	}
	
	
	
}

void clean(){ // ������]�w����visited 
	int in = 0 ;
	int out = 0 ;
	while ( out < big.size() ){
		big[out].visited = false ;
		while ( in < big[out].small.size() ){
			big[out].small[in].visited = false ;			
			in++ ;
		}
		
		out++ ;
		in = 0 ; 
	}

}

void Do4( char what[10] ){
	float now = 0 ;
	int i = 0 ;
	int run1 = 0 ;
	int run2 = 0 ;
	strcpy ( ok.Id, what );
	already.push_back( ok ) ;
	
	
	
	
	while ( i < big.size() ){ // �Ĥ@�� 
		if ( strcmp ( what, big[i].Id1 ) == 0 ){
			while ( run1 < big[i].small.size() ){
				while ( run2 < save.size() ){				
					if ( strcmp(big[i].small[run1].Id2, save[run2].Id) == 0 ){
						save[run2].weights = now+ big[i].small[run1].weights ;
						now = big[i].small[0].weights ;	
						what = big[i].small[0].Id2 ;			
						break ; 
					} // if
					run2++ ;
				} // while		
				
				run1 ++ ;
				run2 = 0 ;
			} // while 
		} //if
		
		i++ ;
	} // while
	
	cout << endl ; 
	cout << what<< "  "<< now ;
	i = 0 ; 
	run1 = 0 ; 
	run2 = 0 ; 
	strcpy ( ok.Id, what );
	already.push_back( ok ) ;
	
	while ( already.size() != save.size() ) {
		while ( i < big.size() ){
			if ( strcmp( what, big[i].Id1) == 0 ){
				
				
				
				
			} // if
		
		
			
			
		} // while
		
		
	} // while 	
	
	
	
	
	
} // Do4()

void mission4( string filenum ){
	

	cout << endl  << "�п�J�@�ӾǸ�" << endl  ;
	cin >> what ;
	cout << endl << endl ;
	clean() ;
	DFS( what, 0, filenum ) ; //�M��P�էO���٦�����  
	copy() ; 
	Do4( what) ;
	
	
	
	
	
}


void seee(){
	int i = 0 ; 
	
	while ( i < save.size() ){
		cout << save[i].Id << "     "<<save[i].weights <<endl ; 
		i++ ;
	}
	
}

 




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

			Do() ;  
			arrange() ;
			Build( filenum ) ; 
			print2() ;
			cout<< "######################################################" << endl;
			cout<< " Mission 2: Build adjacency lists " << endl;
			cout<< "######################################################" << endl;
			cout << "~~~ Connected Components ~~~"<< endl;
			Traversals(filenum);
			mission4( filenum ) ;
			seee() ;
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
			}
			cin >> filenum ;
		} //if
		else{
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
