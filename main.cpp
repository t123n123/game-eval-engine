#include <iostream> 
#include <vector> 

using namespace std; 

struct Board {
	bool firstToMove;
	vector <int> stacks; 
};

Board createBoard(vector<int> stacks, bool firstToMove = true) {
	Board newBoard; 
	newBoard.firstToMove = firstToMove;
	newBoard.stacks = stacks; 
	return newBoard;
}

vector<Board> outcomes( Board board) {
	Board nextBoard = board;
	nextBoard.firstToMove = !nextBoard.firstToMove;
	vector<Board> outcomes;
	for(int index = 0; index < board.stacks.size(); index ++) {
		for(int value = board.stacks[index] - 1; value > 0; value --) {
			nextBoard.stacks[index] = value;
			outcomes.push_back(nextBoard);
		}
		nextBoard.stacks.erase(nextBoard.stacks.begin() + index);
		outcomes.push_back(nextBoard); 
		nextBoard.stacks = board.stacks;
	}

	return outcomes;
}

void printBoard(Board board) { 
	cout << (board.firstToMove ? "First To Move\n" : "Second To Move\n");
	for(int value : board.stacks) {
			cout << value << ' ';
	}
	if(board.stacks.size() == 0) {
		cout << "End State\n";
	}
	cout << '\n';
}


int isEndState( Board board ) { 
	if(board.stacks.size() == 0) {
		return (board.firstToMove ? -1 : 1);
	} else return 0;
}



pair<int,int> evaluateBoard( Board board ) {
	int end = isEndState(board); 
	if(end != 0) {
		return make_pair(end * 1000, 0);
	}
	return make_pair(0,0);
}




int main() { 
	int n; 
	cin >> n;
	vector <int> stacks;
	for(int i = 1; i <= n; i ++) {
		int a;
		cin >> a;
		stacks.push_back(a);
	}
	Board initBoard = createBoard(stacks);
	
	for(Board board : outcomes(initBoard)) {
		printBoard(board);			
	}
}
