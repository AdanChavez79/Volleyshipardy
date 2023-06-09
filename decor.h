#include"/public/colors.h"
#include<vector>
#include<fstream>

using std::endl;
using std::cout;
using std::string;
using std::vector;

void print_title(){
	cout<<BOLDRED<<R"(
__     __  ______  __       __       ________ __      __ _______   ______  ________ ________ __       ________ 
|  \   |  \/      \|  \     |  \     |        \  \    /  \       \ /      \|        \        \  \     |        \
| ▓▓   | ▓▓  ▓▓▓▓▓▓\ ▓▓     | ▓▓     | ▓▓▓▓▓▓▓▓\▓▓\  /  ▓▓ ▓▓▓▓▓▓▓\  ▓▓▓▓▓▓\\▓▓▓▓▓▓▓▓\▓▓▓▓▓▓▓▓ ▓▓     | ▓▓▓▓▓▓▓▓
| ▓▓   | ▓▓ ▓▓  | ▓▓ ▓▓     | ▓▓     | ▓▓__     \▓▓\/  ▓▓| ▓▓__/ ▓▓ ▓▓__| ▓▓  | ▓▓     | ▓▓  | ▓▓     | ▓▓__    
 \▓▓\ /  ▓▓ ▓▓  | ▓▓ ▓▓     | ▓▓     | ▓▓  \     \▓▓  ▓▓ | ▓▓    ▓▓ ▓▓    ▓▓  | ▓▓     | ▓▓  | ▓▓     | ▓▓  \   
  \▓▓\  ▓▓| ▓▓  | ▓▓ ▓▓     | ▓▓     | ▓▓▓▓▓      \▓▓▓▓  | ▓▓▓▓▓▓▓\ ▓▓▓▓▓▓▓▓  | ▓▓     | ▓▓  | ▓▓     | ▓▓▓▓▓   
   \▓▓ ▓▓ | ▓▓__/ ▓▓ ▓▓_____| ▓▓_____| ▓▓_____    | ▓▓   | ▓▓__/ ▓▓ ▓▓  | ▓▓  | ▓▓     | ▓▓  | ▓▓_____| ▓▓_____ 
    \▓▓▓   \▓▓    ▓▓ ▓▓     \ ▓▓     \ ▓▓     \   | ▓▓   | ▓▓    ▓▓ ▓▓  | ▓▓  | ▓▓     | ▓▓  | ▓▓     \ ▓▓     \
     \▓     \▓▓▓▓▓▓ \▓▓▓▓▓▓▓▓\▓▓▓▓▓▓▓▓\▓▓▓▓▓▓▓▓    \▓▓    \▓▓▓▓▓▓▓ \▓▓   \▓▓   \▓▓      \▓▓   \▓▓▓▓▓▓▓▓\▓▓▓▓▓▓▓▓
                                                                                                                
  ______  __    __ ______ _______   ______  _______  _______  __      __ 
 /      \|  \  |  \      \       \ /      \|       \|       \|  \    /  \
|  ▓▓▓▓▓▓\ ▓▓  | ▓▓\▓▓▓▓▓▓ ▓▓▓▓▓▓▓\  ▓▓▓▓▓▓\ ▓▓▓▓▓▓▓\ ▓▓▓▓▓▓▓\\▓▓\  /  ▓▓
| ▓▓___\▓▓ ▓▓__| ▓▓ | ▓▓ | ▓▓__/ ▓▓ ▓▓__| ▓▓ ▓▓__| ▓▓ ▓▓  | ▓▓ \▓▓\/  ▓▓ 
 \▓▓    \| ▓▓    ▓▓ | ▓▓ | ▓▓    ▓▓ ▓▓    ▓▓ ▓▓    ▓▓ ▓▓  | ▓▓  \▓▓  ▓▓  
 _\▓▓▓▓▓▓\ ▓▓▓▓▓▓▓▓ | ▓▓ | ▓▓▓▓▓▓▓| ▓▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓\ ▓▓  | ▓▓   \▓▓▓▓   
|  \__| ▓▓ ▓▓  | ▓▓_| ▓▓_| ▓▓     | ▓▓  | ▓▓ ▓▓  | ▓▓ ▓▓__/ ▓▓   | ▓▓    
 \▓▓    ▓▓ ▓▓  | ▓▓   ▓▓ \ ▓▓     | ▓▓  | ▓▓ ▓▓  | ▓▓ ▓▓    ▓▓   | ▓▓    
  \▓▓▓▓▓▓ \▓▓   \▓▓\▓▓▓▓▓▓\▓▓      \▓▓   \▓▓\▓▓   \▓▓\▓▓▓▓▓▓▓     \▓▓                                                                                                                 
                                                                                                                
)"<<RESET<<endl;
}

void print_ship_prep(){
	cout<<BOLDRED<<R"(
┏━━━┓┏━━━┓┏━━━┓┏━━━┓━━━━┏━━━┓┏┓━┏┓┏━━━┓┏━━━┓┏━━━┓
┃┏━┓┃┃┏━┓┃┃┏━━┛┃┏━┓┃━━━━┃┏━┓┃┃┃━┃┃┃┏━┓┃┃┏━┓┃┃┏━━┛
┃┗━┛┃┃┗━┛┃┃┗━━┓┃┗━┛┃━━━━┃┗━┛┃┃┗━┛┃┃┃━┃┃┃┗━━┓┃┗━━┓
┃┏━━┛┃┏┓┏┛┃┏━━┛┃┏━━┛━━━━┃┏━━┛┃┏━┓┃┃┗━┛┃┗━━┓┃┃┏━━┛
┃┃━━━┃┃┃┗┓┃┗━━┓┃┃━━━━━━━┃┃━━━┃┃━┃┃┃┏━┓┃┃┗━┛┃┃┗━━┓
┗┛━━━┗┛┗━┛┗━━━┛┗┛━━━━━━━┗┛━━━┗┛━┗┛┗┛━┗┛┗━━━┛┗━━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
)"<<RESET<<endl;
}

void print_begin(){
	cout<<BOLDRED<<R"(
┏━━┓━┏━━━┓┏━━━┓┏━━┓┏━┓━┏┓━━━━━━
┃┏┓┃━┃┏━━┛┃┏━┓┃┗┫┣┛┃┃┗┓┃┃━━━━━━
┃┗┛┗┓┃┗━━┓┃┃━┗┛━┃┃━┃┏┓┗┛┃━━━━━━
┃┏━┓┃┃┏━━┛┃┃┏━┓━┃┃━┃┃┗┓┃┃━━━━━━
┃┗━┛┃┃┗━━┓┃┗┻━┃┏┫┣┓┃┃━┃┃┃┏┓┏┓┏┓
┗━━━┛┗━━━┛┗━━━┛┗━━┛┗┛━┗━┛┗┛┗┛┗┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
)"<<RESET<<endl;
}

void print_ship_title(){
	cout<<BOLDBLUE<<R"(
┏━━┓━┏━━━┓┏━━━━┓┏━━━━┓┏┓━━━┏━━━┓┏━━━┓┏┓━┏┓┏━━┓┏━━━┓
┃┏┓┃━┃┏━┓┃┃┏┓┏┓┃┃┏┓┏┓┃┃┃━━━┃┏━━┛┃┏━┓┃┃┃━┃┃┗┫┣┛┃┏━┓┃
┃┗┛┗┓┃┃━┃┃┗┛┃┃┗┛┗┛┃┃┗┛┃┃━━━┃┗━━┓┃┗━━┓┃┗━┛┃━┃┃━┃┗━┛┃
┃┏━┓┃┃┗━┛┃━━┃┃━━━━┃┃━━┃┃━┏┓┃┏━━┛┗━━┓┃┃┏━┓┃━┃┃━┃┏━━┛
┃┗━┛┃┃┏━┓┃━┏┛┗┓━━┏┛┗┓━┃┗━┛┃┃┗━━┓┃┗━┛┃┃┃━┃┃┏┫┣┓┃┃━━━
┗━━━┛┗┛━┗┛━┗━━┛━━┗━━┛━┗━━━┛┗━━━┛┗━━━┛┗┛━┗┛┗━━┛┗┛━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
)"<<RESET<<endl;
}

void border(){
	cout<<"---------------------------------------------------------------------"<<endl;
}
