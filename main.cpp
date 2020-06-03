#include "Game.h"

int main()
{
    auto game = CreateGame();
    game->init();
    game->run();
    delete game;
    return 0;
}
