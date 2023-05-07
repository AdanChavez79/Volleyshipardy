#pragma once
#include <iostream>
#include<sstream>
#include <regex>
using std::string;



class Jeopardy{
private:
	string question;
	string right_answer1;
	string answer2;
	string answer3;
	string answer4;
	string dummy;
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
			else{ outs << rhs.question.at(i);} 
		}
		outs << std::endl;
		/*outs << rhs.right_answer1 << std::endl;
		outs << rhs.answer2 << std::endl;
		outs << rhs.answer3 << std::endl;
		outs << rhs.answer4 << std::endl << std::endl;*/
		return outs;
    }
};
