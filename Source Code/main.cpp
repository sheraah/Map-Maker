#include "Game.h"
#include "TilemapReader.h"
int main()
{
    //creating the game object
    Game game({ 1500, 1000 }, "Map maker");

    game.run();
}