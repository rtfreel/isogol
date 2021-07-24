#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game{
protected:
    char* _name;
    int _width, _height;
    bool _running = false;
    SDL_Window *_window;
    SDL_GLContext glContext;

    bool init();
    bool initGL();
    void close();

    virtual void handleKeys( unsigned char key, int x, int y ) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void setup() = 0;

public:
    Game(char *name, int width, int height);
    virtual ~Game();

    void start();
    int getWidth();
    int getHeight();
};

#endif