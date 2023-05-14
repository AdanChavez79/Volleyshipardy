#include<iostream>
#include<iomanip>
#include<vector>
#include"/public/read.h"

using namespace std;

//Battleship problems:
//1.Need to make sure the ship parts are lined up correctly
//2.Can't have the player put in the same coordinates

//i.a. can't have a ship have a loc at (10,1) and (1,1)


struct Coord {
    int column;
    int row;
};

void print_grid(vector<vector<char>>&grid){
	cout << "  ";
	for (size_t z = 0 ; z < grid.size(); z++){
		cout << z + 1  << " ";
	}
	cout << endl;

	for (size_t i = 0; i < grid.size(); i++) {
		cout << static_cast<char>('A' + i) << " ";
		for (size_t j = 0; j < grid.at(i).size(); j++) {
			if(grid.at(i).at(j) == -1){ cout << " "; }
			else { cout << grid.at(i).at(j) << " "; }
		}
		cout << endl;
	}
	cout<<endl;
}

bool search_grid(int col, int row, const vector<vector<char>>&grid){
     if(grid.at(row).at(col) == '*'){ return true;}
	 return false;
}

//How to use:
//Coord x
//x = readCoordinate;
//User types A7
//x.column now holds 7
//x.row now holds 1


vector<string> pastInputs;
vector<string> pastInputs2;

Coord readCoordinate(int count){
	bool goodInput = false;
	int r;
	int c;
	
	while(goodInput == false){
		string input = read("Enter coordinate: ");
		//Vetting 
		if(isalpha(input[1]) == false and input[0] >= 'A' and input[0] <= 'J'  and input[1] != '0'){
			if(input.size() == 2){
				r = input[0] - 'A' + 1;
				c = stoi(input.substr(1));
				goodInput = true;
			} else if (input.size() == 3 ){
				if(input[2] == '0'){
					r = input[0] - 'A' + 1;
                	c = 10;
                	goodInput = true;
				}
			}
			if(input.size() == 3 and input[2] != '0'){
				goodInput = false;
				cout << "BAD INPUT" << endl;
			}

		}else {
			goodInput = false;
			cout << "BAD INPUT" << endl;
		}

		if(goodInput == true and count == 0){
			if(find(pastInputs.begin(), pastInputs.end(), input) != pastInputs.end()){
				cout << "You already entered this >:[ " << endl;
				goodInput = false;
			} else {
				pastInputs.push_back(input);
			}
		}

		if(goodInput == true and count == 1){
            if(find(pastInputs2.begin(), pastInputs2.end(), input) != pastInputs2.end()){
                cout << "You already entered this >:[ " << endl;
                goodInput = false;
            } else {
                pastInputs2.push_back(input);
            }
        }



	}

	Coord x;
	x.column = c -1; 
	x.row = r - 1;
	cout << "GOOD INPUT" << endl;	
	return x;

}



int main(){
	//vector<vector<char>>grid(10, vector<char> (10, '~'));
	vector<vector<char>>grid_player_one(10,vector<char>(10,'~')); //player one's grid
	vector<vector<char>>grid_player_two(10,vector<char>(10,'~')); //player two's grid
	vector<vector<char>>grid_opponent_one(10,vector<char>(10,'~')); //player two's game grid
    vector<vector<char>>grid_opponent_two(10,vector<char>(10,'~')); //player one's game grid
	bool hit = false;
	cout<<"----------------------------------"<<endl;
    cout<<"|"<<setw(20)<<"           BATTLESHIP           "<<"|"<<endl;
    cout<<"----------------------------------"<<endl<<endl;

	cout<<"Each ship can only be placed in a HORIZONTAL or VERTICAL position!"<<endl<<endl;
	
	int count = 0;
	string player;
	while(true){ //setting up the ships
	if(count == 0){player = "ONE";}
	else{ player = "TWO";}
	cout<<setw(10)<<"PLAYER "<<player<<"'S TURN..."<<endl;
	if(count == 0){ print_grid(grid_player_one);}
    else{ print_grid(grid_player_two);}
	cout<<"PLAYER "<<player<<" please place your DESTROYER (2 spots)"<<endl;
	for(int i = 0; i < 2; i++){
//		int column = read("Enter a column: ");
//		int row = read("Enter a row: ");
//		column-=1;
//		row-=1;
		Coord c;
		c = readCoordinate(count);
		if(count == 0){grid_player_one.at(c.row).at(c.column) = '*';}
        else{ grid_player_two.at(c.row).at(c.column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your CRUSIER (3 spots)"<<endl;
	for(int i = 0; i < 3; i++){
//		int column = read("Enter a column: ");
//      int row = read("Enter a row: ");
//		column-=1;
//		row-=1;
		Coord c;
		c = readCoordinate(count);
        if(count == 0){grid_player_one.at(c.row).at(c.column) = '*';}
        else{ grid_player_two.at(c.row).at(c.column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your BATTLESHIP (4 spots)"<<endl;
	for(int i = 0; i < 4; i++){
//		int column = read("Enter a column: ");
//		int row = read("Enter a row: ");
//		column-=1;
//		row-=1;
		Coord c;
		c = readCoordinate(count);
        if(count == 0){grid_player_one.at(c.row).at(c.column) = '*';}
		else{ grid_player_two.at(c.row).at(c.column) = '*';}
    }
	cout<<setw(5)<<"PLAYER "<<player<<"'S ocean grid"<<endl;
	if(count == 0){ print_grid(grid_player_one);}
	else{ print_grid(grid_player_two);}
	if(count >=1 ){break;}
	count++;
}
 	pastInputs.clear();
	pastInputs2.clear();

	count = 0;
	while(true){ //game time
		if(count > 1){count = 0;}
		if(count == 0){player = "ONE";}
    	else{ player = "TWO";}
    	cout<<setw(10)<<"PLAYER "<<player<<"'S TURN..."<<endl;
    	if(count == 0){
			cout<<setw(15)<<"Your ocean grid: "<<endl;
			print_grid(grid_player_one);
			cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(grid_opponent_two);
		}
    	else{ 
			cout<<setw(15)<<"Your ocean grid: "<<endl;
            print_grid(grid_player_two);
            cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(grid_opponent_one);
		}
		cout<<"You get three shots to hit your opponent's ships"<<endl;
		for(int i = 0; i < 3; i++){
			cout<<"Enter the coordinates for shot "<<i+1<<endl;
	//		int column = read("Enter a column: ");
	//		int row = read("Enter a row: ");
	//		column-=1;
	//		row-=1;

			Coord z;
        	z = readCoordinate(count);
			 if(count == 0){
				 if(search_grid(z.column, z.row, grid_player_two)){ //player one's turn
				 	grid_opponent_two.at(z.row).at(z.column) = '@';
					grid_player_two.at(z.row).at(z.column) = 'X';
				 	cout<<"You got a hit!"<<endl;
				 }else{
					grid_opponent_two.at(z.row).at(z.column) = 'X';
					cout<<"You missed!"<<endl;
				 }
			 }else{ 
                 if(search_grid(z.column, z.row, grid_player_one)){ //player two's turn
                    grid_opponent_one.at(z.row).at(z.column) = '@';
					 grid_player_one.at(z.row).at(z.column) = 'X';
                    cout<<"Yout got a hit!"<<endl;
				 }else{
                    grid_opponent_one.at(z.row).at(z.column) = 'X';
                    cout<<"You missed!"<<endl;
                 	}
				}
			}
		count++;
	}

	return 0;

}
