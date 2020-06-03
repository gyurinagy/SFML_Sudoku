#pragma once
#include "vector"

enum gameStatus {ingame, winner};

class Gamemaster
{
	gameStatus _status;
	std::vector<std::vector<int> > _fields;
	std::vector<std::vector<int> > _erasedFields;
	std::vector<std::vector<int> > _completedFields;

	/// FUNCTIONS
	void checkFields();
	void shuffle();
	void swapRows();
	void swapColumns();
	void swapBlockRows();
	void swapBlockColumns();
	void transposeMain();
	void transposeAnti();
	void eraseCells();
	char good(int i, int j);
public:
	Gamemaster();
	~Gamemaster();

	
	void restartGame(); //restart
	void generateFields(); //new game
	void show();
	gameStatus getGameStatus() const;
	std::vector<std::vector<int> > getFields() const;
};

