#include <iostream>
#include <fstream>
#include <vector>
#include<cstring>
#include<map>
#include <HashTable.h>

using namespace __gnu_cxx;
using namespace std;



struct Data{
	char id[10];
	char name[10];
	unsigned char score[6] ;
	float average;	
};

struct Hash{
	int key ;
	char id[10] ;
	char name[10] ;
	float score ;
};


vector <Data> datavec;
vector <Data> binvec;
void BuildChart( long long int key, char tempid[10], char tempname[10], char readname[10]) ;
void print2( int finalsize) ;

void Build(string filenum){
	ofstream filebin;
	string filename = "input";
	filename = filename+ filenum + ".bin";
	filebin.open(filename.c_str(), ios::out|ios::binary);

	for( int i = 0; i < datavec.size() ; i++ ){
		filebin.write((char*)& datavec[i],sizeof(Data));
	}

	filebin.close();
}


void InputFile(string filenum){
	ifstream fin;
	string filename = "input";
	filename = filename + filenum + ".txt";
	fin.open( filename.c_str());
		char line[255];
	Data temp;

	memset(temp.id,'\0',10);
	memset(temp.name,'\0',10);
	memset(temp.score,'\0',6);
	temp.average = 0;
	int i = 0,j = 0, l = 0,num = 0;
	
	while( fin.getline( line,255,'\n')){
		j = 0;
		l = 0;
		memset(temp.id,'\0',10);
		memset(temp.name,'\0',10);
		memset(temp.score,'\0',6);
		temp.average = 0;
		
		while(line[l] != '\t') {
			temp.id[j] = line[l]; 
			j++;
			l++;
		}


		l++;
		j = 0;
		while( line[l] != '\t'){
			temp.name[j] = line[l];
			j++;
			l++;
		}

		l++;

		j = 0;


		while( j < 6 ){
			num = 0;
			
			while( line[l] != '\t' ){
				num = num*10 + ((int) line[l] - 48 );
				l++; 
			}

			temp.score[j] = (unsigned char) num;

			j++;
			l++;
		}
		
		float numf = 0;
			while( line[l] != '.' && line[l] != '\0'){
				numf = numf*10 + ((float) line[l] - 48 );
				l++; 
			}

			int count = 0;
			if( line[l] != '\0' ){
				for( l++ ; line[l] != '\0' ; l++) {
				count++;
				numf =  numf*10 + (float)line[l] - 48 ;
				}
			}

			
			for( ;count > 0; count--) numf = numf/10;
			temp.average = numf;
		

		datavec.push_back(temp);
		i++;
		
	}	
	
	fin.close();
}
void PrintData(){
	for( int i = 0; i < datavec.size() ; i++){
		cout<< "[" << i+1 << "]";
		cout << datavec[i].id <<  "," <<'\0';
		cout << datavec[i].name << ','<<'\t';
		for( int j = 0;j <6 ; j++ )cout << (int)datavec[i].score[j] << '\t';
		cout << datavec[i].average << endl;
	}
}

void ReadInBin(string filenum){
	ifstream readbin;
	string filename = "input";
	filename = filename + filenum + ".bin";
	readbin.open( filename.c_str(),ios::in| ios::binary);
	for( int i = 0; readbin ;i++){
		Data temp;
		memset(temp.id,'\0',10);
		memset(temp.name,'\0',10);
		memset(temp.score,'\0',6);
		temp.average = 0;
		binvec.push_back(temp);
		readbin.read((char*)& binvec[i],sizeof(Data));
	}

 
	readbin.close();
}
int Findprime( int a ) {   //找質數 
	int b = 2 ;  
	bool get = false ; // 判斷是否已經找到質數
	while ( !get){
		while ( b <= a ){
			if ( a%b == 0 ){
				if ( a == b){
					get = true ; 
					return a ;
				} 
				else{
					break ;
				}

			}
			b++ ;
		
		} 
	a++ ;	
	b = 2 ; 
	}
}



int CountHashKey( char id[10], int finalsize){
	long long int key = 1;
	for( int i = 0; i < 8 ; i++){
		key = key* (int) id[i] ;
	}
	key = key%finalsize;
	
	return (int)key;
}

bool EmptyKey( Hash temp){
	if( temp.id[0] == '\0') return true; // 此櫃子沒東西 
	else return false;
}



void BuildHashTable( int finalsize, string filenum){
	Hash chart[finalsize];
	int i = 0;
	int j =0;
	for( i = 0; i < finalsize ; i++ )memset(chart[i].id,'\0',10 );
	for( i = 0; i < binvec.size() ; i++ ){

		if( EmptyKey( chart[CountHashKey( binvec[i].id,finalsize)] ) ) {
			chart[CountHashKey( binvec[i].id,finalsize)].key = CountHashKey( binvec[i].id,finalsize);
			strcpy(chart[CountHashKey( binvec[i].id,finalsize)].id,binvec[i].id);
			strcpy(chart[CountHashKey( binvec[i].id,finalsize)].name ,binvec[i].name);
			chart[CountHashKey( binvec[i].id,finalsize)].score = binvec[i].average;
		}
		else{ // 往下找空的 
			for( j = CountHashKey( binvec[i].id,finalsize)+1; j < finalsize ; j++){
				if( j == finalsize -1 && ! EmptyKey( chart[j] ) ) j = 0; // 走到底都沒有空格 從頭開始找 
				else if( EmptyKey( chart[j] ) && j < finalsize ) break;
			}
			chart[j].key = CountHashKey( binvec[i].id,finalsize);
			strcpy(chart[j].id,binvec[i].id);
			strcpy(chart[j].name ,binvec[i].name);
			chart[j].score = binvec[i].average;
		}
	}
	
	ofstream filetab;
	string filename = "inpet";
	filename = filename+ filenum + ".tab";
	filetab.open(filename.c_str(), ios::out|ios::binary);
	filetab << " --- Hash Table --- by Linear probing" << endl ;
	for( i = 0 ; i < finalsize ; i++ ){
		filetab << "[ " << i << "]";  
		if( !EmptyKey( chart[i] ))filetab << chart[i].key << "," << chart[i].id << "," <<chart[i].name << "," << chart[i].score;
		filetab << '\n';
	}

	filetab.close() ;
	
	
	
	
	float count = 0;
	
	for( i = 0; i < finalsize ; i++){
		for( j = i ; j < finalsize; j++ ){
			if( EmptyKey( chart[j] ) ) break;
						count++;
		}
	}
	count = count/ (float) finalsize;
	
	cout << "unsuccessful search: " <<count<< " comparisons on average" << endl << endl ;
	
	count = 0;
	
	for( i = 0; i < finalsize ; i++){
		if(!EmptyKey( chart[i] )){
			if( chart[i].key < i ){ // 被擠下來的 
				count = count + i-chart[i].key+1;
			}
			else if( chart[i].key == i  )count++;
			else if( chart[i].key > i  )count = finalsize - chart[i].key + i+1 +count;
			
		}

	}
	count = count/ (float) binvec.size();
	
	cout << "successful search: " <<count<< " comparisons on average" << endl << endl ;
	
}

/*
float su( int size, int finalsize){ // unsuccessful search
	float total = 0 ;
	float count = 0 ;
	float where = 0 ;
	while ( where < finalsize ){
		if ( chart[where].fine){
			if (where < chart[where].key){
				count = where + 127 - chart[where].key + 1 ;
				total = total + count ;
			}
			else{
				count = where - chart[where].key + 1 ;
				total = total + count ;
			}
	}
		where++ ;
		
	}
	
	return total/size ;
	
}



*/
int main(){
	int size = 0 ;
	int finalsize ;
	string filenum;
	getline(cin,filenum);
	InputFile(filenum);
	PrintData();
	Build(filenum);
	size = datavec.size() ;
	finalsize = size*1.2 ;
	finalsize = Findprime( finalsize) ;
		ReadInBin( filenum);
    BuildHashTable( finalsize,filenum) ;
	cout << endl << endl ;
	// mission two	
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "Mission 2: Build a hash table by linear probing" << endl ;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << endl ; 
	cout << "~~ The hash table has been successfully created! ~~ " << endl << endl ; 


	//cout << "unsuccessful search: " << unsu(finalsize) << " comparisons on average" << endl << endl ;
	//cout << "successful search: " << su(size, finalsize) << " comparisons on average" << endl ;
	//print2( finalsize ) ;
//Build2( filenum, finalsize) ;
  

}



