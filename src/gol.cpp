#include "gol.h"
#include "globals.h"

#include <random>
#include <GL/gl.h> 
#include <GL/glu.h>

GameOfLife::GameOfLife(int width, int height) : Game((char*)"Isosurface particle game of life", width, height) {
    setCount(global::G_SIZE);
    setRadius(global::P_RADIUS);
}

void GameOfLife::setup(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distw(0, _width);
    std::uniform_int_distribution<std::mt19937::result_type> disth(0, _height);
    std::uniform_real_distribution<float> distf(-2.5f, 2.5f);

    _particles = new Particle[_p_count];
    Vector2 force;
    for(int i = 0; i < _p_count; i++){
        _particles[i] = Particle(distw(rng), disth(rng), _p_radius);
        force = Vector2(distf(rng), distf(rng));
        _particles[i].applyForce(force);
        _particles[i].setWrap(_width, _height);
    }
}

void GameOfLife::handleKeys( unsigned char key, int x, int y ) {
    switch(key){
        case 'q':
            _running = !_running;
    }
}

void GameOfLife::update() {}

void GameOfLife::render(){
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
    //Render quad
    if( _running )
    {
        for(int i = 0; i < _p_count; i++){
            _particles[i].update();
            _particles[i].render();
            _particles[i].applyFriction(global::MU);
        }
    }
}

void GameOfLife::setCount(int count){ this->_p_count = count; }
void GameOfLife::setRadius(float radius){ this->_p_radius = radius; }