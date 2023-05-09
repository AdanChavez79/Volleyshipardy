#pragma once
#include <iostream>
#include<sstream>
#include <regex>
#include <time.h>




class player {
private:
	bool ball;
	clock_t time_start;
	clock_t time_taken;

public:

	player(){
	ball = true;
	time_start = clock();
	time_taken = 0;
	}

	Jeopardy(const bool &new_ball, const int &new_time) : ball(new_ball) , time(new_ball){}
	clock_t get_time_start(){return time_start;}
    clock_t get_time_taken() const { return time_taken;}
	bool get_ball(){return ball;}


	void set_time_start(const clock_t &new_time_start) { time_start = new_time_start; }
    void set_time_taken(const clock_t &new_time_taken) { time_taken = new_time_taken; }
    void set_ball(const bool &new_ball) { ball = new_ball; }

	void update_time_taken() {
        time_taken = clock() - time_start;
    }

};

















