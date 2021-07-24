#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
    virtual ~GameObject(){};
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif