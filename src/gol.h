#ifndef GOL_H
#define GOL_H

#include "game.h"
#include "particle.h"

class GameOfLife : public Game{
private:
    int _p_count, _g_count, _g_size;
    float _p_radius;
    Particle *_particles;

    void handleKeys( unsigned char key, int x, int y );
    void update();
    void render();
    void setup();

public:
    GameOfLife(int width, int height);

    void setCount(int count);
    void setDensity(int density);
    void setRadius(float radius);
};
#endif