#include<iostream>
#include<iomanip>
#include<vector>
#include"read.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::setw;


class Battleship{
	private:
		char ship;
	public:
	vector<vector<char>>grid_player_one{10,vector<char>(10,'~')}; //player one's grid
	vector<vector<char>>grid_player_two{10,vector<char>(10,'~')}; //player two's grid
	vector<vector<char>>grid_opponent{10,vector<char>(10,'~')}; //player two's game grid
    vector<vector<char>>game_grid{10,vector<char>(10,'~')}; //player one's game grid

		Battleship(){
			ship = '*';
		}

	void set_grid_opponent(vector<vector<char>>grid){
		grid_opponent = grid;
	}

// Huh, Its usually X an Y, not really columns and rows

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

bool search_grid(int col, int row, vector<vector<char>>&grid){
	if(grid.at(row).at(col) == '*'){
		grid_opponent.at(row).at(col) = 'X';
		return true; }
     return false;
}

vector<string> pastInputs;
vector<string> pastInputs2;


Coord readCoordinate(string player){
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
			if(input.size() == 3 and input.at(2) != '0'){
				goodInput = false;
            	cout << "BAD INPUT" << endl;
			}

        }else {
			goodInput = false;
            cout << "BAD INPUT" << endl;
        }


		 if(goodInput == true and player == "ONE"){
            if(find(pastInputs.begin(), pastInputs.end(), input) != pastInputs.end()){
                cout << "You already entered this >:[ " << endl;
                goodInput = false;
            } else {
                pastInputs.push_back(input);
            }
        }

        if(goodInput == true and player != "ONE"){
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

void battleship_setup(string player){
	cout<<"----------------------------------"<<endl;
    cout<<"|"<<setw(20)<<"           BATTLESHIP           "<<"|"<<endl;
    cout<<"----------------------------------"<<endl<<endl;

	cout<<"Each ship can only be placed in a HORIZONTAL or VERTICAL position!"<<endl<<endl;

	if(player == "ONE"){ print_grid(grid_player_one);}
    else{ print_grid(grid_player_two);}
	cout<<"PLAYER "<<player<<" please place your DESTROYER (2 spots)"<<endl;
	for(int i = 0; i < 2; i++){
		Coord c;
		c = readCoordinate(player);
		if(player == "ONE"){grid_player_one.at(c.row).at(c.column) = '*';}
        else{ grid_player_two.at(c.row).at(c.column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your CRUSIER (3 spots)"<<endl;
	for(int i = 0; i < 3; i++){
		Coord c;
		c = readCoordinate(player);
        if(player == "ONE"){grid_player_one.at(c.row).at(c.column) = '*';}
        else{ grid_player_two.at(c.row).at(c.column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your BATTLESHIP (4 spots)"<<endl;
	for(int i = 0; i < 4; i++){
		Coord c;
		c = readCoordinate(player);
        if(player == "ONE"){grid_player_one.at(c.row).at(c.column) = '*';}
		else{ grid_player_two.at(c.row).at(c.column) = '*';}
    }
	cout<<setw(5)<<"PLAYER "<<player<<"'S ocean grid"<<endl;
	if(player == "ONE"){ print_grid(grid_player_one);}
	else{ print_grid(grid_player_two);}
	pastInputs.clear();
    pastInputs2.clear();
}

void battleship_machine(string player){
    	if(player == "ONE"){
			cout<<setw(15)<<"Your ocean grid: "<<endl;
			print_grid(grid_player_one);
			cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(game_grid);
		}
    	else{ 
			cout<<setw(15)<<"Your ocean grid: "<<endl;
            print_grid(grid_player_two);
            cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(game_grid);
		}
		cout<<"You get three shots to hit your opponent's ships"<<endl;
		for(int i = 0; i < 3; i++){
			cout<<"Enter the coordinates for shot "<<i+1<<endl;
			Coord z;
        	z = readCoordinate(player);
			 if(player == "ONE"){
				 if(search_grid(z.column, z.row, grid_opponent)){ //player one's turn
				 	game_grid.at(z.row).at(z.column) = '@';
					grid_opponent.at(z.row).at(z.column) = 'X';
				 	cout<<"You got a hit!"<<endl;
				 }else{
					game_grid.at(z.row).at(z.column) = 'X';
					cout<<"You missed!"<<endl;
				 }
			 }else{ 
                 if(search_grid(z.column, z.row, grid_opponent)){ //player two's turn
                     game_grid.at(z.row).at(z.column) = '@';
					 grid_opponent.at(z.row).at(z.column) = 'X';
                    cout<<"You got a hit!"<<endl;
				 }else{
                    game_grid.at(z.row).at(z.column) = 'X';
                    cout<<"You missed!"<<endl;
                 	}
				}
			 if(i+1 == 3){ 
				 cout<<"YOUR TURN HAS ENDED!";
				 cout<<"GOING BACK TO THE VOLLARDY PHASE..."<<endl;
			 }
			}
}
};
