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
	bool visited2;
	float weights ; 
};




struct outside{
	int num ;
	char Id1[10] ; 
	bool visited;
	bool visited2;
	vector<inside> small ;
};


void seee() ;

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
			tempin.visited2 = false;
			tempout.visited2 = false;
			big.push_back( tempout) ; // 在相鄰串列中建立第一筆資料 
			big[0].small.push_back( tempin ) ;
			
			//------------------------------------------------------------------- // 將學號對調、建立第二筆資料 
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
		else{    // 相鄰串列已經有資料 
		
			strcpy( tempout.Id1, one[i].Id1 ) ;
			strcpy( tempin.Id2, one[i].Id2 ) ;
			tempin.weights = one[i].weights ;
			tempin.visited = false;
			tempout.visited = false;
			tempin.visited2 = false;
			tempout.visited2 = false;
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
			tempin.visited2 = false;
			tempout.visited2 = false;
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
				
				if ( big[run1].small[run2].weights >= big[run1].small[run3].weights){   // 把小的往後搬 
					
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
		big[i].num = i + 1 ;
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
	float sweights;
};


void Setvisied( char str[10]){  // 將點設為visited 表示在DFS中 設為已走訪 (不同串中學號一樣的都要設為visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited = true;
		}
	}
	
}
void Setvisited2( char str[10]){ //// 將點設為visited2 表示在Prim 演算法中 設為已走訪 (不同串中學號一樣的都要設為visited) 

	for ( int i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,str) == 0 ) big[i].visited2 = true;
		for( int j = 0 ; j < big[i].small.size() ; j++ ){
			if( strcmp(big[i].small[j].Id2,str) == 0) big[i].small[j].visited2 = true;
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

void sortInside(vector<inside> & item){ //  PQ 內依權重排序 以確保vec中第一筆資料為最小權重 
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



void Print( vector<Stack> item, int count ){ //  印出每一個subgraph 
	cout << endl <<"{ " << count << "}";
	cout <<" Connected Components: size = " << item.size() << endl << '\t';
	for( int i = 0 ; i < item.size() ; i++){
		cout << "(" << i+1 << ")" << item[i].sId ;
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
	
	sort(connect);
	 
}



vector< inside> pq;

// PQ 為 priority queue 

void PQDelete( char id[10] ){ // 將PQ中已走訪過的點 不需要的邊的刪掉 
	for( int i = 0 ; i <pq.size() ;){
		if( strcmp(pq[i].Id2, id ) == 0 ) pq.erase( pq.begin() + i );
		else i++;
	}
}


inside PQ( char id[10] ){ // 將可能所有跟已走訪點連接的邊丟入PQ中 
	int i = 0;
	for( i = 0 ; i < big.size() ; i++){
		if( strcmp(big[i].Id1,id) == 0 )break;
	}
	
	for( int j = 0 ; j < big[i].small.size() ; j++ ){
		if(  ! big[i].small[j].visited2 ) { // 若還未visited 則丟入PQ 
			pq.push_back( big[i].small[j] );
		}
		
	}
	
	
	 sortInside( pq ); // 排序 
	 inside temppq =  pq.front(); // 取第一個 
	 PQDelete(temppq.Id2 ); // 刪除已走訪的點所接的其他邊 
	 return temppq;
	
	
}

vector<float> sumvec;
void MST( char id[10], int numOfConnect ){ // 算出MST的總權重 

	inside unvisited;
	char temp[10];
	strcpy( temp , id);
	Setvisited2( temp );

	int countEdge = 0;
	float sum = 0;
	while( countEdge < numOfConnect -1  ) { // 使用Prim's 演算法 
		unvisited = PQ(temp); // PQ 會回傳還沒走訪到且到此點權重最小的點 
		strcpy(temp,unvisited.Id2);
		Setvisited2( unvisited.Id2 );  
		sum = sum + unvisited.weights; // 算權重 
		countEdge++;
	}
	
	sumvec.push_back(sum); 
	pq.clear();
}

void PrintSum( int count ){ // 印出第count 的 connected component 的總權重 
	cout << endl << endl ;
	for( int c =  1 ; c <= count ; c++)
	cout << "The MST cost of connect component <" << c << "> = " << sumvec[c-1] << endl << endl ;
}

void Traversals(string filenum){ // 走訪graph 
	int count = 0, numOfConnect = 0;
	for( int i  = 0; i < big.size() ; i++ ){
		// 檢查是否還有點為走到 走訪其他subgraph 
		if( !big[i].visited ) {
			DFS( big[i].Id1,++count,filenum ); // DFS 走訪 
			numOfConnect = connect.size();  // 給出有幾個邊 
			MST( big[i].Id1, numOfConnect ); // 找MST 
			Print(connect,count); // 印出和輸出subgraphs
			connect.clear();
		}
	}

	cout << endl ;
	system("pause") ;
	PrintSum( count ); // 印出所有connected component 的總權重 
	sumvec.clear();
	count = 0;
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char what[10] ;



struct use {
	int num ;
	char Id[10] ;
	float weights ;
	int length ;
	bool can ;
};

vector<use> walked ;
vector<use> Nwalked ;
use take ; 


void copy() {  // 把所有相關的學號設丟到未走訪的vector 
	int a = 0 ;
	int run1 = 0 ;
	int run2 = 0 ;
	while ( a < connect.size() ){
		strcpy( take.Id, connect[a].sId );
		take.weights = 0 ;
		Nwalked.push_back( take ) ;
		a++ ;	
	}
	
	
	while (run1 < Nwalked.size() ){
		while ( run2 < big.size() ){
			if (strcmp( Nwalked[run1].Id , big[run2].Id1 ) == 0 ) {
				Nwalked[run1].num = big[run2].num ;
			}
			
			
			run2 ++ ;
	
		}
		run1 ++ ;
		run2 = 0 ;
	}
	
	
}

void clean(){ // 把全部設定為未visited 
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




void deleted( use &which ){ //將學號從未走訪的vector中刪除 
	
	int i = 0 ;
	while ( i < Nwalked.size() ){
		if ( strcmp( which.Id, Nwalked[i].Id ) == 0 ){
			Nwalked.erase( Nwalked.begin() + i ) ;
		}
		
		i++ ; 
	}
}


void BuildDis( char origin[10], string filenum ){ //建立Dis檔 
	ofstream filedis;
	string filename = "pairs";
	filename = filename+ filenum + ".dis";
	filedis.open(filename.c_str() ,ios_base::app);


	int i = 0 ; 
	int j = 0 ; 
	int node = 0 ;

	filedis << "origin : " << origin << endl ;
	while ( i < walked.size()){
		filedis << "(" << walked[i].num << ")" <<"   " << walked[i].Id << "   "<< walked[i].weights << "   ";
		
			if ( (i+1) % 5 == 0 ){
				filedis << endl ; 
			}		
		
		i++ ;
	}
	
	
	filedis << '\n'  << '\n' << '\n'<< endl ;
	filedis.close() ;
	
}

int findsmallest(){ // 尋找接下來要最短的距離 

	int i = 0 ;
	int run1 = 0 ;
	int run2 = 0 ; 
	use temp  ;
	while ( run1 < Nwalked.size() ){
		while ( run2< Nwalked.size()){
			if ( Nwalked[run1].weights >= Nwalked[run2].weights ){ //把權重大或結點多的往後搬 
				if ( Nwalked[run1].weights == Nwalked[run2].weights ){ //若權重一樣 
					if ( Nwalked[run1].length > Nwalked[run2].length ){ //把走訪節點少的放到前面 
						
						//交換 
						temp.weights = Nwalked[run1].weights ;
						strcpy(temp.Id, Nwalked[run1].Id );
						temp.can = Nwalked[run1].can;
						temp.num = Nwalked[run1].num ;
						temp.length = Nwalked[run1].length ;
				
				
						Nwalked[run1].weights = Nwalked[run2].weights ;
						strcpy( Nwalked[run1].Id ,Nwalked[run2].Id) ;
						Nwalked[run1].can =Nwalked[run2].can ;
						Nwalked[run1].num = Nwalked[run2].num ;
						Nwalked[run1].length = Nwalked[run2].length ;
				
						Nwalked[run2].weights = temp.weights ;
						strcpy( Nwalked[run2].Id, temp.Id ) ;
						Nwalked[run2].can = temp.can ; 
						Nwalked[run2].num = temp.num ;
						Nwalked[run2].length = temp.length ;
						
					}			
				} // if 
				else{  //權重大往後搬 
					temp.weights = Nwalked[run1].weights ;
					strcpy(temp.Id, Nwalked[run1].Id );
					temp.can = Nwalked[run1].can;
					temp.num = Nwalked[run1].num ;
					temp.length = Nwalked[run1].length ;
				
				
					Nwalked[run1].weights = Nwalked[run2].weights ;
					strcpy( Nwalked[run1].Id ,Nwalked[run2].Id) ;
					Nwalked[run1].can =Nwalked[run2].can ;
					Nwalked[run1].num = Nwalked[run2].num ;
					Nwalked[run1].length = Nwalked[run2].length ;
				
					Nwalked[run2].weights = temp.weights ;
					strcpy( Nwalked[run2].Id, temp.Id ) ;
					Nwalked[run2].can = temp.can ; 
					Nwalked[run2].num = temp.num ;
					Nwalked[run2].length = temp.length ;
				}// else
				
			}
			
			run2 ++ ;
		}
		
		run1++ ;
		run2 = run1 + 1 ;
	}	
	
	while ( i < Nwalked.size()){  //回傳已走訪的點中最小的一個節點的位置 
		
		if ( Nwalked[i].can){
			return i ;
		} // if
		
		i++ ; 
	} // while
	
	
}

void re() {   // 輸出時照著流水編號排大小 
	int run1 = 0 ; 
	int run2 = 1 ; 
	use temp ; 
	while ( run1 < walked.size() ){
		while ( run2 < walked.size() ){
			if ( walked[run1].num > walked[run2].num ){
				
					temp.weights = walked[run1].weights ;
					strcpy(temp.Id, walked[run1].Id );
					temp.can = walked[run1].can;
					temp.num = walked[run1].num ;
					temp.length = walked[run1].length ;
				
				
					walked[run1].weights = walked[run2].weights ;
					strcpy( walked[run1].Id ,walked[run2].Id) ;
					walked[run1].can =walked[run2].can ;
					walked[run1].num = walked[run2].num ;
					walked[run1].length = walked[run2].length ;
				
					walked[run2].weights = temp.weights ;
					strcpy( walked[run2].Id, temp.Id ) ;
					walked[run2].can = temp.can ; 
					walked[run2].num = temp.num ;
					walked[run2].length = temp.length ;
				
				
			}
			run2 ++ ;
		}
		run1++ ;
		run2 = run1 + 1   ;
	}
}

void Do4( char what[10], string filenum ){
	char remember[10] ;
	int k = 0 ; 
	int l = 0 ;
	strcpy(take.Id , what) ;
	strcpy( remember, what ) ;
	
	while ( k < big.size() ){
		if ( strcmp(big[k].Id1, take.Id  ) == 0 ) {
			take.num = big[k].num ; 
		}
		
		k++ ; 
	}
	
	while ( l < Nwalked.size() ){
		Nwalked[l].length = 0 ;
		l++ ;
	}
	
	
	

	take.weights = 0 ;
	take.can = true ;
	
	

	deleted( take ) ;
	
	int run1 = 0 ; 
	int run2 = 0 ; 
	int run3 = 0 ;
	float now = 0 ; //計算走到目前為止的權重 
	int howlong  = 0 ; // 計算走了幾個節點 
	
	while ( !Nwalked.empty() ){
		
		while( run1 < big.size() ) {
			
			if ( strcmp( what, big[run1].Id1 ) == 0 ) {
				
				while ( run2 < big[run1].small.size() ){
					
					while ( run3 < Nwalked.size() ){
				
						if ( strcmp( big[run1].small[run2].Id2, Nwalked[run3].Id) == 0 ){  
 
							if ( !Nwalked[run3].can ){  //若這個節點還未走訪 
								Nwalked[run3].weights = now +  big[run1].small[run2].weights ; // 計算走到下個節點後的總權重 
								Nwalked[run3].can = true ;  //把這個節點設為已走訪 
								Nwalked[run3].length = howlong + 1 ; // 走的節點+1 
							}
							else{
								if ( now +  big[run1].small[run2].weights < Nwalked[run3].weights  ){ //找到比之前更短的距離，取代他 
									Nwalked[run3].weights = now + big[run1].small[run2].weights ;
									Nwalked[run3].length  = howlong  + 1 ;
								}

							}
						} // if 
						
												
						run3 ++ ;
					} // while
					
					
					
					
					run2 ++ ;
					run3 = 0 ;
				}  // while
				
				
			} //if
		
			run1 ++ ;
			run2 = 0 ;
		} //while 
			
			
		run1 = 0 ;
		run2 = 0 ;
		run3 = 0 ;
		
		//尋找下個最接近的點 
		howlong = Nwalked[findsmallest()].length  ;
		
		strcpy(what, Nwalked[findsmallest()].Id ) ;

		strcpy(take.Id, Nwalked[findsmallest()].Id ) ;
		take.length = Nwalked[findsmallest()].length ;
		take.weights = Nwalked[findsmallest()].weights ;
		take.num = Nwalked[findsmallest()].num ;
		take.can =  Nwalked[findsmallest()].can ;
		
		now =  take.weights ;		
		walked.push_back( take) ;  // 把下個最近的點丟進已走訪 
		deleted( take ) ;   // 將下個最近的點從未走訪刪掉 

		// 往下個最近的點走 
	
		
	} // while
	
	
	
	re() ;
	BuildDis( remember, filenum ) ;
	
	
} // Do4()

bool mission4( string filenum ){
	
	bool have = false ;
	bool done = false ;
	string read ; 
	int i = 0 ; 
	int k = 0 ;
	cout << endl << endl << endl << endl ;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
	cout << "Mission 2: Shortest Distances" << endl ;	
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;


	
	while ( !done){
		i = 0 ;
		k = 0 ;
		have = false ; 
		while ( k < big.size() ){
			
			cout << big[k].Id1 << "   " ;
			
			if ((k+1)%5==0){
				cout << endl ;
			}
			k++ ;
		}
		
		cout << endl  << "Input a student id from the above:" << endl  ;
		cin >> what ;
		
		while ( i < big.size() ){
			if ( strcmp(big[i].Id1, what ) == 0 ) {
				have = true ; 
			}
			i++ ; 
		} // while 
		
 
		if ( have ){
			cout << endl << endl ;
			clean() ;
			DFS( what, 0, filenum ) ; //尋找同組別的還有哪些  
			copy() ; 
			Do4( what, filenum ) ;
			cout << "~~~ Shortest Distances are computed! ~~~" ;
			cout << endl << endl ;
			cout << "[0]Quit or [Any other key]continue?" << endl ; 
			cin >> read ;
			if ( read == "0" ){
				done = true ;
			}	// if		
		}
		else{
			cout << endl << what << "does not exist!!!" << endl  ;
			cout << "[0]Quit or [Any other key]continue?" << endl ;
			cin >> read ;
			if ( read == "0" ){
				done = true ;
				break ;
			}	// if
		}
		
	} // while 
	
	
	return true ;
	
	
}




void seee(){
	int i = 0 ; 
	int run1 = 0 ;
	int run2 = 0 ; 
	use temp  ;
	while ( run1 < walked.size() ){
		while ( run2< walked.size()){
			if ( walked[run1].weights < walked[run2].weights ){

					temp.weights = Nwalked[run1].weights ;
					strcpy(temp.Id, Nwalked[run1].Id );
					temp.can = Nwalked[run1].can;
					temp.num = Nwalked[run1].num ;
					temp.length = Nwalked[run1].length ;
				
				
					Nwalked[run1].weights = Nwalked[run2].weights ;
					strcpy( Nwalked[run1].Id ,Nwalked[run2].Id) ;
					Nwalked[run1].can =Nwalked[run2].can ;
					Nwalked[run1].num = Nwalked[run2].num ;
					Nwalked[run1].length = Nwalked[run2].length ;
				
					Nwalked[run2].weights = temp.weights ;
					strcpy( Nwalked[run2].Id, temp.Id ) ;
					Nwalked[run2].can = temp.can ; 
					Nwalked[run2].num = temp.num ;
					Nwalked[run2].length = temp.length ;

			}
			
			run2 ++ ;
		}
		
		run1++ ;
		run2 = run1 + 1 ;
	}	
	
	cout << endl << endl << endl ;

	while ( i < walked.size() ){
		
		cout << "VertexSet <--" << walked[i].num << ", min. distance = " << walked[i].weights << endl << endl ;
		
		
		i++ ;
	}
	
	
}



 




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
	

	string filenum = "-1";
	cout << "***********************************" << endl ;
	cout << " On-machine Exercise              *" << endl ;
	cout << "Mission 1: Minimum Spanning Tree *" << endl ;
	cout << "Mission 2: Shortest Distances    *" << endl ;
	cout << "***********************************" << endl ;
	cout << "Input the file name (e.g., 601, 602): [0]Quit" << endl ;	
	cin >> filenum ; 
	
	while (filenum != "0" ){ 
	
		if ( open( filenum) ){

			Do() ;  
			arrange() ;
			Build( filenum ) ; 
			print2() ;
			cout<< endl ;
			cout << "~~~ Connected Components ~~~"<< endl;
			Traversals(filenum);
			system("pause") ;
			while ( !mission4( filenum )){
				seee() ;
				
			}  // while
			
			cout << endl <<"[0]Quit or [Any other]continue?" << endl;
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
		walked.clear() ;
		Nwalked.clear()	;
	}
} 
