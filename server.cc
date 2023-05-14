//
// daytime_server.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "read.h"
#include "common.h"
#include "ship.h"
#include "jeopardy.h"
using namespace std;
using boost::asio::ip::tcp;

/*string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}*/

int main()
{
	try
	{
		boost::asio::io_context io_context;

		tcp::endpoint endpoint(tcp::v4(), read<int>("Please enter a port number: \n"));
		tcp::acceptor acceptor(io_context, endpoint);

		for (;;)
		{
			tcp::iostream stream;
			boost::system::error_code ec;
			acceptor.accept(stream.socket(), ec);
			if (!ec)
			{	//To Do:
				//Check for bugs/vetting
				//Clean up interface
				//Make it fancy


				//stream << make_daytime_string();
				//vector<vector<char>>player_one{10,vector<char>(10,'~')};
        		vector<vector<char>>opponent{10,vector<char>(10,'~')};
				size_t size = opponent.size();
				float new_time = 0.0, old_time = 0.0, count = 0.0;
				int trash = 0;
				string two_time, line, blah;
				stringstream ss;
				Jeopardy jeopardy;
				Battleship battleship;
				cout<<setw(25)<<"****PLAYER ONE****"<<endl<<endl;
				 //Prep for Battleship
                    cout<<"BATTLESHIP PREP PHASE..."<<endl;
                    cout<<"YOU WILL BEGIN..."<<endl;
                    battleship.battleship_setup("ONE");
                    for(size_t i = 0; i < size; i++){
                    for(size_t j = 0; j < size; j++){
                        stream<<battleship.grid_player_one.at(i).at(j);
                    	}
                	}
                    stream<<"HI\n";
                    cout<<"PLAYER TWO'S TURN..."<<endl;
                    for(size_t i = 0; i < size; i++){
                    for(size_t j = 0; j < size; j++){
                        stream>>opponent.at(i).at(j);
                    	}
					}
                    getline(stream, blah);
                    cout<<endl<<"VOLLEYARDY PHASE..."<<endl;
					battleship.set_grid_opponent(opponent);

				while(true){
					//Begin Jeopardy
					jeopardy.jeopardy_machine();
					new_time = jeopardy.get_time_to_beat(); 
					if(jeopardy.get_answer() == "WRONG"){ //Player two gets to shoot
						cout<<"PLAYER TWO WINS"<<endl;
						stream<<0;
						stream<<"WRONG\n";
						cout<<"PLAYER TWO GETS 3 SHOTS IN BATTLESHIP..."<<endl;
						for(size_t i = 0; i < size; i++){
                    		for(size_t j = 0; j < size; j++){
                        		stream>>battleship.grid_player_one.at(i).at(j);
                        	}
                    	}
						getline(stream,blah);
					}else{
					if(count != 0){
					if(new_time > old_time){ //Player two gets to shoot
                        cout<<"YOU TOOK TO LONG"<<endl;
                        cout<<"PLAYER TWO WINS"<<endl;
						stream<<0;
                        stream<<"LONG\n"<<endl;
                        cout<<"PLAYER TWO GETS 3 SHOTS IN BATTLESHIP..."<<endl;
                        for(size_t i = 0; i < size; i++){
                    		for(size_t j = 0; j < size; j++){
                        	stream>>battleship.grid_player_one.at(i).at(j);
                        	}
                    	}
						getline(stream,blah);
                        }
					}
					cout<<"Time taken to answer: "<<jeopardy.get_time_to_beat()<<" seconds"<<endl<<endl;
					stream<<jeopardy.get_time_to_beat(); //send time
					stream<<"Time to beat: "<<jeopardy.get_time_to_beat()<<" seconds\n"; //send message
					cout<<"PLAYER TWO'S TURN..."<<endl; 
					stream>>old_time; //get time
					getline(stream,two_time); //get message
					if(two_time == "WRONG"){ //Player one gets to shoot
						cout<<"PLAYER TWO GOT THEIR QUESTION WRONG"<<endl;
						cout<<"YOU WIN!"<<endl<<endl;
                		cout<<"ENTERING BATTLESHIP PHASE..."<<endl;
                		battleship.battleship_machine("ONE");
                		for(size_t i = 0; i < size; i++){
                    	for(size_t j = 0; j < size; j++){
                        	stream<<battleship.grid_opponent.at(i).at(j);
                        }
                    	}
                		stream<<"HI\n";
					}else if(two_time == "LONG"){ //Player one gets to shoot
						cout<<"PLAYER TWO TOOK TO LONG"<<endl;
						cout<<"YOU WIN!"<<endl<<endl;
                		cout<<"ENTERING BATTLESHIP PHASE..."<<endl;
                		battleship.battleship_machine("ONE");
                		for(size_t i = 0; i < size; i++){
                    	for(size_t j = 0; j < size; j++){
                        	stream<<battleship.grid_opponent.at(i).at(j);
                        	}
                    	}
                		stream<<"HI\n";
					}else{
						cout<<two_time<<endl;
						count++;
					}
					}
				}
      }
    }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }
}
