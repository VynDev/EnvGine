#include "Entity.h"
#include "Environment.h"
#include "Surface.h"
#include "Texture.h"
#include <iostream>

Texture *Entity::defaultTexture = new Texture(256, 256);

Entity::Entity(Environment *environment) : Base(environment->GetEnginePointer()) {
    this->environment = environment;
    this->texture = defaultTexture;
}

void Entity::Render(Surface &surface) {
    surface.Draw(texture, GetX(), GetY(), GetWidth(), GetHeight());
}