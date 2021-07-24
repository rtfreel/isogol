#ifndef PARTICLE_H
#define PARTICLE_H

#include "gameObject.h"
#include "globals.h"

class Particle : public GameObject{
private:
    bool _wrap = false;
    float _x, _y, _r, _xBound, _yBound;
    Vector2 _vel, _acc;

    void wraparound();

public:
    Particle();
    Particle(float x, float y, float r);
    void update();
    void render();

    void applyFriction(float mu);
    void applyForce(Vector2 &force);

    void setWrap(float maxX, float maxY);
    void disableWrap();

    Vector2 getPos();
    Vector2& getVel();
    Vector2& getAcc();
};

#endif