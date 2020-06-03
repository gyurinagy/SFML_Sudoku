#include "Sudoku.h"
#include "iostream"

extern Game* CreateGame() { return new Sudoku(); }


/// CONSTRUCTOR / DESTRUCTOR
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

/// INITIALIZING
void Sudoku::initWindow()
{
    _window = new sf::RenderWindow();
    _window->create(_videoMode, "Sudoku", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(60);
}
void Sudoku::initializeVariables()
{
    gmaster = new Gamemaster();
    std::vector<std::vector<int > >vec2 =  gmaster->getFields() ;

    if (!_font.loadFromFile("Fonts/Poppins-Medium.ttf"))
        throw("COULD NOT LOAD FONT!");

    srand(time(NULL));

    for (int i = 0; i < 9; i++) {
        std::vector<Field*> vec;
        for (int j = 0; j < 9; j++) {
            Field* field = new Field(_font, this, { (float)(100 + j * (40 + 3)),(float)(100 + i * (40 + 3)) });
            field->setOutlineColor(sf::Color::Black);
            field->setOutlineThickness(3.f);
            field->setValue(vec2[i][j]);
            vec.push_back(field);
        }
        _fields.push_back(vec);
    }

    

    gmaster->show();
}

/// GAME MECHANICS
void Sudoku::refreshGame()
{
}


