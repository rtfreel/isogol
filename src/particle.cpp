#include "particle.h"

#include <math.h>
#include <GL/gl.h>

Particle::Particle() : _x(0), _y(0) {}
Particle::Particle(float x, float y, float r) : _x(x), _y(y), _r(r) {}

void Particle::update() {
    _vel += _acc;
    _x += _vel.x;
    _y += _vel.y;
    _acc *= 0;
    if(_wrap)
        wraparound();
}

void Particle::render() {
    glColor3ub(color->r, color->g, color->b);
    glBegin(GL_POLYGON);
    for (int a = 0; a < 360; a += 360 / 90) {
        double heading = a * 3.1415926535897932384626433832795 / 180;
        glVertex2i(_x + (cos(heading) * _r), _y + (sin(heading) * _r));
    }
    glEnd();
}

void Particle::wraparound(){
    if(_x < 0)
      _x = _xBound - fmod(abs(_x), _xBound);
    if(_x > _xBound)
      _x = fmod(_x, _xBound);
    if(_y < 0)
      _y = _yBound - fmod(abs(_y), _yBound);
    if(_y > _yBound)
      _y = fmod(_y, _yBound);
}

Vector2 Particle::vectorTo(Particle &particle){
    Vector2 pos = this->getPos();
    Vector2 result = particle.getPos() - pos;
    if(_wrap){
        float dx = abs(result.x);
        float dy = abs(result.y);
        bool xcross = dx > _xBound / 2,
            ycross = dy > _yBound / 2;
        if(xcross){
            dx = _xBound - dx;
            result.x *= -1;
        }
        if(ycross){
            dy = _yBound - dy;
            result.y *= -1;
        }
        if(xcross || ycross)
            result.setMag(sqrtf((dx*dx) + (dy*dy)));
    }
    return result;
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

void Particle::setWrap(float maxX, float maxY) {
    _xBound = maxX;
    _yBound = maxY;
    _wrap = true;
}
void Particle::disableWrap() { _wrap = false; }

void Particle::setColor(RGBColor *color) { 
    delete this->color; 
    this->color = color; 
}
Vector2 Particle::getPos(){ return Vector2(_x, _y); }
Vector2& Particle::getVel(){ return _vel; }
Vector2& Particle::getAcc(){ return _acc; }