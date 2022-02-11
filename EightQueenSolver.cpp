#include "EightQueenSolver.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

EightQueenSolver::EightQueenSolver()
	: Steps(0)
{
	for (int i = 0; i < 8; ++i)
	{
		States[i] = -1;
		Pos_Diagonal[i] = -10;
		Neg_Diagonal[i] = -10; //-10 because it is not a valid posi
	}
}

//Init first queen State[0] to random position, then set other queens on row that causes minimum conflicts
void EightQueenSolver::Initizialization()
{
	std::srand((unsigned int)std::time(NULL));
	States[0] = std::rand() % 8;
	for (int i = 1; i < 8; ++i) 
	{
		ConflictCounting(i);
	}
}

//Search for solution, keep track of steps
void EightQueenSolver::Search()
{
	int ConflictSize = 0;
	int LastStateSize = 0;
	std::vector<int> LastState = Queens_In_Conflict;
	int NoChangeCount = 0;
	bool StateChanged = false;
	//while keep going
	//for each queen, if it is in conflict, find min state
	//move to min state, random state if tie
	//if there is a local minima, move one to a random space, then find all conflicts and recount
	bool keepGoing = true;
	while (keepGoing)
	{
		StateChanged = false;
		CalculateDiagonals();
		CheckForConflicts();
		ConflictSize = Queens_In_Conflict.size();
		LastStateSize = LastState.size();
		if (ConflictSize == LastStateSize && ConflictSize != 0)
		{
			for (int i = 0; i < LastStateSize; ++i)
			{
				for (int j = 0; j < ConflictSize; ++j)
				{
					if (LastState[i] == Queens_In_Conflict[j])
					{
						break;
					}
					if (j == ConflictSize - 1)
					{
						StateChanged = true;
						break;
					}
				}
				if (StateChanged)
				{
					break;
				}
			}
			if (!StateChanged)
			{
				++NoChangeCount;
			}
			LastState = Queens_In_Conflict;
		}
		if (NoChangeCount >= 3)
		{
			//local minima
			int index = Queens_In_Conflict[std::rand() % ConflictSize];
			int cur_row = States[index];
			bool newRow = false;
			while (!newRow)
			{
				States[index] = std::rand() % 8;
				newRow = States[index] != cur_row; //don't want it to go to same row it was in
			}
			States[index] = std::rand() % 8;
			NoChangeCount = 0;
			CalculateDiagonals(); //State changed 
			CheckForConflicts(); //State changed so need to check for conflicts again
		}
		keepGoing = !IsFinalState(); //is final state returns false if it is not final state, so we need to invert it with !
		if (!keepGoing)
		{
			break;
		}
		ConflictCounting(Queens_In_Conflict[std::rand() % ConflictSize]);
		++Steps;
		if (Steps > 30)
		{
			break; //taking too long
		}
	}
	if (Steps > 30)
	{
		std::cout << "To many steps for this configuration" << std::endl;
		return;
	}
	std::cout << "# of steps: " << Steps << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << "(" << i << ", " << States[i] << ")" << std::endl;
	}
}

//Check EVERY queen for conflicts. If it is in conflict, push it's column index into Queens_In_Conflict
void EightQueenSolver::CheckForConflicts()
{
	bool ConflictFound[8] = { false };
	Queens_In_Conflict.clear();
	//for (int i = 0; i < 8; ++i) // don't need to go all the way to the end, as j will cover that with the other i's
	//{
	//	ConflictFound[i] = false;
	//}
	for (int i = 0; i < 7; ++i)
	{
		if (ConflictFound[i])
		{
			continue;
		}
		for (int j = i + 1; j < 8; ++j) //don't need to check things less than j because i checks those
		{
				//same row					same positive diagonal					same negative diagonal
			if (States[i] == States[j] || Pos_Diagonal[i] == Pos_Diagonal[j] || Neg_Diagonal[i] == Neg_Diagonal[j])
			{
				Queens_In_Conflict.push_back(i);
				ConflictFound[i] = true;
				if (!ConflictFound[j])
				{
					Queens_In_Conflict.push_back(j);
					ConflictFound[j] = true;
				}
				break; //can break because we're just checking for conflicts, not how many conflicts
			}
		}
	}
}

//Handles the 'movement' of the queens as well. Should change A) the state B) pos_diagonal[index] C) neg_diagonal[index]
void EightQueenSolver::ConflictCounting(int cur_index)
{
	int Conflicts[8];
	for (int i = 0; i < 8; ++i)
	{
		Conflicts[i] = 0;
	}
	int min_conflict_index = 0; //represents the row value with the minimum number of conflicts
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (col == cur_index)
			{
				continue;
			}
			if (States[col] == row)
			{
				++Conflicts[row];
			}
			if ((row + cur_index) == Neg_Diagonal[col])
			{
				++Conflicts[row];
			}
			if ((row - cur_index) == Pos_Diagonal[col])
			{
				++Conflicts[row];
			}
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		if (i == min_conflict_index)
		{
			continue;
		}
		if (Conflicts[i] == Conflicts[min_conflict_index])
		{
			if (std::rand() % 2 == 0)
			{
				min_conflict_index = i; //picking random on tie
			}
		}
		if (Conflicts[i] < Conflicts[min_conflict_index])
		{
			min_conflict_index = i;
		}
	}
	States[cur_index] = min_conflict_index;
}

void EightQueenSolver::CalculateDiagonals()
{
	for (int i = 0; i < 8; ++i)
	{
		Pos_Diagonal[i] = States[i] - i;
		Neg_Diagonal[i] = States[i] + i;
	}
}

//If there are no Queens_In_Conflict, we can return true
bool EightQueenSolver::IsFinalState()
{
	return Queens_In_Conflict.empty();
}