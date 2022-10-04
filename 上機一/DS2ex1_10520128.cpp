// 電資二 林佳穎 10520128 
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib> 
using namespace std;

string fileName = "-1", fileNum;
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

class MaxHeap{
	
	vector<Data> maxheap;
	public:
		
	int Two( int n){ // return 2的N次方 
		int sum = 1 ;
		for(; n > 0 ; n--)sum = 2*sum;
		return sum;
	}
	
	int LeftBottomIndex(){ // return leftbottom 的index 
		 int level = 1;
		for(; maxheap.size() > Two( level)-1 ;level++);
		return Two(level-1)-1;
	}



	void Print(){ // 印出 root bottom leftbottom 的編碼及資料 
		if(maxheap.empty()) cout << "### There is noting matched ###" << endl;
		else{
			cout << "<max heap>" << endl;
			cout << "root: " << '[' << maxheap.front().num << ']'<< ' ' << maxheap.front().graduate << endl;
			cout << "bottom: " << '[' << maxheap.back().num << ']' << ' ' << maxheap.back().graduate << endl;
			cout << "Leftmost bottom: " << '[' << maxheap[LeftBottomIndex()].num << ']' << ' ' << maxheap[LeftBottomIndex()].graduate << endl;
		}
	
	}



	void Numbering(){ // 將任務一 符合的資料邊上流水編碼 
		if( !matchvec.empty())for( int num = 1; num <= matchvec.size() ; num++ ) matchvec[num-1].num = num;
	}

	void SwapMaxHeap(int index, int parent){ // 父子資料(位置)交換 
		Data temp;
		temp = maxheap[index];
		maxheap[index] = maxheap[parent];
		maxheap[parent] = temp;
	}

	void ReHeapUp( int index ){ // 調整資料到符合MAXheap 
		if( maxheap[index].graduate <= maxheap[(index-1)/2].graduate); // 資料比其父小或一樣 不用換，否之交換 
		else{
			SwapMaxHeap(index,(index-1)/2);
			if( (index-1)/2 != 0 )ReHeapUp( (index-1)/2 );
		}
	}

	void Build(){ // 建立MAXHEAP 
		Numbering(); // 將任務一 符合的資料邊上流水編碼 
		while(!matchvec.empty()){
			maxheap.push_back(matchvec.front()); // 放資料到bottom 
			matchvec.erase(matchvec.begin());// 刪除原vec的資料 
			if( maxheap.size() != 1 )ReHeapUp(maxheap.size()-1); // 調整資料到符合MAXheap。maxheap.size()-1為剛放入資料的vindex 
		}
		
	}

};




int main(){
	
	// 開黨 讀黨 建資料庫(vector) 
	while( fileName != "0" && !set ){
		cout << "Input the file number: 101, 102, ..... [0]Quit" << endl;
		getline(cin,fileNum);
		fileName = "input" + fileNum + ".txt";
		ReadFileAndBuildDatavec();
	}
		
	while( fileNum != "0"){
		

		matchvec.clear();
		matchvec = datavec; // 複製資料vec到符合資料  假設還沒塞選時 所有資料都是符合的 
		
		cout << "**********************************************************" << endl;
		cout << "***Mission One: Select Matched Records from a Text File***" << endl;
		cout << "**********************************************************" << endl;
		
		string key;
	
		cout << "Enter a keyword of 學校名稱: [*]for all" << endl;
		getline(cin,key); //輸入使用者要的條件 
		Search( key, "學校名稱");
		cout << endl;
	
		cout << "Enter a keyword of 科系名稱: [*]for all" << endl;
		getline(cin,key);//輸入使用者要的條件 
		Search( key, "科系名稱");
		cout << endl;
		
		cout << "Enter a keyword of 日夜別: [*]for all" << endl;
		getline(cin,key);//輸入使用者要的條件 
		Search( key, "日夜別");
		cout << endl;
		
		cout << "Enter a keyword of 等級別: [*]for all" << endl; 
		getline(cin,key);//輸入使用者要的條件 
		Search( key, "等級別");
		cout << endl;
		
		Print(); // 印出所有符合的資料 
		cout << "**********************************************************" << endl;
		system("pause");
		
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@ Mission Two: Build a Max Heap from the Selected Data @@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
		MaxHeap * maxheap = new MaxHeap();
		maxheap -> Build(); // 建立max heap 
		maxheap -> Print(); // 印HEAP的root bottom leftbottom 
		cout << "[0]Quit or [Any other]continue?" << endl;
		getline(cin,fileNum);
	}
	
	fin.close();
	return 0;
}
