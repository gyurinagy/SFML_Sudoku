#include "Game.h"
#include "iostream"


/// ****************** PRIVATE FUNCTIONS ******************
void Game::initWindow() 
{
    _window = new sf::RenderWindow();
    _window->create(_videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(60);
}

void Game::setBackground(sf::Color color)
{
    _backgroundColor = color;
}



/// ****************** CONSTRUCTOR / DESTRUCTOR ******************
Game::Game() :
    _window{nullptr}, _videoMode{600, 600}, _focusedWidget{ -1 }, _hoveredWidget{ -1 }, _backgroundColor{sf::Color::Black}
{ }

Game::Game(int windowheight, int windowwidth) :
    _window(nullptr), _videoMode(windowheight,windowwidth), _focusedWidget{ -1 }, _hoveredWidget{ -1 }
{ }

Game::~Game()
{
    for (auto w : _widgets) delete w;
  
    delete _window;
}

/// ****************** FUNCTIONS ******************
void Game::init()
{
    initWindow();
    initializeVariables();
}

void Game::registerWidget(widget* widget)
{
    _widgets.push_back(widget);
}

/// *********** EVENT HANDLING / MAIN LOOP *****************
void Game::pollEvents() {
    while (_window->pollEvent(_ev)) {
        switch (_ev.type) {

        case sf::Event::Closed:
            _window->close();
            break;

        /// TRIGGERED BY KEY PRESSING
        case sf::Event::KeyPressed:
            if (_ev.key.code == sf::Keyboard::Escape)
                _window->close();
            if (_ev.key.code == sf::Keyboard::Tab) {
                for (size_t i = 0; i < _widgets.size(); i++) {
                    /// FIND THE RECENT FOCUSED WIDGET AND SET IT TO DEFAULT
                    if (_widgets[i]->getState()==_focused) {
                        _focusedWidget = i;
                        _widgets[_focusedWidget]->setState(_default);
                        break;
                    }
                }
                if (_widgets.size() > 1) {
                    _focusedWidget++;
                    if (_focusedWidget > _widgets.size() - 1) { _focusedWidget = 0; }
                    if (!(_widgets[_focusedWidget]->isFocusable())) { _focusedWidget++; }
                }
            }
            break;  

        /// TRIGGERED BY MOUSE CLICK
        case sf::Event::MouseButtonPressed:
            
            if (_ev.mouseButton.button == sf::Mouse::Left) {
                int recentFocusedWidget = -1;
                for (size_t i = 0; i < _widgets.size(); i++) {
                    if (_widgets[i]->isHovered(sf::Mouse::getPosition(*_window)) &&
                        _widgets[i]->isFocusable()) {
                        recentFocusedWidget = i;
                        break;
                    }
                }
                if ( recentFocusedWidget != _focusedWidget && _focusedWidget != -1) {
                    _widgets[_focusedWidget]->setState(_default);
                    _focusedWidget = -1;
                }
                _focusedWidget = recentFocusedWidget;
            }
            break;

        /// TRIGGERED BY MOUSE BUTTON RELEASE
        /*case sf::Event::MouseButtonReleased:
            if (_ev.mouseButton.button == sf::Mouse::Left)
                for (size_t i = 0; i < _widgets.size(); i++) {
                    _focusedWidget = -1;
                    _widgets[i]->setState(_default);
                }
            break;*/

        /// TRIGGERED BY MOUSE MOVEMENT
        case sf::Event::MouseMoved:
            int recentHoveredWidget = -1;
            for (size_t i = 0; i < _widgets.size(); i++) {
                
                if (_widgets[i]->isHovered(sf::Mouse::getPosition(*_window)) &&
                    _widgets[i]->canHoverChangeAppearance()) {
                    recentHoveredWidget = i;
                    break;
                }
            }
            if (_focusedWidget != _hoveredWidget && recentHoveredWidget != _hoveredWidget && _hoveredWidget!=-1) {
                _widgets[_hoveredWidget]->setState(_default);
                _hoveredWidget = -1;
            }
            else {
                _hoveredWidget = recentHoveredWidget;
            }
            break;
        }

        if (_hoveredWidget != -1) { _widgets[_hoveredWidget]->handle(_ev, _hovered); }
        if (_focusedWidget != -1) {  _widgets[_focusedWidget]->handle(_ev, _focused); }
    }
}

void Game::update()
{
    pollEvents(); // Event handling
    refreshGame(); // Sending data to the Gamemaster, processing, sending data back
}

void Game::render()
{
    _window->clear(_backgroundColor);

    for (auto w : _widgets) w->drawTo(*_window);

    _window->display();
}

void Game::run()
{
    while (_window->isOpen()) {
        update();
        render(); //Drawing every element to the window
    }
}
