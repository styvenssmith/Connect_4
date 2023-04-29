#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <queue>

using namespace std;


vector<vector<char>>arr(6, vector<char>(7, '.'));
queue<pair<int, int>>open;

struct location{

	int row, col;
};

void draw(){

	for(int i = 0;i<7;i++){
		cout<<i<<" ";
	}
	cout<<"\n";

	for(int i = 0;i<13;i++){
		cout<<"-";
	}
	cout<<"\n";
	for(int i = 0;i<arr.size();i++){
		for(int j = 0;j<arr[0].size();j++){

			cout<<arr[i][j]<<" ";

		}
		cout<<"\n";
	}
}


int evaluate(vector<vector<char>>&arr, bool mx){

	if(mx) return 10;
	else return -10;
/*
//horizontal
	for(int i = 0;i<arr.size();i++){
		for(int j = 0;j<=arr[0].size()-2;j++){
			if(arr[i][j]==arr[i][j+1] && arr[i][j+1]==arr[i][j+2] && arr[i][j+2]==arr[i][j+3] ){
				if(arr[i][j]=='X')
				return 10;
				else if(arr[i][j]=='O')return -10;
			}
			
		}
	}

//vertical
	for(int i = 0;i<arr[0].size();i++){
		for(int j = 0;j<arr.size()-3;j++){	

			if(arr[j][i]=='X' && arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i] && arr[j+2][i]==arr[j+3][i]){
				
				return 10;
			}
			else if(arr[j][i]=='O' && arr[j][i]==arr[j+1][i] && arr[j+1][i]==arr[j+2][i] && arr[j+2][i]==arr[j+3][i]){
				
				return -10;
			}	
		}
	}


	//diagonal front

	for(int i = 0;i<arr.size()-3;i++){
		for(int j = 0;j<arr[0].size()-3;j++){
			if(arr[i][j]=='X' && arr[i][j]==arr[i+1][j+1] && arr[i+1][j+1]==arr[i+2][j+2] && arr[i+2][j+2]==arr[i+3][j+3]){
				
				return 10;
			}
			else if(arr[i][j]=='O' && arr[i][j]==arr[i+1][j+1] && arr[i+1][j+1]==arr[i+2][j+2] && arr[i+2][j+2]==arr[i+3][j+3]){
				
				return -10;
			}	
		}
	}

	
	//diagonal back
	for(int i = 0;i<arr.size()-3;i++){
		for(int j = arr[0].size()-1;j>2;j--){
			if(arr[i][j]=='X' && arr[i][j]==arr[i+1][j-1] && arr[i+1][j-1]==arr[i+2][j-2] && arr[i+2][j-2]==arr[i+3][j-3]){
				
				return 10;
			}
			else if(arr[i][j]=='O' && arr[i][j]==arr[i+1][j-1] && arr[i+1][j-1]==arr[i+2][j-2] && arr[i+2][j-2]==arr[i+3][j-3]){
				
				return -10;
			}
		}
		
	}
*/
	
	int how_many = 0;

	for(int i = 0;i<arr.size();i++){
		for(int j = 0;j<arr[0].size();j++){
			if(arr[i][j]=='.') how_many++;
		}
	}

	if(how_many==0) return 0;

	return INT_MIN;
}



int minmax(vector<vector<char>>&arr, bool max_player){

	int score = evaluate(arr, max_player);

	if(score!=INT_MIN){
		return score;
	}

	
	if(max_player){
		int bestscore = INT_MIN;
		for(int i = 0;i<arr.size();i++){
			for(int j = 0;j<arr[0].size();j++){
				if(arr[i][j]=='.'){
					arr[i][j] = 'X';
					int num_score = minmax(arr, false);
					arr[i][j] = '.';
					bestscore = max(bestscore, num_score);
				}
			}
		}
		return bestscore;
	}
	else{
		int bestscore = INT_MAX;
		for(int i = 0;i<arr.size();i++){
			for(int j = 0;j<arr[0].size();j++){
				if(arr[i][j]=='.'){
					arr[i][j] = 'O';
					int min_score = minmax(arr, true);
					arr[i][j] = '.';
					bestscore = min(bestscore, min_score);
				}
			}
		}
		return bestscore;
	}
}

location move(vector<vector<char>>&arr){

	int score = INT_MIN;

	location ans;
	ans.row = ans.col = -1;




	for(int i = arr.size()-1;i>=0;i--){
		for(int j = 0;j<arr[0].size();j++){


			//if we are at the last row and it is empty consider it
			if(i==arr.size()-1 && arr[i][j]=='.'){
				arr[i][j] = 'X';
				int curr = minmax(arr, false);
				arr[i][j] = '.';
				if(curr>=score){
					score = curr;
					ans.row = i;
					ans.col = j;
				}
			}
			//if we are empty and the cell below us is not empty then consider it
			else if(i<=arr.size()-2 && arr[i][j]=='.' && arr[i+1][j]!='.'){
				arr[i][j] = 'X';
				int curr = minmax(arr, false);
				arr[i][j] = '.';
				if(curr>=score){
					score = curr;
					ans.row = i;
					ans.col = j;
				}
			}
			else break;

			
		}
	}
	return ans;
}


bool valid(string val){

	int num = -1;
	if(val.size()>1) return false;

	if(val.size()==1){
		if(isdigit(val[0])){
			num = val[0]-'0';
		}else return false;
	}

	int cnt = 0;
		for(int i = arr.size()-1;i>=0;i--){
		if(arr[i][num]!='.'){
			cnt++;
			continue;
		}
		if(arr[i][num]=='.' &&num<=6){
			arr[i][num]='O';
			return true;
		}

		
		}
		if(cnt==6){
			return false;
		}
	return 1;
}


//human player
void play(){

	cout<<"Choose a column where you would like to play: \n";

	string b;

	cin>>b;

	while(!valid(b)){
		cout<<"Please enter a different column: \n";
		cin>>b;
	}

	

	
	
}




int main(){

	

	int i = 0;

	draw();
	while(1){
		location a = move(arr);
		arr[a.row][a.col] = 'X';
		i = evaluate(arr, 1);
		if(i==10){
			cout<<"The computer has won\n";
			return 0;
		}
		else if(i==-10){
			cout<<"The human has won\n";
			return 0;
		}
		else if(i==0){
			cout<<"The game is a Tie\n";
			return 0;
		}
		draw();
		play();
		i = evaluate(arr, 0);
		if(i==10){
			cout<<"The computer has won\n";
			return 0;
		}
		else if(i==-10){
			cout<<"The human has won\n";
			return 0;
		}
		else if(i==0){
			cout<<"The game is a Tie\n";
			return 0;
		}
		draw();
	}
	return 0;
}
