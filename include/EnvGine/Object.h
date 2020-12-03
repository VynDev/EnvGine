#pragma once
#include "RenderableEntity.h"

class Object : public RenderableEntity {
    
    public:

    Object(Environment *environment);

    virtual void Render(Surface &surface) override;
    virtual int GetWidth() const override {return width;}
    virtual int GetHeight() const override {return height;}

    void SetWidth(int value) {width = value;}
    void SetHeight(int value) {height = value;}

    protected:

    void SetTexture(Texture *texture) {this->texture = texture;}
    Texture &GetTexture() {return *texture;}

    static Texture *defaultTexture;

    private:

    Texture *texture = nullptr;
    int width;
    int height;
};