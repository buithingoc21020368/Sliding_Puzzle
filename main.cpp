#include "Gamestate_Menu.h"
#include <SDL_main.h>
#include "Graphics.h"
#include <bits/stdc++.h>
extern const int numCats = 12;
int randInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
extern int id = 0;

int main(int argc, char **args)
{
    srand(time(NULL));
    id = randInt(1, numCats);
    Game game;
    if (game.init(new MenuState()))
        game.loop();
    return 0;
}