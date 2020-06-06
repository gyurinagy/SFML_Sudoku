#include "Gamemaster.h"
#include <time.h> 
#include <stdlib.h> 
#include <iostream> 
#include <set> 
Gamemaster::Gamemaster():
	_status{ingame}
{
	generateFields();
}

Gamemaster::~Gamemaster() 
{
}
/// ***** CREATING PUZZLE ***** ///
void Gamemaster::swapRows()
{
    int block = rand() % 3 * 3;
    int row1 = block + rand() % 3;
    int row2 = block + rand() % 3;
    _completedFields[row1].swap(_completedFields[row2]);
}
void Gamemaster::swapColumns()
{
    int block = rand() % 3 * 3;
    int column1 = block + rand() % 3;
    int column2 = block + rand() % 3;
    for (unsigned int i = 0; i < 9; i++)
        std::swap(_completedFields[i][column1], _completedFields[i][column2]);
}
void Gamemaster::swapBlockRows()
{
    int block1 = rand() % 3 * 3;
    int block2 = rand() % 3 * 3;
    _completedFields[block1].swap(_completedFields[block2]);
    _completedFields[block1 + 1].swap(_completedFields[block2 + 1]);
    _completedFields[block1 + 2].swap(_completedFields[block2 + 2]);
}
void Gamemaster::swapBlockColumns()
{
    int block1 = rand() % 3 * 3;
    int block2 = rand() % 3 * 3;
    for (unsigned int i = 0; i < 9; i++)
    {
        std::swap(_completedFields[i][block1], _completedFields[i][block2]);
        std::swap(_completedFields[i][block1 + 1], _completedFields[i][block2 + 1]);
        std::swap(_completedFields[i][block1 + 2], _completedFields[i][block2 + 2]);
    }
}
void Gamemaster::transposeMain()
{
    for (unsigned int i = 0; i < 9; i++)
        for (unsigned int j = 0; j < i; j++)
            std::swap(_completedFields[i][j], _completedFields[j][i]);
}
void Gamemaster::transposeAnti()
{
    for (unsigned int i = 0; i < 9; i++)
        for (unsigned int j = 0; j < 9 - i; j++)
            std::swap(_completedFields[i][j], _completedFields[8 - j][8 - i]);
}
void Gamemaster::shuffle()
{
    srand(time(NULL));

    for (unsigned int i = 0; i < 25; i++)
    {
        int dice = rand() % 6;
        switch (dice)
        {
        case 0:
            transposeAnti(); break;
        case 1:
            swapBlockColumns(); break;
        case 2:
            swapBlockRows(); break;
        case 3:
            transposeMain(); break;
        case 4:
            swapRows(); break;
        case 5:
            swapColumns(); break;
        }
    }
}
char Gamemaster::good(int i, int j) 
{
    std::set<char> exclude; 

    for (int k = 0; k < 9; k++)
    {
        if (k == i) continue;
        exclude.insert(exclude.begin(), _fields[k][j]);
    }
    for (int k = 0; k < 9; k++)
    {
        if (k == j) continue;
        exclude.insert(exclude.begin(), _fields[i][k]);
    }
    for (int k = floor(j / 3) * 3; k < floor(j / 3) * 3 + 3; k++)
    {
        if (k == j) continue;
        for (int l = floor(i / 3) * 3; l < floor(i / 3) * 3 + 3; l++)
        {
            if (l == i) continue;
            exclude.insert(exclude.begin(), _fields[l][k]);
        }
    }

    if (exclude.size() - exclude.count(0) == 8)
        for (unsigned char k = 1; k <= 9; k++)
            if (!exclude.count(k)) return k;

    return 0;
}
void Gamemaster::eraseCells()//levels level)
{
    int erased = 0;
    int limit = 0;
    while (erased < 31 || 1000 < limit++)
    {
        int i = rand() % 9;
        int j = rand() % 9;
        if (_fields[i][j] && good(i, j) != 0)
        {
            _fields[i][j] = 0;
            erased++;
        }
    }
   /* for (unsigned int i = 0; i < 9; i++)
        for (unsigned int j = 0; j < 9; j++)
            if (good(i, j) != 0)
                _fields[i][j] = 0;*/

}

 /// ***** CHECKING ***** ///
// Check if the created board is equal with the solution
// Returning true if the player solved the game
// Setting the status to 'winner'
bool Gamemaster::checkForWin()
{
    bool win = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (_completedFields[i][j] != _fields[i][j]) {
                win = false;
                break;
            }
        }
    }
    _status = winner;
    return win;
}
// Check if every field has a value, so whether the board is full or not
// Returning true if the board is full.
// Setting the game status to 'fullboard'
bool Gamemaster::checkFullBoard() {
    bool full = true;
    for (auto row : _fields)
        for (auto f : row)
            if (f == 0) {
                full = false;
                break;
            }
    _status = fullBoard;
    return full;

}
// Get every field's value that is displayed and compare it to every value the master have
// if there is two value that different the function returning true
bool Gamemaster::updateField(const std::vector<std::vector<int>>& values)
{
    bool change = false;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (values[i][j] != _fields[i][j]) {
                _fields[i][j] = values[i][j];
                change = true;
                show(); // TÖRLÉS
            }

    return change;
}

/// ***** PUBLIC ***** ///
void Gamemaster::check(const std::vector<std::vector<int>> & values)
{
    if (updateField(values)) {
        if (checkFullBoard()) {
            
            if (checkForWin()) {
                std::cout << "hello";
                _status = winner;
            }
        }
    }
}

void Gamemaster::generateFields()
{
    for (unsigned int i = 0; i < 9; i++)
    {
        _completedFields.push_back({});
        for (unsigned int j = 0; j < 9; j++)
            _completedFields[i].push_back((i * 3 + j + (int)floor(i / 3)) % 9 + 1);
    }

    shuffle();

    _fields = _completedFields;

    eraseCells();

    _erasedFields = _fields;
    for (auto row : _completedFields) {
        for (auto f : row) {
            std::cout << f << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
void Gamemaster::restartGame()
{
    _fields = _erasedFields;
}
void Gamemaster::show() {
   
    
    /*for (auto row : _fields) {
        for (auto f : row) {
            std::cout << f << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';*/
}

gameStatus Gamemaster::getGameStatus() const
{
	return gameStatus();
}

std::vector<std::vector<int>> Gamemaster::getFields() const
{
	return _fields;
}
/// **************************************************************************

