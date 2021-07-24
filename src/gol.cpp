#include "gol.h"
#include "globals.h"

//#include <iostream>
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
    std::uniform_int_distribution<std::mt19937::result_type> distc(0, 360);
    std::uniform_real_distribution<float> distf(-2.5f, 2.5f);

    _particles = new Particle[_p_count];
    // _particles[0] = Particle(100, 100, _p_radius);
    // _particles[0].setWrap(_width, _height);
    Vector2 force;
    RGBColor *color;
    for(int i = 0; i < _p_count; i++){
        force = Vector2(distf(rng), distf(rng));
        color = new RGBColor(distc(rng));
        _particles[i] = Particle(distw(rng), disth(rng), _p_radius);
        _particles[i].applyForce(force);
        _particles[i].setWrap(_width, _height);
        _particles[i].setColor(color);
    }
}

void GameOfLife::handleKeys( unsigned char key, int x, int y ) {
    y = _height - y;
    switch(key){
        case 'q':
            _running = !_running;
            break;
        // case 'r':
        //     _particles[1] = Particle(x, y, _p_radius);
        //     _particles[1].setWrap(_width, _height);
        //     std::cout << _particles[0].vectorTo(_particles[1]).mag() << std::endl;
        //     break;
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