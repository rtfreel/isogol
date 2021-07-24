#include "gol.h"
#include "globals.h"

int main(int argc, char *argv[]){
    GameOfLife *game = new GameOfLife(global::SCREEN_WIDTH, global::SCREEN_HEIGHT);
    game->start();
    return 0;
}