#include "Sudoku.h"
#include "iostream"

extern Game* CreateGame() { return new Sudoku(); }


/// ***** CONSTRUCTOR / DESTRUCTOR ***** ///
Sudoku::Sudoku() : Game(), gmaster{nullptr}
{
	setBackground(sf::Color(250, 235, 215, 255));
}
Sudoku::Sudoku(int windowHeight, int windowWidth) : Game(windowHeight, windowWidth), gmaster{ nullptr }
{
	setBackground(sf::Color(250, 235, 215, 255));
}

Sudoku::~Sudoku()
{
}

/// ***** INITIALIZING ***** ////
void Sudoku::initializeWindow()
{
    _window = new sf::RenderWindow();
    _window->create(_videoMode, "Sudoku", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(60);
}

void Sudoku::initializeVariables()
{
    gmaster = new Gamemaster();
    std::vector<std::vector<int > >vec =  gmaster->getFields() ;

    if (!_font.loadFromFile("Fonts/Poppins-Medium.ttf"))
        throw("COULD NOT LOAD FONT!");


    for (int i = 0; i < 9; i++) {
        std::vector<Field*> v;
        for (int j = 0; j < 9; j++) {
            Field* field = new Field(_font, this, { (float)(100 + j * (40 + 3)),(float)(100 + i * (40 + 3)) });
            field->setOutlineColor(sf::Color::Black);
            field->setOutlineThickness(3.f);
            field->setValue(vec[i][j]);
            field->setFieldState(active);
            v.push_back(field);
        }
        _fields.push_back(v);
    }

}
/// GAME MECHANICS
void Sudoku::refreshGame()
{
    gmaster->check(getFieldValues());
    if (gmaster->getGameStatus() == winner)
        for (size_t i = 0; i < _fields.size(); i++)
            for (size_t j = 0; j < _fields[i].size(); j++)
                _fields[i][j]->setFieldState(inactive);

            

        
    
    
    
}
///
std::vector<std::vector<int>> Sudoku::getFieldValues()
{
    std::vector<std::vector<int> > values;
    for (int i = 0; i < _fields.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < _fields[i].size(); j++) {
            row.push_back(_fields[i][j]->getValue());
        }
        values.push_back(row);
    }
    return values;
}