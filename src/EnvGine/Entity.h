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
    virtual void Render(Surface &surface);

    void SetClickable(bool value) {isClickable = value;}
    bool IsClickable() const {return isClickable;}
    
    void SetClicked_(bool value) {isClicked = value;}
    bool IsClicked() const {return isClicked;}
    virtual void OnClick() {};
    
    void EnableRendering(bool value) {shouldRender = value;}
    bool ShouldRender() const {return shouldRender;}

    const Position &GetPosition() const {return position;}
    int GetX() const {return position.x;}
    int GetY() const {return position.y;}
    void SetPosition(int x, int y) {position.x = x; position.y = y;}
    void SetX(int x) {position.x = x;}
    void SetY(int y) {position.y = y;}

    void SetWidth(int value) {width = value;}
    int GetWidth() const {return width;}
    void SetHeight(int value) {height = value;}
    int GetHeight() const {return height;}

    void SetTexture(Texture *texture) {this->texture = texture;}
    Texture &GetTexture() {return *texture;}

    static Texture *defaultTexture;
    
    protected:

    Environment *environment = nullptr;
    Texture *texture = nullptr;

    bool isClickable = false;
    bool isClicked = false;

    bool shouldRender = true;

    Position position;
    int width;
    int height;

};