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
//#include"player.h"
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
		string one_time;
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
				cout<<"YOU WIN"<<endl;
				return 0;
			}
			old_time = jeopardy.get_time_to_beat(); //player one's time
			cout<<one_time<<endl;
			jeopardy.jeopardy_machine();
			if(jeopardy.get_answer() == "WRONG"){ 
				cout<<"PLAYER ONE WINS"<<endl;
				s<<"WRONG";
				return 0;
			}/*else{
				battleship stuff	
		 	}
			*/
			cout<<"Time taken to answer: "<<jeopardy.get_time_to_beat()<<" seconds"<<endl;
			new_time = jeopardy.get_time_to_beat(); //plaer two's time
			if(new_time > old_time){break;} //if player two's time is more then player one's
		 	s<<"Time to beat: "<<new_time<<" seconds\n";
		}
	
	}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
