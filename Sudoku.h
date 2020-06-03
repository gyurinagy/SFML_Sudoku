#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Field.h"
#include "Gamemaster.h"
#include "vector"
#include <stdlib.h>
#include <time.h>

class Sudoku : public Game
{
	Gamemaster* gmaster;
	std::vector<std::vector<Field*> > _fields;

	void initializeVariables();
	void initWindow();
	void refreshGame();

public:
	Sudoku();
	Sudoku(int windowHeight, int windowWidth);
	~Sudoku();

	

};

