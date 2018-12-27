/******************************************************************************/
/* Problem: Jury Jeopardy                                                     */
/* Solution: Simulation                                                       */
/* Time: O(n)                                                                 */
/* Author Quirijn Bouts                                                       */
// @EXPECTED_RESULTS@: CORRECT
/******************************************************************************/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum Dir{
	N,
	W,
	E,
	S
};

enum Move{
	F,
	L,
	R,
	B
};

struct Position{
	int x,y;
	Position():x(0),y(0){}
	Position(int _x,int _y): x(_x),y(_y){};
	Position operator+(const Position other) const{return Position(x+other.x,y+other.y);}
};

class Robot{
	public:
		Position pos; //current location
		Dir dir=E; //direction he is facing
		Position Move(Move move){
			int res[4][4][3]={ //results of a move: [Dir][Move][dx,dy,newDir] 
				{{ 0, 1, N},{-1, 0, W},{ 1, 0, E},{ 0,-1, S}}, //Facing North, moving F,L,R,B
				{{-1, 0, W},{ 0,-1, S},{ 0, 1, N},{ 1, 0, E}}, //Facing West
				{{ 1, 0, E},{ 0, 1, N},{ 0,-1, S},{-1, 0, W}}, //Facing East
				{{ 0,-1, S},{ 1, 0, E},{-1, 0, W},{ 0, 1, N}}  //Facing South
			};
			pos=pos+Position(res[dir][move][0],res[dir][move][1]);
			dir=Dir(res[dir][move][2]);
			return pos;
		}
};

Move GetMove(char c){
	switch(c){
		case 'F': return F; break;
		case 'L': return L; break;
		case 'R': return R; break;
		case 'B': return B; break;
	}
	return F;
}

void Code(){
	string instructions;
	cin >> instructions;
	Robot rob;
	Position high,low;
	//we go through the instructions twice, once to get the maze dimensions and once to "draw" the maze
	for(unsigned int i=0;i<instructions.length();i++){
		Position ret=rob.Move(GetMove(instructions.at(i)));
		if(ret.x>high.x){high.x=ret.x;}
		if(ret.y>high.y){high.y=ret.y;}
		if(ret.x<low.x){low.x=ret.x;} //note that this can not happen for this specific problem since we start at the west-most edge of the maze
		if(ret.y<low.y){low.y=ret.y;}
//cout << ">" << ret.x << "," << ret.y<<endl;
	}
	int w=high.x+abs(low.x)+2; //+2 because of outer wall & counting from 0
	int h=high.y+abs(low.y)+3; //+3 because of outer wall & counting from 0
	vector<vector<char>> maze;
	maze.resize(w);
	for(int i=0;i<w;i++){
		maze[i].resize(h);
		for(int j=0;j<h;j++){
			maze[i][j]='#';
		}
	}
	Position start(-low.x,-low.y+1); //+1 because of outer wall
	rob.pos=start;
	maze[start.x][start.y]='.';
	rob.dir=E;
	//now go through the instructions again and draw the maze
	for(unsigned int i=0;i<instructions.length();i++){
		Position ret=rob.Move(GetMove(instructions.at(i)));
		maze[ret.x][ret.y]='.';
	}
	//output:
	cout<<h<<" "<<w<<endl;
	for(int i=h-1;i>=0;i--){
		for(int j=0;j<w;j++){
			cout << maze[j][i];
		}
		cout<< endl;
	}
}

int main(){
	int runs;
	cin >> runs;
	cout << runs <<endl;
	while(runs--){
		Code();
	}
	return 0;
}


