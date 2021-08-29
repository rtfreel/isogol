#include "gol.h"
#include "globals.h"

// #include <iostream>
#include <random>
#include <GL/gl.h> 
#include <GL/glu.h>

GameOfLife::GameOfLife(int width, int height) : Game((char*)"Isosurface particle game of life", width, height) {
    setGroupCount(global::G_COUNT);
    setGroupSize(global::G_SIZE);
    setRadius(global::P_RADIUS);
}

void GameOfLife::setup(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distw(0, _width);
    std::uniform_int_distribution<std::mt19937::result_type> disth(0, _height);
    std::uniform_int_distribution<std::mt19937::result_type> distc(0, 360);
    std::uniform_real_distribution<float> distf(-2.5f, 2.5f);

    _particles = new Particle[this->getTotal()];
    // _particles[0] = Particle(100, 100, _p_radius);
    // _particles[0].setWrap(_width, _height);
    Vector2 force;
    RGBColor *color;
    int index;
    for(int g = 0; g < _g_count; g++) {
        color = new RGBColor(distc(rng));
        for(int i = 0; i < _g_size; i++) {
            index = (_g_size * g) + i;
            force = Vector2(distf(rng), distf(rng));
            _particles[index] = Particle(distw(rng), disth(rng), _p_radius);
            _particles[index].setType(g);
            _particles[index].applyForce(force);
            _particles[index].setWrap(_width, _height);
            _particles[index].setColor(color);
        }
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
        for(int i = 0; i < this->getTotal(); i++){
            _particles[i].update();
            _particles[i].render();
            _particles[i].applyFriction(global::MU);
        }
    }
}

int GameOfLife::getTotal(){ return this->_g_count * this->_g_size; }
void GameOfLife::setGroupCount(int count){ this->_g_count = count; }
void GameOfLife::setGroupSize(int size){ this->_g_size = size; }
void GameOfLife::setRadius(float radius){ this->_p_radius = radius; }