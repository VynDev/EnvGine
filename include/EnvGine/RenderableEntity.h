#pragma once
#include "Entity.h" 

class RenderableEntity : public Entity {

    public:

    RenderableEntity(Environment *environment) : Entity(environment) {}

    virtual bool IsRenderable() const {return true;}
    virtual void Render(Surface &surface) {};
    virtual void OnClick() {};
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    void EnableRendering(bool value) {shouldRender = value;}
    bool ShouldRender() const {return shouldRender;}

    void SetClickable(bool value) {isClickable = value;}
    bool IsClickable() const {return isClickable;}
    
    void SetClicked_(bool value) {isClicked = value;}
    bool IsClicked() const {return isClicked;}
    
    private:

    bool shouldRender = true;

    bool isClickable = false;
    bool isClicked = false;
};