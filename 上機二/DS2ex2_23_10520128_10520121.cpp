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
bool set = false; // 是否讀黨成功
 
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



void Print(){ // 印符合使用者輸入條件的所有資料 
	cout << "*** There are " << matchvec.size() << " matched records, listed as below:" << endl;
	for( int i = 0; i < matchvec.size() ;i++ ) {
		cout << "[" << i+1 << "]" << matchvec[i].school;
		cout << matchvec[i].department << ',';
		cout << matchvec[i].day << ',';
		cout << matchvec[i].level << ',';
		cout << matchvec[i].graduate << endl;
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
				if( count == 1)cur.numofschool = cut;
				if( count == 2)cur.school = cut;
				if( count == 3)cur.numofdepartment = cut;
				if( count == 4)cur.department = cut;
				if( count == 5)cur.day = cut;
				if( count == 6)cur.level = cut;
				if( count == 7)cur.student = atoi( cut.c_str() ); // atoi 為 char *c 轉 int ; str.c_str() 為 string 轉 char *c 
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
			if(!deletebool)datavec.push_back( cur ) ; // 如果畢業生人數沒有缺項 就丟入資料VEECTOR中 
		}
	}
}

bool Include(string str1, string str2){ // str1 是否含有Str2 
	if( strstr( str1.c_str() , str2.c_str() ) != NULL)return true; // strstr( char* a, char* b) a 內有無包含b  不含為NULL 
	else return false;
}

void Search(string key,string keytype){ // match vetor資料中是否有含使用者輸入的資料
										//包含的話就不用移除, 反之則移除 

	for( int i = 0; i < matchvec.size(); ){
		
		if( key == "*" ) break;
		
		if( keytype == "學校名稱") { // 使用者搜找的類別 
			if( !Include(matchvec[i].school,key) || key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++; // 此資料使用者要得 ，不用移除 換下一個資料比較看看 
		}
		
		if( keytype == "科系名稱") {
			if( !Include(matchvec[i].department,key) || key == "") matchvec.erase(matchvec.begin()+i);
			else i++;
		}
		
		if( keytype == "日夜別") {
			if( !Include(matchvec[i].day,key)|| key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++;
		}
		
		if( keytype == "等級別") {
			if( !Include(matchvec[i].level,key)|| key == "" ) matchvec.erase(matchvec.begin()+i);
			else i++;
		}
	}
}


class MinMaxHeap{
	
	vector<Data> maxitems;
	vector<Data> minmaxheap;
	public:
		
	int Two( int n){ // return 2的N次方 
		int sum = 1 ;
		for(; n > 0 ; n--)sum = 2*sum;
		return sum;
	}
	
	int LeftBottomIndex(){ // return leftbottom 的index 
		 int level = 1;
		for(; minmaxheap.size() > Two( level)-1 ;level++);
		return Two(level-1)-1;
	}

	void Print(){ // 印出  bottom leftbottom 的編碼及資料 
		if(minmaxheap.empty()) cout << "### There is noting matched ###" << endl;
		else{
			cout << "bottom: " << '[' << minmaxheap.back().num << ']' << ' ' << minmaxheap.back().graduate << endl;
			cout << "Leftmost bottom: " << '[' << minmaxheap[LeftBottomIndex()].num << ']' << ' ' << minmaxheap[LeftBottomIndex()].graduate << endl;
		}
	}
	
	void PrintMaxItems(){ // 印出  bottom leftbottom 的編碼及資料 
		for( int i = 0; i < maxitems.size() ; i++)	cout << "Top  " << i+1 << ":  [" <<maxitems[i].num << "]"  << maxitems[i].school << maxitems[i].department << ", " <<
			  maxitems[i].day << ", " <<  maxitems[i].level << ", " <<  maxitems[i].graduate << endl; 
	}
	
	int HowBig() {  // 查看樹的大小 ， 用來檢查讀入K的時候是否超出範圍 
	  return minmaxheap.size() ;
	}

	
	
	
	
	/* debug 用 
	void PrintAll(){  
		for( int i = 0; i < minmaxheap.size() ; i++)	cout << "[" << i+1 <<"]"<<minmaxheap[i].num << ", " << minmaxheap[i].school << minmaxheap[i].department << ", " <<
			  minmaxheap[i].day << ", " <<  minmaxheap[i].level << ", " <<  minmaxheap[i].graduate << endl; 
	}
	*/
	 
	void Swap(int index, int index2){ // 父子資料(位置)交換 
		Data temp;
		temp = minmaxheap[index];
		minmaxheap[index] = minmaxheap[index2];
		minmaxheap[index2] = temp;
	}

	int Level( int  index ){ // 計算在Min層 還是 Max層 min return 0 max return 1 
		return (int)floor( log2(index+1) ) %2;
	}
	
	void ReHeapUp( int index ){ 
		if( index == 0 );
		else if( Level(index) == 0 ) {// min heap
			if( minmaxheap[index].graduate > minmaxheap[(index-1)/2].graduate){  // 比父大 
				Swap( index, (index-1)/2);
				ReHeapUp((index-1)/2);
			}
			while( index > 2 && minmaxheap[index].graduate < minmaxheap[(index-3)/4].graduate ){ // 比祖父大 
					Swap( index, (index-3)/4);
					index = (index-3)/4;
			}
		}
		else{ // maxheap
			if( minmaxheap[index].graduate < minmaxheap[(index-1)/2].graduate ){ // 比父小 
				Swap( index, (index-1)/2 );
				ReHeapUp((index-1)/2);	
			} 
			while( index > 2 && minmaxheap[index].graduate > minmaxheap[(index-3)/4].graduate) { // 比祖父大
					Swap( index, (index-3)/4);			 
					index = (index-3)/4;					
			}
		}

	}
	
	void Numbering(){ // 將任務一 符合的資料編上流水編碼 
		if( !matchvec.empty())for( int num = 1; num <= matchvec.size() ; num++ ) matchvec[num-1].num = num;
	}
	
	void Build(){      // 建立minmax heap 
		Numbering();
		while(!matchvec.empty()){
			minmaxheap.push_back(matchvec.front());
			matchvec.erase(matchvec.begin());
			ReHeapUp(minmaxheap.size()-1); 			
		}
	}
	
	int BiggestChild( int index ){   //取得較大子樹的位置 
		if( (index*2)+1 >= minmaxheap.size() ) return -1;
		else if( (index*2)+1 == minmaxheap.size()-1 ) return (index*2)+1;
		else if( (index*2)+2 < minmaxheap.size() && minmaxheap[(index*2)+1].graduate >= minmaxheap[(index*2)+2].graduate ) return (index*2)+1;
		else return (index*2)+2;
	}
	
	int BiggestGrandchild( int index ){
		
		if( (index*4)+3 > minmaxheap.size()-1 ) return -1;
		else if( (index*4)+6 < minmaxheap.size() ) {// 四孫都存在  

			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate && minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+5].graduate
				&& minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+3;
			
			else if( minmaxheap[(index*4)+4].graduate >= minmaxheap[(index*4)+3].graduate && minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+5].graduate
				&& minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+4;
			
			else if( minmaxheap[(index*4)+5].graduate >= minmaxheap[(index*4)+3].graduate && minmaxheap[(index*4)+5].graduate >=  minmaxheap[(index*4)+4].graduate
				&& minmaxheap[(index*4)+5].graduate >=  minmaxheap[(index*4)+6].graduate) return (index*4)+5;
			
			else return (index*4)+6;
		} 
		else if((index*4)+5 == minmaxheap.size() -1 ) {// 三孫 
			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate && minmaxheap[(index*4)+3].graduate >=  minmaxheap[(index*4)+5].graduate) return (index*4)+3;
			
			else if( minmaxheap[(index*4)+4].graduate >= minmaxheap[(index*4)+3].graduate && 
					minmaxheap[(index*4)+4].graduate >=  minmaxheap[(index*4)+5].graduate) return (index*4)+4;
			
			else return(index*4)+5;			
		}
		else if((index*4)+5 == minmaxheap.size() -1 ) {// 二孫 
			if( minmaxheap[(index*4)+3].graduate >= minmaxheap[(index*4)+4].graduate ) return (index*4)+3;		
			else return (index*4)+4;		
		}
		else return (index*4)+3;
	}

	void Delete(int index){ 
		minmaxheap[index] = minmaxheap[minmaxheap.size()-1]; // 將bottom 複製上去
		minmaxheap.pop_back(); // 刪除bottom 
		if( BiggestChild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestChild(index)].graduate) Swap( index,BiggestChild(index) ); // 跟小孩檢查 
		while( BiggestGrandchild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestGrandchild(index)].graduate ) { // 跟孫子檢查 
			int temp = BiggestGrandchild(index);
			Swap( index,BiggestGrandchild(index) );
			index = temp;
		}
		if( BiggestChild(index) != -1 && minmaxheap[index].graduate < minmaxheap[BiggestChild(index)].graduate) Swap( index,BiggestChild(index) );
			// 到最後面有小孩在跟小孩檢查一次 
	}  
	
	void GetMax( int k){   // 取的最大值 
		if ( k <= 0);
		else if ( minmaxheap.size() > 2) {  
				if( minmaxheap[1].graduate >= minmaxheap[2].graduate) maxitems.push_back(minmaxheap[1]),Delete(1);  //若左子樹較大，取左子樹 
				else maxitems.push_back(minmaxheap[2]),Delete(2);   //反之，取右子樹                                                 
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
	
	bool NumOk = false ;  // 檢查K是否在範圍內 
	bool IsZero = false ; 

	string readnum ;
	int a = 0 ;
	int k = 0 ;
	
	// 開黨 讀黨 建資料庫(vector) 
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
		matchvec = datavec; // 複製資料vec到符合資料  假設還沒塞選時 所有資料都是符合的 
		

		
		string key;
	
		cout << "Enter a keyword of 學校名稱: [*]for all" << endl;
		cin >> key ; //輸入使用者要的條件 
		Search( key, "學校名稱");
		cout << endl;
	
		cout << "Enter a keyword of 科系名稱: [*]for all" << endl;
		cin >> key ;//輸入使用者要的條件 
		Search( key, "科系名稱");
		cout << endl;
		
		cout << "Enter a keyword of 日夜別: [*]for all" << endl;
		cin >> key ;//輸入使用者要的條件 
		Search( key, "日夜別");
		cout << endl;
		
		cout << "Enter a keyword of 等級別: [*]for all" << endl; 
		cin >> key ;//輸入使用者要的條件 
		Search( key, "等級別");
		cout << endl;
		
		a = matchvec.size() ;
		if ( a == 0) {  // 若篩選完完全沒有符合的資料，則不進任務二 
			cout << "There is no matched records!" << endl ;
		}
		if ( a != 0) { // 篩選玩有資料，進任務二 

			Print(); // 印出所有符合的資料 
			system("pause");
		
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
			cout << "@@@         Mission 1: Min-max Heap Construction         @@@" << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
			MinMaxHeap * minmaxheap = new MinMaxHeap();
			minmaxheap -> Build(); // 建立minmax heap 
			minmaxheap -> Print(); // 印HEAP的bottom leftbottom 
			cout << endl << endl ;
			
			NumOk = false ;
		
			while ( !NumOk) {
				cout << "Enter the value of K:" << endl;
				int max = minmaxheap -> HowBig() ;
				cout << "[" << "1..." << max << "]" ;			
				cin >> readnum;//輸入使用者要幾個MAx值 
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
