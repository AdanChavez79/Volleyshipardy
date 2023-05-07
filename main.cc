#include<unordered_map>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include"jeopardy.h"
#include"/public/colors.h"
#include"/public/read.h"

using namespace std;

//1. Replace string \n with actual endline
//2. Userface
//3. Print questions and answers randomly
//4. A way to win the game

int main(){
 Jeopardy info;
 int key = 1;
 unordered_map<int,Jeopardy> database;
 database.reserve(1'000'000);

 ifstream ins("questions.txt");
 	while(ins){
    ins>>info;
    if(!ins){break;}    
    database.insert({key,{info}});
    key++;
}
/*for (auto x : database){
    cout << x.second;
}*/

 srand(time(0));
 int count = 1;
 char answer;
 vector<int>old_questions;
	
 while(true){
	int random = rand()%key;
	cout<<"----------------------------------"<<endl;
	cout<<"|"<<setw(20)<<"           JEOPARDY             "<<"|"<<endl;
	cout<<"----------------------------------"<<endl;
	cout<<database.find(random)->second<<endl;
	old_questions.push_back(random); //stores the question numbers that have already been used
	//need to make sure questions aren't repeated
	
	cout<<"Please choose an answer: "<<endl;
	cin>>answer;
	if(answer == 'A'){ cout<<"CORRECT!"<<RESET<<endl; } //needs to be randomized
	else{ cout<<"WRONG"<<endl;}
	if(count == 94) {break;} //94 questions in total
	count++;
	}

return 0;
}
