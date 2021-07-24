#include "particle.h"

#include <math.h>
#include <stdio.h>
#include <GL/gl.h>

Particle::Particle() : _x(0), _y(0) {}
Particle::Particle(float x, float y, float r) : _x(x), _y(y), _r(r) {}

void Particle::update() {
    _vel += _acc;
    _x += _vel.x;
    _y += _vel.y;
    _acc *= 0;
}

void Particle::render() {
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    for (int a = 0; a < 360; a += 360 / 90)
    {
        double heading = a * 3.1415926535897932384626433832795 / 180;
        glVertex2i(_x + (cos(heading) * _r), _y + (sin(heading) * _r));
    }
    glEnd();
}

void Particle::applyFriction(float mu){
    if(_vel.mag() < mu){
        _acc -= _vel;
        return;
    }
    Vector2 friction = _vel;
    friction.setMag(mu);
    _acc -= friction;
}

void Particle::applyForce(Vector2 &force){
    _acc += force;
}

Vector2 Particle::getPos(){ return Vector2(_x, _y); }
Vector2& Particle::getVel(){ return _vel; }
Vector2& Particle::getAcc(){ return _acc; }