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
	bool fine ;  
	long long int key ;
	char id[10] ;
	char name[10] ;
	float score ;
};

vector <Hash> chart ;
vector <Data> datavec;

void BuildChart( long long int key, char tempid[10], char readname[10], float ave) ;
void print2( int finalsize) ;
int Findprime( int a ) ;

void Build(string filenum){ // 輸出bin檔 
	ofstream filebin;
	string filename = "input";
	filename = filename+ filenum + ".bin";
	filebin.open(filename.c_str(), ios::out|ios::binary); // 開檔 

	for( int i = 0; i < datavec.size() ; i++ ){ // 以一個struct 32位元 寫入bin檔 

		filebin.write((char*)& datavec[i],sizeof(Data));
		
	}

	
}


bool InputFile(string filenum){ // Txt開檔 
	bool quit = false;
	ifstream fin;
	string filename = "input";
	filename = filename + filenum + ".txt";
	fin.open( filename.c_str());
	while( !fin ){ 
		cout << "### " << filename << " does not exist! ###"<< endl;
		cout << "Input the file name <e.g. , 401,402 >: [0]Quit" << endl;
	
		getline(cin,filenum);
		if( filenum == "0"){
			quit = true;
			break;
		}
		string filename = "input";
		filename = filename + filenum + ".txt";
		fin.open( filename.c_str());
	}
	if(!quit){
		char line[255];
	Data temp;

	memset(temp.id,'\0',10);
	memset(temp.name,'\0',10);
	memset(temp.score,'\0',6);
	temp.average = 0;
	int i = 0,j = 0, l = 0,num = 0;
	
	while( fin.getline( line,255,'\n')){ // 取一行 
		j = 0;
		l = 0;
		
		while(line[l] != '\t') { // 學號 
			temp.id[j] = line[l]; 
			j++;
			l++;
		}


		l++;
		j = 0;
		while( line[l] != '\t'){ // 名子 
			temp.name[j] = line[l];
			j++;
			l++;
		}

		l++;

		j = 0;


		while( j < 6 ){ // 六個成績 
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
			while( line[l] != '.' && line[l] != '\0'){ // 取平均成績的整數位 
				numf = numf*10 + ((float) line[l] - 48 );
				l++; 
			}

			int count = 0;
			if( line[l] != '\0' ){
				for( l++ ; line[l] != '\0' ; l++) { // 取平均成績的小數位，並與整數位合併 
				count++;
				numf =  numf*10 + (float)line[l] - 48 ;
				}
			}

			
			for( ;count > 0; count--) numf = numf/10;
			temp.average = numf;
		

		datavec.push_back(temp);// 放入vector中 
		i++;
		

		}
	}
	
	return !quit;
}



vector<Data> get ;








void open2(string filenum){
	ifstream filebin;
	string filename = "input";
	filename = filename+ filenum + ".bin";
	filebin.open(filename.c_str(), ios::in|ios::binary);	
	Data getdata ; 
		for ( int i = 0 ; filebin ; i++ ) {


			filebin.read((char*)& getdata, sizeof(Data));

			get.push_back(getdata) ;

		}

	filebin.close();
	
	get.pop_back() ;


}

void Do( int finalsize){
	long long int total = 1 ;
	long long int k = 1 ;
	long long int key = 0 ;
	long long int final = 0 ; 
	int count = 0 ;
	int where = 0 ; 
	char how ; 

	while ( where < get.size() ){
	total = 1 ;
	count = 0 ;
	
   	while ( count <= 9 ){   // 讀學號 
		how  = 	get[where].id[count] ;
		if ( how != '\0'){
			k = how  ; 
			total = total * k ; // 用total 計算相乘的值 
		} // if  
		count ++ ;

	}

	final = total % finalsize ;  // total 除以雜湊表大小 算出應該存放的位置 
	key = final ;  
	

		BuildChart( key, get[where].id, get[where].name, get[where].average ) ;  // 將資料存到雜湊表中 
		where++ ;
	}
	
	
}

void PrintData(){ // 印出datavec的資料 
	for( int i = 0; i < datavec.size() ; i++){
		cout<< "[" << i+1 << "]";
		cout << datavec[i].id <<  "," <<'\0';
		cout << datavec[i].name << ','<<'\t';
		for( int j = 0;j <6 ; j++ )cout << (int) datavec[i].score[j] << '\t';
		cout << datavec[i].average << endl;
	}
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
void Build2(string filenum, int finalsize){
	ofstream filetab;
	string filename = "input";
	filename = filename+ filenum + ".tab";
	filetab.open(filename.c_str(), ios::out|ios::binary);
	int i = 0 ;
	filetab << " --- Hash Table --- by Linear probing" << endl ;
	while ( i < finalsize ){
		filetab << "[" << i << "] ";
		if ( chart[i].fine){
			filetab << chart[i].key << ", ";
			filetab << chart[i].id << ", ";
			filetab << chart[i].name << ", " ;
			filetab << chart[i].score << endl ;
		} // if 
		else {
			filetab << endl ;
		}
		i++ ;
	}
	filetab.close() ;
}


void open( string filenum, int size, int finalsize){  // 讀取bin檔 

	long long int key ; 
	char tempid[10] ;  // 學號 
	char tempname[10] ;  // 名字 
	char readname[10] ;   
	long long int total = 1 ; 
	long long int k = 0 ;
	long long int final = 0 ;
	float average ;
	char num[3] ;
	int six = 1 ;
	int howmuch = 0 ; 
	char noneed ; 
	int count = 0 ; 
	ifstream fin;
	string filename = "input";
	filename = filename + filenum + ".bin";
	fin.open( filename.c_str(),ios::in|ios::binary);
    char how ;    
    char trash ;  // 用來讀不需要的欄位 
    while ( howmuch < size ){
    	count = 0 ;
    	total = 1 ;
    	k = 0 ;
   	
   		while ( count <= 9 ){   // 讀學號 
			fin.get( how) ;
			tempid[count] = how ; 
			if ( how != '\0'){
				k = how  ; 
				total = total * k ; // 用total 計算相乘的值 
			} // if  
			count ++ ;

		}

		final = total % finalsize ;  // total 除以雜湊表大小 算出應該存放的位置 
		key = final ;  
	
		fin.read( readname, 10) ; // 讀入學生名字 
	
		six = 1 ; 
		
		while ( six <= 6){  // 讀掉任務二不需要的成績 
			fin.get(noneed) ;
			six++ ;
		}
  		fin.read(num, 6 ) ;      // 讀取平均值(還沒搞定) 
	
 		int k = 0 ;
 		int run = 0 ;
 		while ( run <6 ){
 			k = (float)num[run] ;
			run++ ;	
		}
 


		
			

		howmuch++ ; 
		
		}
		
		fin.close();
	
}

void BuildChart( long long int key, char tempid[10],  char readname[10 ], float ave ){  // 建立雜湊表 
	
	
	long long int where = 0 ; // 現在位置 
	int run = 0 ;
	bool done = false ;  
	where = key ;
	while ( !done ) {  
		run = 0 ;
		if (chart[where].fine == false ){ //若該位置沒檔案 
			chart[where].key = key ;   //將該資料存入 
			while ( run < 10){           //存入學號 
				chart[where].id[run] = tempid[run] ; 
				run++ ; 
			} // while 
			run = 0 ;
			while ( run < 10){        //存入名稱 
				chart[where].name[run] = readname[run] ; 
				run++ ; 
			} // while
			
			chart[where].score = ave ;
			chart[where].fine = true ;  
			done = true ; 
		} // if 
		else{   // 該位置已有東西    
			if ( where + 1 >= chart.size())  {  // 已經在最後一欄，回到0 
				where = 0 ;
			} // if 
			else{     // 往下一個位置看 
				where ++ ; 
			} 
		} // else 
	} // while 
	
	
}

void print2( int finalsize ){  //測試用 
	int i = 0 ;
	while ( i < finalsize ){
		cout << "[" << i << "]"  ;
		if ( chart[i].fine){
			cout << chart[i].key << ", ";
			cout << chart[i].id << ", ";
			cout << chart[i].name << ", "  ;
			cout << chart[i].score << endl ;
		} // if 
		else {
			cout << endl;
		}
		i++ ;
	}
}




float unsu( int finalsize){  // unsuccessful search
	float total = 0 ;
	float count1 = 0 ;
	float count2 = 0 ;
	float where = 0 ;
	while ( count1 < chart.size() ){
		where = count1 ;
		count2 = 0 ;
		while( chart[where].fine ){
			if ( where == chart.size() - 1){
				where = 0 ;
				count2++ ;
			}
			else{
				count2++ ;
				where++ ;
			}
		
		}
		total = total + count2 ;
		count1++ ;
	}
	
	
	return total/finalsize;
	
}


float su( int size, int finalsize){ // unsuccessful search
	float total = 0 ;
	float count = 0 ;
	float where = 0 ;
	while ( where < finalsize ){
		if ( chart[where].fine){
			if (where < chart[where].key){
				count = where + finalsize - chart[where].key + 1 ;
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


int main(){
	bool ok = false ; 
	string filenum = "-1";
	bool intput = false;
	while (filenum != "0" ){
		cout << "********************************************" << endl;
		cout << "On-machine Exercise                        *" << endl;
		cout << "Mission 1: Make binary file                *" << endl;
		cout << "Mission 2: Hashing with Linear probing     *" << endl;
		cout << "********************************************" << endl;
		cout<< "######################################################" << endl;
		cout<< " Mission 1: Transform a text file into a binary file " << endl;
		cout<< "######################################################" << endl;
		cout << "Input the file name <e.g. , 401,402 >: [0]Quit" << endl;
		getline(cin,filenum);
		intput = InputFile(filenum);
		if( !intput ) break;
		cout << "~~~~A binary file has been successfully created!~~~~"<< endl;
		PrintData(); // 印datavec資料 
		Build(filenum); // 建Bin檔 
		cout << endl << endl ;
		// mission two	
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "Mission 2: Build a hash table by linear probing" << endl ;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << endl ; 
		cout << "~~ The hash table has been successfully created! ~~ " << endl << endl ; 
		int size = 0 ;
		int finalsize = 0;
		open2( filenum) ;
		size = get.size() ;
		finalsize = size*1.2 ;
		finalsize = Findprime( finalsize) ;

		chart.resize(finalsize) ; 

		Do( finalsize ) ; 


		cout << "unsuccessful search: " << unsu(finalsize) << " comparisons on average" << endl << endl ;
		cout << "successful search: " << su(size, finalsize) << " comparisons on average" << endl ;
		Build2( filenum, finalsize) ;
		cout << "[0]Quit or [Any other]continue?" << endl;
		getline(cin,filenum);
		
		datavec.clear();
		chart.clear();
		get.clear();
	}
	

	


}



