#pragma once

#include <SFML/Graphics.hpp>
#include "widget.h"
#include "Field.h"
#include "vector"


class Game
{
protected:
    sf::RenderWindow* _window;
    sf::VideoMode _videoMode;
    int _focusedWidget, _hoveredWidget;
    sf::Color _backgroundColor;
    sf::Event _ev;
    sf::Font _font;

    std::vector<widget*> _widgets;

    /// INITIALIZING
    virtual void initializeVariables()=0;
    virtual void initWindow();
    void setBackground(sf::Color color);
    
    /// EVENT HANDLING AND RUNNING
    virtual void refreshGame() = 0;
    void pollEvents();
    void update();
    void render();

public:
    /// CONSTRUCTOR / DESTRUCTOR
    Game();
    Game(int windowheight, int windowwidth);
    virtual ~Game();
   
    void registerWidget(widget* widget);
    void init();
    void run();
};

extern Game* CreateGame();
