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
		//string full_question;
    	getline(ins, rhs.question, '\n');
		//std::regex target("(\n)+"); //trying to replace the \n in the string with an actual endline, not working
    	//string replacement = " ";
    	//rhs.question = std::regex_replace(full_question, target, replacement);
    	getline(ins, rhs.right_answer1, '\n');
		getline(ins, rhs.answer2, '\n');
        getline(ins, rhs.answer3, '\n');
		getline(ins, rhs.answer4, '\n');
		getline(ins, rhs.dummy, '\n');
    	return ins;
    }

    friend std::ostream& operator<<(std::ostream& outs, const Jeopardy &rhs) { //output
        return outs << rhs.question << std::endl <<"A. " << rhs.right_answer1 << std::endl << "B. " << rhs.answer2 << std::endl << "C. " << rhs.answer3 << std::endl << "D. "<< rhs.answer4 << std::endl <<std::endl;
    }
};
