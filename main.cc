#include<unordered_map>
#include<fstream>
#include"jeopardy.h"

using namespace std;

int main(){
 Jeopardy info;
 int key = 1;
 unordered_map<int,Jeopardy> database;
 database.reserve(1'000'000);

 ifstream ins("questions2.txt");
 	while(ins){
    ins>>info;
    if(!ins){break;}    
    database.insert({key,{info}});
    key++;
}

for (auto x : database){
    cout << x.second;
}

return 0;
}
