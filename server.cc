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
#include "/public/read.h"
#include"jeopardy.h"
using namespace std;
using boost::asio::ip::tcp;

string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

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
			{
				//stream << make_daytime_string();
				float new_time = 0.0, old_time = 0.0, winner = 0.0;
				string two_time;
				Jeopardy jeopardy;
					cout<<setw(25)<<"****PLAYER ONE****"<<endl<<endl;
					cout<<"----------------------------------"<<endl;
					cout<<"|"<<setw(20)<<"           VOLLEYBALL            "<<"|"<<endl;
					cout<<"----------------------------------"<<endl<<endl;
					while(true){
					jeopardy.jeopardy_machine();
					old_time = jeopardy.get_time_to_beat();
					if(jeopardy.get_answer() == "WRONG"){
						cout<<"PLAYER TWO WINS"<<endl;
						stream<<"WRONG";
						return 0;
					}/*else{
						battleship stuff
					}*/
					cout<<"Time taken to answer: "<<jeopardy.get_time_to_beat()<<" seconds"<<endl<<endl;
					stream<<"Time to beat: "<<jeopardy.get_time_to_beat()<<" seconds\n";
					cout<<"PLAYER TWO'S TURN..."<<endl;
					new_time = jeopardy.get_time_to_beat();
					if(new_time > old_time){break;}
					getline(stream,two_time);
					if(two_time == "WRONG"){
						cout<<"PLAYER TWO GOT THEIR QUESTION WRONG"<<endl;
						cout<<"YOU WIN!"<<endl;
						return 0;
					}
					cout<<two_time<<endl;
				}
      }
    }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }
}
