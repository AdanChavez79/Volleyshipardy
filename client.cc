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
#include"jeopardy.h"
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
		//s >> line;
		//Player player;
		float new_time = 0.0, old_time = 0.0, winner = 0.0;
		string one_time, time;
		stringstream ss;
		Jeopardy jeopardy;
		cout<<setw(25)<<"****PLAYER TWO****"<<endl<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"|"<<setw(20)<<"           VOLLEYBALL           "<<"|"<<endl;
		cout<<"----------------------------------"<<endl<<endl;
		while(true){
			cout<<endl<<"PLAYER ONE'S TURN..."<<endl;
			getline(s,one_time);
			if(one_time == "WRONG"){
				cout<<"PLAYER ONE GOT THEIR QUESTION WRONG"<<endl;
				cout<<"YOU WIN!"<<endl;
				return 0;
			}
			if(one_time == "LONG"){
				cout<<"PLAYER ONE TOOK TO LONG"<<endl;
				cout<<"YOU WIN!"<<endl;
				return 0;
			}
			cout<<one_time<<endl;
			for(size_t i = 0; i < one_time.size(); i++){
				one_time.erase(remove_if(one_time.begin(), one_time.end(), [](char c) { return !isdigit(c); } ), one_time.end());
			}
			ss << one_time;
			ss >> old_time;
			old_time = old_time*(0.001);
			jeopardy.jeopardy_machine();
			if(jeopardy.get_answer() == "WRONG"){ 
				cout<<"PLAYER ONE WINS"<<endl;
				s<<"WRONG";
				return 0;
			}/*else{
				battleship stuff	
		 	}
			*/
			cout<<"Time taken to answer: "<<jeopardy.get_time_to_beat()<<" seconds"<<endl<<endl;
			new_time = jeopardy.get_time_to_beat(); //plaer two's time
			if(new_time > old_time){
				cout<<"YOU TOOK TO LONG TO ANSWER"<<endl;
				cout<<"PLAYER ONE WINS"<<endl;
				s<<"LONG";
				return 0;
				} 
		 	s<<"Time to beat: "<<new_time<<" seconds\n";
		}	
	}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
