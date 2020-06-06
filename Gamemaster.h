#pragma once
#include "vector"

enum gameStatus {ingame, fullBoard, winner};

class Gamemaster
{
	gameStatus _status;
	std::vector<std::vector<int> > _fields;
	std::vector<std::vector<int> > _erasedFields;
	std::vector<std::vector<int> > _completedFields;

	/// CREATING PUZZLE
	void swapRows();
	void swapColumns();
	void swapBlockRows();
	void swapBlockColumns();
	void transposeMain();
	void transposeAnti();
	void shuffle();
	char good(int i, int j);
	void eraseCells();

	/// CHECKING 
	bool checkForWin();
	bool checkFullBoard();
	bool updateField(const std::vector<std::vector<int > >& values);

public:
	Gamemaster();
	~Gamemaster();

	/// PUBLIC FUNCTIONS
	void check(const std::vector<std::vector<int > >& values);
	void restartGame(); //restart
	void generateFields(); //new game
	void show();
	gameStatus getGameStatus() const;
	std::vector<std::vector<int> > getFields() const;
};

