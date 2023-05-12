#include<iostream>
#include<iomanip>
#include<vector>
#include"/public/read.h"

using namespace std;

//Battleship problems:
//1.Need to make sure the ship parts are lined up correctly
//i.a. can't have a ship have a loc at (10,1) and (1,1)
//2.Can't have the player put in the same coordinates
//3.Need to read in coordinates like D4

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

bool search_grid(vector<vector<char>>grid, vector<vector<char>>grid2){
	const int size = grid.size();
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(grid.at(i).at(j) == '*' and grid2.at(i).at(j) == '*'){
				return true;
			}else{ return false;}
		}
	}

	return false;
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
		int column = read("Enter a column: ");
		int row = read("Enter a row: ");
		column-=1;
		row-=1;
		if(count == 0){grid_player_one.at(row).at(column) = '*';}
        else{ grid_player_two.at(row).at(column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your CRUSIER (3 spots)"<<endl;
	for(int i = 0; i < 3; i++){
		int column = read("Enter a column: ");
        int row = read("Enter a row: ");
		column-=1;
		row-=1;
        if(count == 0){grid_player_one.at(row).at(column) = '*';}
        else{ grid_player_two.at(row).at(column) = '*';}
	}
	cout<<"PLAYER "<<player<<" please place your BATTLESHIP (4 spots)"<<endl;
	for(int i = 0; i < 4; i++){
        int column = read("Enter a column: ");
        int row = read("Enter a row: ");
		column-=1;
		row-=1;
        if(count == 0){grid_player_one.at(row).at(column) = '*';}
		else{ grid_player_two.at(row).at(column) = '*';}
    }
	cout<<setw(5)<<"PLAYER "<<player<<"'S ocean grid"<<endl;
	if(count == 0){ print_grid(grid_player_one);}
	else{ print_grid(grid_player_two);}
	if(count >=1 ){break;}
	count++;
}
 
	while(true){ //game time
		if(count > 1){count = 0;}
		if(count == 0){player = "ONE";}
    	else{ player = "TWO";}
    	cout<<setw(10)<<"PLAYER "<<player<<"'S TURN..."<<endl;
    	if(count == 0){
			cout<<setw(10)<<"Your ocean grid: "<<endl;
			print_grid(grid_player_one);
			cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(grid_opponent_two);
		}
    	else{ 
			cout<<setw(10)<<"Your ocean grid: "<<endl;
            print_grid(grid_player_two);
            cout<<setw(10)<<"Opponent's ocean grid: "<<endl;
			print_grid(grid_opponent_one);
		}
		cout<<"You get three shots to hit your opponent's ships"<<endl;
		for(int i = 0; i < 3; i++){
			cout<<"Enter the coordinates for shot "<<i+1<<endl;
			int column = read("Enter a column: ");
			int row = read("Enter a row: ");
			column-=1;
			row-=1;
			 if(count == 0){
				 grid_opponent_two.at(row).at(column) = '*'; 
				 if(search_grid(grid_opponent_two, grid_player_two)){ //compares player two's grid and player one's game grid
				 	grid_opponent_two.at(row).at(column) = '@';
				 	cout<<"You got a hit!"<<endl;
				 }else{
					grid_opponent_two.at(row).at(column) = 'X';
					cout<<"You missed!"<<endl;
				 }
			 }else{ 
				 grid_opponent_one.at(row).at(column) = '*';
                 if(search_grid(grid_opponent_one, grid_player_one)){ 
                    grid_opponent_one.at(row).at(column) = '@';
                    cout<<"Yout got a hit!"<<endl;
				 }else{
                    grid_opponent_one.at(row).at(column) = 'X';
                    cout<<"You missed!"<<endl;
                 	}
				}
			}
		count++;
	}

	return 0;

}
