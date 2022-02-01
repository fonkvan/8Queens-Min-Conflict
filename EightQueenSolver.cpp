#include "EightQueenSolver.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

EightQueenSolver::EightQueenSolver()
{
	for (int i = 0; i < 8; ++i)
	{
		States[i] = -1;
	}
}

void EightQueenSolver::Initizialization()
{
	std::srand((unsigned int)std::time(NULL));
	States[0] = std::rand() % 8;
	for (int i = 1; i < 8; ++i) 
	{
		ConflictCounting(i);
	}
}

void EightQueenSolver::Search()
{
	bool keepGoing = true;
	while (keepGoing)
	{
		ConflictCounting(std::rand() % 8);
		keepGoing = IsFinalState();
	}
	for (int i = 0; i < 8; ++i)
	{
		std::cout << "(" << i << ", " << States[i] << ")" << std::endl;
	}
}

void EightQueenSolver::ConflictCounting(int cur_index)
{
	int Conflicts[8];
	int min_conflict_index = 0;
	for (int i = 0; i < 8; ++i)
	{
		Conflicts[i] = 0;
	}
	for (int i = 0; i < 8; ++i)
	{
		if (States[i] == -1)
		{
			break;
		}
		if (i == cur_index)
		{
			continue;
		}
		for (int j = 0; j < 8; ++j)
		{
			if (abs(i - cur_index) == abs(States[i] - j) || States[i] == j)
			{
				++Conflicts[j];
			}
		}
	}
	for (int i = 1; i < 8; ++i)
	{
		if (Conflicts[i] < Conflicts[min_conflict_index])
		{
			min_conflict_index = i;
		}
	}
	States[cur_index] = min_conflict_index;
}

bool EightQueenSolver::IsFinalState()
{
	int last_row = 0;
	for (int i = 0; i < 8; ++i)
	{
		last_row = States[i];
		ConflictCounting(i);
		if (last_row != States[i]) //there was a change
		{
			return false;
		}
	}
	return true;
}