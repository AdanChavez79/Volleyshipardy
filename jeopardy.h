#pragma once
#include <iostream>
#include<sstream>
#include<unordered_map>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<chrono>
#include<iomanip>
#include"colors.h"
#include"read.h"
using std::string;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

// Generally, 
// We would have a question class and another class with database in it.
class Jeopardy{
	private:
		string question;
		string right_answer1;
		string answer2;
		string answer3;
		string answer4;
		string dummy;
		float time_to_beat = 0.0;
		float old_time = 0.0;
		string answer = "wrong";
	public:

		Jeopardy() {
			question = "?";
			right_answer1 = "right";
			answer2 = "wrong";
			answer3 = "wrong";
			answer4 = "wrong";
			dummy = "blah";
		}

		Jeopardy(const string &new_question, const string &new_right_answer1, const string &new_answer2, const string &new_answer3, const string &new_answer4, const string &new_dummy) : question(new_question), right_answer1(new_right_answer1), answer2(new_answer2), answer3(new_answer3), answer4(new_answer4), dummy(new_dummy) {}

		//Getters
		string get_question() const {return question;}
		string get_right_answer1() const {return right_answer1;}
		string get_answer2() {return answer2;}
		string get_answer3() const {return answer3;}
		string get_answer4() const {return answer4;}
		string get_answer() const {return answer;}
		float get_time_to_beat() const{return time_to_beat;}
		float get_old_time() const {return old_time;}

		void set_time_to_beat(float clock){
			time_to_beat = (clock*0.001);
		}
		void set_old_time(float old){
			old_time = old;
		}
		void set_answer(string a){
			answer = a;
		}

		void jeopardy_machine(){
			Jeopardy info;
			int key = 0;
			// Wait what
			std::unordered_map<int,Jeopardy> database;
			database.reserve(1'000'000);
			typedef std::chrono::high_resolution_clock clock;
			auto end = clock::now();

			std::ifstream ins("questions.txt"); //reading file into a hash
			while(ins){
				ins>>info;
				if(!ins){break;}
				database.insert({key,{info}}); //key = int, info = Jeopardy data
				key++;
			}

			srand(time(0));
			char answer;
			Jeopardy question;
			string correct, wrong1, wrong2, wrong3;
			//while(true){
				int random = rand()%key; //randomizing the question
				int random_question = rand()%4;
				question = database.find(random)->second;
				correct = database.find(random)->second.get_right_answer1();
				wrong1 = database.find(random)->second.get_answer2();
				wrong2 = database.find(random)->second.get_answer3();
				wrong3 = database.find(random)->second.get_answer4();
				
				auto start = clock::now();
				std::cout<<question;
			//	setcolor(135,206,250);
				if(random_question == 1){ //random question sequence
					std::cout<<"A. "<<correct<<endl;
					std::cout<<"B. "<<wrong1<<endl;
					std::cout<<"C. "<<wrong2<<endl;
					std::cout<<"D. "<<wrong3<<endl;
					char answer = read("Please enter a letter: \n");
					auto end = clock::now();
					if(answer == 'A'){
						std::cout<<"CORRECT"<<endl<<endl;
						set_answer("CORRECT");
					}
					else{
						std::cout<<"WRONG"<<endl<<endl;
						set_answer("WRONG");
					}
				}else if(random_question == 2){
					std::cout<<"A. "<<wrong1<<endl;
					std::cout<<"B. "<<correct<<endl;
					std::cout<<"C. "<<wrong2<<endl;
					std::cout<<"D. "<<wrong3<<endl;
					char answer = read("Please enter a letter: \n");
					end = clock::now();
					if(answer == 'B'){
						std::cout<<"CORRECT"<<endl<<endl;
						set_answer("CORRECT");
					}
					else{
						std::cout<<"WRONG"<<endl<<endl;
						set_answer("WRONG");
					}
				}else if(random_question == 3){
					std::cout<<"A. "<<wrong3<<endl;
					std::cout<<"B. "<<wrong2<<endl;
					std::cout<<"C. "<<correct<<endl;
					std::cout<<"D. "<<wrong1<<endl;
					char answer = read("Please enter a letter: \n");
					end = clock::now();
					if(answer == 'C'){
						std::cout<<"CORRECT"<<endl<<endl;
						set_answer("CORRECT");
					}else{
						std::cout<<"WRONG"<<endl<<endl;
						set_answer("WRONG");
					}
				}else if(random_question == 4){
					std::cout<<"A. "<<wrong2<<endl;
					std::cout<<"B. "<<wrong1<<endl;
					std::cout<<"C. "<<wrong3<<endl;
					std::cout<<"D. "<<correct<<endl;
					char answer = read("Please enter a letter: \n");
					end = clock::now();
					if(answer == 'D'){
						std::cout<<"CORRECT"<<endl<<endl;
						set_answer("CORRECT");
					}
					else{
						std::cout<<"WRONG"<<endl<<endl;
						set_answer("WRONG");
					}
				}else{
					std::cout<<"A. "<<wrong1<<endl;
					std::cout<<"B. "<<wrong3<<endl;
					std::cout<<"C. "<<correct<<endl;
					std::cout<<"D. "<<wrong2<<endl;
					char answer = read("Please enter a letter: \n");
					end = clock::now();
					if(answer == 'C'){
						std::cout<<"CORRECT"<<endl<<endl;
						set_answer("CORRECT");
					}
					else{
						std::cout<<"WRONG"<<endl<<endl;
						set_answer("WRONG");
					}
				}
		//		cout << RESET;

				set_time_to_beat(duration_cast<milliseconds>(end-start).count());
			//	count++;
			//}

		}

		friend std::istream& operator>>(std::istream& ins, Jeopardy &rhs) { //input
			getline(ins, rhs.question, '\n');
			getline(ins, rhs.right_answer1, '\n');
			getline(ins, rhs.answer2, '\n');
			getline(ins, rhs.answer3, '\n');
			getline(ins, rhs.answer4, '\n');
			getline(ins, rhs.dummy, '\n');
			return ins;
		}

		friend std::ostream& operator<<(std::ostream& outs, const Jeopardy &rhs) { //output
			for(size_t i = 0; i < rhs.question.size(); ++i){
				if( rhs.question.substr(i,2) == "\\n"){
					outs << '\n';
					++i;
				}
				else{setcolor(255, 255, 0); 
					outs <<rhs.question.at(i) << RESET;} 
			}
			outs << std::endl;
			return outs;
		}
};
