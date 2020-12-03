#include "Object.h"
#include "Environment.h"
#include "Surface.h"
#include "Texture.h"
#include <iostream>

Texture *Object::defaultTexture = new Texture(256, 256);

Object::Object(Environment *environment) : RenderableEntity(environment) {
    this->texture = defaultTexture;
}

void Object::Render(Surface &surface) {
    surface.Draw(texture, GetX(), GetY(), GetWidth(), GetHeight());
}