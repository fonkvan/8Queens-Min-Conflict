#pragma once
#include <vector>

class EightQueenSolver
{
public:

	//Constructor
	EightQueenSolver();
	//Initializes the board, with leftmost queen in random spot, and then each queen after that in a min conflict position
	void Initizialization();
	//The main function that searches for a solution
	void Search();
	//counts the number of conflicts on each row on a given column
	void ConflictCounting(int cur_index);
	//Check which queens are actually IN conflict, and push them into the Queens_In_Conflict vector
	void CheckForConflicts();
	//For each queen, calculates it's 'positive' diagonal and 'negative' diagonal values
	void CalculateDiagonals();
	//Checks if Queens_In_Conflict is empty or not
	bool IsFinalState();

private:
	//# of steps to reach goal state
	int Steps;
	//A List of 'queens', the index being the column and the value at that index being the row
	int States[8];
	//Positive Diagonal explanation: Going from bottom left to top right (like y = x) squares in the same diagonal share a value equal to row - col
	int Pos_Diagonal[8]; //row - col
	//Negative Diagonal explanation: Going from the top left down to the bottom right (in a y = -x like way), squares of the same diagonal are equal to row + col
	int Neg_Diagonal[8]; //row + col 
	//A list that contains ONLY the queens that are currently in conflict
	std::vector<int> Queens_In_Conflict;
};

