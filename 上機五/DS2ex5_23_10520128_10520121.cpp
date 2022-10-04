// 第23組 
// 10520121 杜欣洋	
// 10520128 林佳穎

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

struct Data {   // 用來存讀近來bin檔的資料 
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



bool open( string filenum){ //開檔 ，讀檔 
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
		
		
	if ( big.empty() ){  // 若完全沒資料 
			
			strcpy( tempout.Id1, one[i].Id1 ) ;
			strcpy( tempin.Id2, one[i].Id2 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			big.push_back( tempout) ; // 在相鄰串列中建立第一筆資料 
			big[0].small.push_back( tempin ) ;
			
			//------------------------------------------------------------------- // 將學號對調、建立第二筆資料 
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
		else{    // 相鄰串列已經有資料 
		
			strcpy( tempout.Id1, one[i].Id1 ) ;
			strcpy( tempin.Id2, one[i].Id2 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			run1 = 0 ;
			
			while ( run1 < big.size()  ){  //進去找是否有相同的學號 

				if( strcmp(tempout.Id1, big[run1].Id1 ) <=0 ){   //學號比較小或相同 
					if (strcmp(tempout.Id1, big[run1].Id1 ) ==0 ){ //有相同的學號 
						big[run1].small.push_back( tempin ) ;	  //將Id2塞入同學號的vector 
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
			
			//--------------------------------------------------------// 將學號對調，再做一次上面的動作 
			

			strcpy( tempout.Id1, one[i].Id2 ) ;
			strcpy( tempin.Id2, one[i].Id1 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			run1 = 0 ;
			
			while ( run1 < big.size()  ){  //進去找是否有相同的學號 

				if( strcmp(tempout.Id1, big[run1].Id1 ) <=0 ){   //學號比較小或相同 
					if (strcmp(tempout.Id1, big[run1].Id1 ) ==0 ){ //有相同的學號 
						big[run1].small.push_back( tempin ) ;	  //將Id2塞入同學號的vector 
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




void arrange(){   // 	將資料照權重排順序 
	int run1 = 0 ;
	int run2 = 0 ; 
	int run3 = 1 ;
	int copy = 0 ;   
	inside tempin ; 
	while ( run1 < big.size()  ){
		
		while ( run2 < big.size()  ){
			
			while ( run3 < big[run1].small.size()  ){
				
				if ( big[run1].small[run2].weights <= big[run1].small[run3].weights){   // 把小的往後搬 
					
					if ( big[run1].small[run2].weights == big[run1].small[run3].weights){  // 若兩筆資料一樣 
					
						if ( strcmp(big[run1].small[run2].Id2 , big[run1].small[run3].Id2) > 0){  //兩筆資料一樣，比學號，學號小的在前面 

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




void print(){    // 測試用 
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

void Build(string filenum){  //建立ADJ檔 
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


	
int count(){  // 計算有幾個結點 
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


void print2(){  //顯示必要的東西在螢幕上 
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


void Setvisied( char str[10]){  // 將點設為visited  (不同串中學號一樣的都要設為visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited = true;
		}
	}
	
}

bool AdjacentHasNotVisited( Stack temp, Stack &UnVisited){ // 如果temp.sId這點 附近還有位走訪的 則回傳true ,反之亦然 
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

void sort(vector<Stack> & connect){ // 將在同一個subgraph的點排序後印出 
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
void BuildCC(vector<Stack> connect,string filenum,int count ){ // 每一個subgraph寫入CC黨 
	fout << endl <<"{ " << count << "}";
	fout <<" Connected Components: size = " << connect.size() << endl << '\t';
	for( int i = 0 ; i < connect.size() ; i++){
		fout << "(" << i+1 << ")" << connect[i].sId ;
		if( (i+1)%5 == 0 ) fout << endl<< '\t';
	} 
}
void Print( vector<Stack> connect, int count ){ //  印出每一個subgraph 
	cout << endl <<"{ " << count << "}";
	cout <<" Connected Components: size = " << connect.size() << endl << '\t';
	for( int i = 0 ; i < connect.size() ; i++){
		cout << "(" << i+1 << ")" << connect[i].sId ;
		if( (i+1)%5 == 0 ) cout << endl << '\t';
	}
	
}
vector<Stack> connect; //subgraphs
void DFS( char id[10] , int count,string filenum){ // 使用stack實現DFS 
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
			stack.push_back( UnVisited ); // 往下visited		
		}
		else {
			connect.push_back( stack.back() );
			stack.pop_back(); // explored
		}
	}
	
	// 印出和輸出subgraphs 
	sort(connect); 
	BuildCC(connect, filenum , count);
	Print(connect,count);
	connect.clear();
	 
}

void Traversals(string filenum){ // 走訪graph 
	string filename = " pairs"+filenum + ".cc";
	fout.open( filename.c_str()); // 建立CC檔 
	int count = 0;
	for( int i  = 0; i < big.size() ; i++ ){
		// 檢查是否還有點為走到 走訪其他subgraph 
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
			// 任務一 
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
