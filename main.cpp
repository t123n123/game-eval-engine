#include <iostream> 
#include <vector> 
#include <random> 
#include <cctype>

using u32    = uint_least32_t;
using engine = std::mt19937;

using namespace std; 

struct Board {
	bool firstToMove;
	vector <int> stacks; 
};

int isEndState( Board board ) { 
	if(board.stacks.size() == 0) {
		return (board.firstToMove ? -1 : 1);
	} else return 0;
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


// random number from 0 to range-1
int generateRandom(int range) {
	std::random_device os_seed;
  	const u32 seed = os_seed();

  	engine generator( seed );
  	std::uniform_int_distribution< u32 > distribute(0, range-1);	
	return distribute(generator);
}


Board createBoard(vector<int> stacks, bool firstToMove = true) {
	Board newBoard; 
	newBoard.firstToMove = firstToMove;
	newBoard.stacks = stacks; 
	return newBoard;
}

vector<Board> outcomes(Board board) {
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

Board randomMove(Board board) { 
	vector<Board> nextMoves = outcomes(board); 
	int moveIndex = generateRandom(nextMoves.size());
	return nextMoves[moveIndex];	
}


// return 1 if first won, -1 if second 
int randomGameOutcome(Board board, bool print = false) {
	while(!isEndState(board)) {
		if(print) printBoard(board);
		board= randomMove(board);
	}
	if(print)printBoard(board);
	return (board.firstToMove ? -1 : 1);
}


// returns (value, complexity) of the board
// value is in the range (min_value, max_value), complexity is in the range (0, max_complexity)
// complexity represents how hard the position is to evaluate, prioritize good states with low complexity 
// and bad states with high complexity
// (hard-to-lose good positions, easy-to-comeback bad positions) 
// this should make the engine prefer moves that keep it alive for more turns
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
	cout << randomGameOutcome(initBoard, true) << '\n';
}
