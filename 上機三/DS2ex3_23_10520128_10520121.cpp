// 第23組 
// 電資二 林佳穎 10520128 
// 電資二 杜欣洋 10520121 
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
bool set = false; // 是否讀黨完成
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
void Print(){ // 印符合使用者輸入條件的所有資料 
	cout << "*** There are " << datavec.size() << " matched records, listed as below:" << endl;
	for( int i = 0; i < datavec.size() ;i++ ) {
		cout << "[" << datavec[i].num << "]" << datavec[i].school;
		cout << datavec[i].department << ',';
		cout << datavec[i].day << ',';
		cout << datavec[i].level << ',';
		cout << datavec[i].graduate << endl;
	}
}

void ReadFileAndBuildDatavec(){ // 讀黨 並建立所有讀入資料的vector 資料庫 
	Data cur;
	bool deletebool = false; // 畢業生人數是否缺項 
	char cstr[255];
	string str = "0", cut = "0";
	int pre = 0, post = 0, count = 1;
	char c;
	fin.open( fileName.c_str() );
	if( !fin ) cout << "### " << fileName << " does not exist! ###"<< endl;
	else{
		set = true;
		while( str != "體系別" ) fin >> str;
		fin >> c; 
		while( fin.getline( cstr ,255 , '\n') ) {
			str.assign(cstr);
			deletebool = false;
			while( pre < 255 && count < 12 ){
				post = str.find_first_of( '\t', pre); // 找出'\t'所在的index 
				cut = str.substr(pre,post-pre); // 從index pre開始取post-pre個字元assign 給string cut
				if( count == 2)cur.school = cut;
				if( count == 4)cur.department = cut;
				if( count == 5)cur.day = cut;
				if( count == 6)cur.level = cut;
				if( count == 9){
					if( cut != "" )cur.graduate = atoi( cut.c_str() ); // atoi 為 char *c 轉 int ; str.c_str() 為 string 轉 char *c 
					else deletebool = true;
				} 
				count++;
				pre  = post+1;
			}
		
			count = 1;
			strcpy( cstr, "\0");
			if(!deletebool)datavec.push_back( cur ) ; // 如果畢業生人數沒有缺項 就丟入資料VECTOR中 
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
		
	DatavecPtr New( Data data){ // 建構一個 指標指向一個vector內有一個資料 
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
	
	int Height(DatavecPtr head, DatavecPtr item){ // 算item所在樹高 
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
	
	void PrintRoot(){  //印出根的資料 
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
	
	void Print( DatavecPtr head){ // 印出node&所在樹高 
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
	
	void Sort( DatavecPtr & cur ){ // Key的排序 
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
	
	DatavecPtr FindParent(DatavecPtr p,DatavecPtr child){ // 回傳child 的父親 
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
	
	void Split( DatavecPtr  cur, DatavecPtr  parent, int jump , DatavecPtr & A){ // 分裂 三key已排好序

		DatavecPtr temp = new vector<Data>;
		DatavecPtr temp2 = new vector<Data>;

		if ( cur->size() == 3 ){ // 需要分裂 
			if( parent == cur ) {// 為樹根  
				// temp為新的樹根 
				temp = New((*cur)[1]); 
				temp2 = New((*cur)[2]);	  
				cur->erase(cur->begin()+1);
				cur->erase(cur->begin()+2);

				(*temp)[0].p1 = cur;
				(*temp)[0].p2 = temp2;
				
				// 一開始 全部只有三筆資料時  
					if( jump == 1 ){ // 由左邊分裂上來時 
						(*temp2)[0].p1 = (*cur)[0].p2;
						(*temp2)[0].p2 = (*cur)[0].p3;
						(*cur)[0].p2 = NULL;
						(*cur)[0].p3 = NULL;
						

					}
					if( jump == 2){  // 由中間分裂上來時 
						(*temp2)[0].p2 = (*cur)[0].p3;
						(*cur)[0].p3 = NULL;
						
						A = temp2;
						
					}
					if( jump == 3 ){// 由右邊分裂上來時 
						
						(*temp2)[0].p1 = (*cur)[0].p3;
						(*cur)[0].p3 = NULL;
						A = temp2;

					}
					
					root =temp; // 一開始 全部只有三筆資料時 只需要此設定 
										

			}
			else{
				if( parent->size() == 1 ){

					parent->push_back((*cur)[1]); // 中間值丟上去 
					Sort( parent ); // 排序 確保遞迴分裂會成功 

					cur->erase(cur->begin()+1);
					temp = New((*cur)[1]);  // 大的Key 獨立出來 
					cur->erase(cur->begin()+1); 
					if(cur == (*parent)[0].p1){ // 左分裂 
						(*parent)[0].p3 = (*parent)[0].p2;
						(*parent)[0].p2 = temp;
					}
					if(cur == (*parent)[0].p2){ // 右分裂  
						(*parent)[0].p3 = temp;
					}

					A = temp;

				}
				else{ // parent->size() == 2
					// jump 設定為從哪裡來(回) 
					if( cur == (*parent)[0].p1) jump = 1;  
					else if( cur == (*parent)[0].p2) jump = 2;
					else if ( cur == (*parent)[0].p3) jump = 3;

					parent->push_back((*cur)[1]); // 中間Key往上丟 
					Sort( parent ); 
					cur->erase(cur->begin()+1); // 刪掉中間Key 

					temp = cur; // temp 最小的Key   
					temp2 = New((*cur)[1]); // temp 最大的Key 
					cur->erase(cur->begin()+1);  
					
					Split( parent, FindParent(root,parent),jump,A); //遞迴 往上分裂 
					
					
					// 分裂後得到新的父節點 A
					// 依jump所記錄的方向 連接A或原本的parent
					// A 也要設定如果下面還有分裂的話要接哪個 (A設為"新"分裂出來的) 
					if(jump == 1 ){  
						if( A == NULL){ // root 三分裂時 
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
	
	void Build(){ // 建立2-3Tree 
		root = new vector<Data>;
		root = New(datavec[0]);
		datavec.erase(datavec.begin());
		while( datavec.size() != 0){ // 沒資料(全部都建到樹裡了)及結束 

			Insert( root, datavec[0] );
			datavec.erase(datavec.begin());
		}

	}
	
	void Insert(DatavecPtr cur, Data item){ // 找到該資料所屬的樹葉 並放入樹中 
		
		DatavecPtr a = NULL;
		if ( (*cur)[0].p1 == NULL && (*cur)[0].p2 == NULL && (*cur)[0].p3 == NULL ) {// 樹葉
			if( (*cur)[0].school.compare(item.school )== 0 ) samevec.push_back(item);
			else if( cur->size() == 2 && (*cur)[1].school.compare(item.school ) == 0 ) samevec.push_back(item);
			else cur->push_back(item);
				Sort( cur );
				DatavecPtr parent = FindParent(root,cur);
				if ( cur->size() == 3 )Split(cur,parent,0,a);// 如過放入後KEY為三 則分裂 		
		}
		//沒到樹葉 繼續走訪 一樣的就放入samevec中 
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
	
	void search( string a ){ // 任務二搜尋用 
		bool finish = false ;   
		one = false ;  // 用來判斷該節點是否有兩筆資料 
		int i = 0 ;
		DatavecPtr find = new vector<Data> ;
		vector<Data> *point = NULL ;
		find = root ;
		while ( !finish){
		if ( (*find)[0].p3 == NULL) { // 若第三個pointer = NULL ，有兩種可能 1.該節點只有一筆資料 2.該節點有兩筆資料、但是是葉子 
			if ( (*find).size() == 2 ){  // 該節點是葉子 
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
		else {  //該節點有兩筆資料 
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
			else if ( a.compare( (*find)[0].school) < 0 ){ //讀入的較小，走左邊 
				if ( (*find)[0].p1 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
					finish = true ;
					break ;
				}
				else {
					find = (*find)[0].p1 ;  
				}
				
			}
			else if ( a.compare( (*find)[1].school) > 0 ){  //讀入的較大，走右邊 
				if ( (*find)[0].p3 == NULL ){
             		cout<< a << "cannot find a match!!!" << endl ; 
             		finish = true;
             		break ;
				}
				else {
					find = (*find)[0].p3 ;  
				}
				
			}
			else {  //讀入的介於兩數中間，走中間 
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

void take( DatavecPtr k){ // 把所有資料存進final vector
	int run = 0 ;
	vector<Data> final ;
	if ( !one ){
		final.push_back( (*k)[0] ) ;
		while ( run < samevec.size() ){
			if( samevec[run].school.compare((*k)[0].school) == 0){ //把大學名稱相同的資料也存進去 
				final.push_back(samevec[run]) ;
			}
		run ++ ;
		}
	}
	else{
		final.push_back( (*k)[1] ) ;
		while ( run < samevec.size() ){
			if( samevec[run].school.compare((*k)[1].school) == 0){  //把大學名稱相同的資料也存進去  
				final.push_back(samevec[run]) ;
			}
			run ++ ;
		}		
	}

	order( final) ;
	mission2print( final) ;
}


void order ( vector<Data> &done){ // 將vinal vector 中的資料照畢業人數由大到小排
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


void mission2print( vector<Data> done ){  // 印出任務二要的東西 
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
	
	bool NumOk = false ;  // 檢查K是否在範圍內 
	bool IsZero = false ; 

	string readnum ;
	int a = 0 ;
	int k = 0 ;
	
	// 開黨 讀黨 建資料庫(vector) 
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

		Print(); // 印出所有符合的資料 	
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
			cin >> k ; //讀入使用者輸入的大學名稱 
			twothreetree->search(k) ;
	
			
			cout << "[0]Quit or [Any other]continue?" << endl;
			cin >> x ;
			if ( x == "0"){
				break ;
			}		
	}
}
