#include<unordered_map>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include"jeopardy.h"
#include"/public/colors.h"
#include"/public/read.h"

using namespace std;

int main(){
 Jeopardy info;
 int key = 0;
 unordered_map<int,Jeopardy> database;
 database.reserve(1'000'000);

 ifstream ins("questions.txt"); //reading file into a hash
 	while(ins){
    ins>>info;
    if(!ins){break;}    
    database.insert({key,{info}}); //key = int, info = Jeopardy data
    key++;
}

 srand(time(0));
 int count = 1, win = 0, lose = 0;
 char answer;
 vector<int>old_questions;
 Jeopardy question;
 string correct, wrong1, wrong2, wrong3;

 cout<<"----------------------------------"<<endl;
 cout<<"|"<<setw(20)<<"           JEOPARDY             "<<"|"<<endl;
 cout<<"----------------------------------"<<endl;
	
 while(true){
	int random = rand()%key; //randomizing the question
	int random_question = rand()%4;
	question = database.find(random)->second;
	correct = database.find(random)->second.get_right_answer1();
	wrong1 = database.find(random)->second.get_answer2();
	wrong2 = database.find(random)->second.get_answer3();
	wrong3 = database.find(random)->second.get_answer4();

	cout<<count<<". "<<question;
	if(random_question == 1){ //random question sequence
		cout<<"A. "<<correct<<endl;
		cout<<"B. "<<wrong1<<endl;
		cout<<"C. "<<wrong2<<endl;
		cout<<"D. "<<wrong3<<endl;
		char answer = read("Please enter a letter: \n");
		if(answer == 'A'){ 
			cout<<"CORRECT"<<endl;
			win++;
		}
		else{ 
			cout<<"WRONG"<<endl; 
			lose++;
		}
	}else if(random_question == 2){
		cout<<"A. "<<wrong1<<endl;
		cout<<"B. "<<correct<<endl;
		cout<<"C. "<<wrong2<<endl;
		cout<<"D. "<<wrong3<<endl;
		char answer = read("Please enter a letter: \n");
		if(answer == 'B'){ 
			cout<<"CORRECT"<<endl;
			win++;
		}
        else{ 
			cout<<"WRONG"<<endl; 
			lose++;
		}
	}else if(random_question == 3){
		cout<<"A. "<<wrong3<<endl;
		cout<<"B. "<<wrong2<<endl;
		cout<<"C. "<<correct<<endl;
		cout<<"D. "<<wrong1<<endl;
		char answer = read("Please enter a letter: \n");
		if(answer == 'C'){ 
			cout<<"CORRECT"<<endl;
			win++;
		}
        else{ 
			cout<<"WRONG"<<endl;
			lose++;
		}
	}else if(random_question == 4){
		cout<<"A. "<<wrong2<<endl;
		cout<<"B. "<<wrong1<<endl;
		cout<<"C. "<<wrong3<<endl;
		cout<<"D. "<<correct<<endl;
		char answer = read("Please enter a letter: \n");
		if(answer == 'D'){ 
			cout<<"CORRECT"<<endl;
			win++;
		}
        else{ 
			cout<<"WRONG"<<endl; 
			lose++;
		}
	}else{
		cout<<"A. "<<wrong1<<endl;
		cout<<"B. "<<wrong3<<endl;
		cout<<"C. "<<correct<<endl;
		cout<<"D. "<<wrong2<<endl;
		char answer = read("Please enter a letter: \n");
		if(answer == 'C'){ 
			cout<<"CORRECT"<<endl;
			win++;
		}
        else{ 
			cout<<"WRONG"<<endl; 
			lose++;
		}
	}
	
	if(win == 5) { //Way to win the game -> change? 
		cout<<"YOU WIN"<<endl;
		cout<<"CORRECT: "<<win<<endl;
		cout<<"WRONG: "<<lose<<endl;
		break;
	}
	count++;
	}

return 0;
}
