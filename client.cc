//
// daytime_client.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <string>
#include<chrono>
#include <boost/asio.hpp>
#include"common.h"
#include"ship.h"
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			cerr << "Usage: daytime_client <host> <port>" << endl;
			return EXIT_FAILURE;
		}

		tcp::iostream s(argv[1], argv[2]); //[1] == host, [2] == port
		if (!s) //Connection failed
		{
			cout << "Unable to connect: " << s.error().message() << endl;
			return EXIT_FAILURE;
		}

		//vector<vector<char>>player_two{10,vector<char>(10,'*')};
        vector<vector<char>>opponent{10,vector<char>(10,'~')};
		size_t size = opponent.size();
		float new_time = 0.0, old_time = 0.0, winner = 0.0;
		int trash = 0;
		string one_time, time, blah;
		stringstream ss;
		Jeopardy jeopardy;
		Battleship battleship;
		cout<<setw(25)<<"****PLAYER TWO****"<<endl<<endl;
		//Prep for Battleship
            cout<<"BATTLESHIP PREP PHASE..."<<endl;
            cout<<"PLAYER ONE WILL BEGIN..."<<endl;
           	for(size_t i = 0; i < size; i++){
                    for(size_t j = 0; j < size; j++){
                        s>>opponent.at(i).at(j);
                    }
                }
            getline(s, blah);
            cout<<"YOUR TURN..."<<endl;
            battleship.battleship_setup("TWO");
            for(size_t i = 0; i < size; i++){
                    for(size_t j = 0; j < size; j++){
                        s<<battleship.grid_player_two.at(i).at(j);
                    }
                }
            s<<"HI\n";
			cout<<endl<<"VOLLEYARDY PHASE..."<<endl;
			battleship.set_grid_opponent(opponent);

		while(true){
			//Jeopardy Begins
			cout<<"PLAYER ONE'S TURN..."<<endl;
			s>>old_time; //get time
			getline(s,one_time); //get message
			if(one_time == "WRONG"){ //Player two battleship
				cout<<"PLAYER ONE GOT THEIR QUESTION WRONG"<<endl;
				cout<<"YOU WIN!"<<endl<<endl;
				cout<<"ENTERING BATTLESHIP PHASE..."<<endl;
				battleship.battleship_machine("TWO");
				s<<0;
				s<<"HI\n";
			}
			if(one_time == "LONG"){ //Player two battleship
				cout<<"PLAYER ONE TOOK TO LONG"<<endl;
				cout<<"YOU WIN!"<<endl;
				cout<<"ENTERING BATTLESHIP PHASE..."<<endl;
                battleship.battleship_machine("TWO");
                s<<0;
                s<<"HI\n";
			}
			cout<<one_time<<endl;

			//Jeopardy Begins
			jeopardy.jeopardy_machine();
			if(jeopardy.get_answer() == "WRONG"){ //Player one battleship
				cout<<"PLAYER ONE WINS"<<endl;
				s<<0;
				s<<"WRONG\n";
				cout<<"PLAYER ONE GETS 3 SHOTS IN BATTLESHIP..."<<endl;
                s>>trash;
                getline(s,blah);
			}else{
			cout<<"Time taken to answer: "<<jeopardy.get_time_to_beat()<<" seconds"<<endl<<endl;
			new_time = jeopardy.get_time_to_beat(); //player two's time
			if(new_time > old_time){ //Player one battleship
				cout<<"YOU TOOK TO LONG TO ANSWER"<<endl;
				cout<<"PLAYER ONE WINS"<<endl;
				s<<0;
				s<<"LONG\n";
				cout<<"PLAYER ONE GETS 3 SHOTS IN BATTLESHIP..."<<endl;
                s>>trash;
                getline(s,blah);
				}else{ 
				s<<new_time; //send time
		 		s<<"Time to beat: "<<new_time<<" seconds\n"; //send message
				}
			}
		}	
	}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
