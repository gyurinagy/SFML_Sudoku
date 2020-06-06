#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Field.h"
#include "Gamemaster.h"
#include "vector"



class Sudoku : public Game
{
	Gamemaster* gmaster;
	std::vector<std::vector<Field*> > _fields;

	std::vector<std::vector<int > > getFieldValues();

	void initializeVariables();
	void initializeWindow();
	void refreshGame();

public:
	Sudoku();
	Sudoku(int windowHeight, int windowWidth);
	~Sudoku();

	

};

