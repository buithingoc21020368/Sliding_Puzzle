#include "stateMenu.h"

int main(int argc, char* argv[]) {
    Game game;
    if (game.init(new MenuState()))
        game.loop();
    return 0;
}