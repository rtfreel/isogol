#ifndef PARTICLE_H
#define PARTICLE_H

#include "gameObject.h"
#include "globals.h"

class Particle : public GameObject{
private:
    float _x, _y, _r;
    Vector2 _vel, _acc;

public:
    Particle();
    Particle(float x, float y, float r);
    void update();
    void render();

    void applyFriction(float mu);
    void applyForce(Vector2 &force);

    Vector2 getPos();
    Vector2& getVel();
    Vector2& getAcc();
};

#endif