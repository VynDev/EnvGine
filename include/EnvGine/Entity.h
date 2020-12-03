#pragma once

#include "Base.h"
#include "Utils.h"

class Environment;
class Surface;
class Texture;

class Entity : public Base {

    public:

    Entity(Environment *environment);

    Environment &GetEnvironment() {return *environment;}

    virtual void Tick(float deltaTime) {};
    virtual bool IsRenderable() const {return false;}

    virtual void SetX(int x) {position.x = x;}
    virtual void SetY(int y) {position.y = y;}
    virtual int GetX() const {return position.x;}
    virtual int GetY() const {return position.y;}
    virtual void SetPosition(int x, int y) {position.x = x; position.y = y;}
    virtual const Position &GetPosition() const {return position;}

    protected:

    Environment *environment = nullptr;
    Position position = {0, 0};
};