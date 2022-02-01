#pragma once
class EightQueenSolver
{
public:

	EightQueenSolver();
	void Initizialization();
	void Search();
	void ConflictCounting(int cur_index);
	bool IsFinalState();

private:
	int States[8];
};

